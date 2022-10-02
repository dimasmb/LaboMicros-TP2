/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "i2cm.h"
#include "MK64F12.h"
#include "hardware.h"
#include "board.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ALT5 5
#define ALT2 2

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{
  I2C0_SCL_ACC = PORTNUM2PIN(PE, 24),
  I2C0_SDA_ACC = PORTNUM2PIN(PE, 25),
  I2C0_SCL_EXT = PORTNUM2PIN(PB, 2),
  I2C0_SDA_EXT = PORTNUM2PIN(PB, 3),
  I2C1_SCL = PORTNUM2PIN(PC, 10),
  I2C1_SDA = PORTNUM2PIN(PC, 11),
};

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static I2C_Type* I2C_x[2] = {I2C0, I2C1};
static i2cx i2c_num;
static RW_mode rw_mode;
static bool reg_read = false;
static uint32_t cant_bytes;
static uint8_t* data = NULL;
//static uint8_t* Wdata;
static uint8_t* Rdata = NULL;
//static uint8_t W_cant_bytes;
static uint8_t R_cant_bytes;
static bool W_error = false;
static uint8_t dev_address;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void I2C_init(i2cx num)
{
  SIM->SCGC4 |= (1<<(6+num)); //clock gating
  i2c_num = num;

  //configuro los pines
  if(!num)
  {
    //Para el I2C0, configuro los pines PTE24 y 25 que son los del acelerómetro
    PORTE->PCR[PIN2NUM(I2C0_SCL_ACC)] = 0;
    PORTE->PCR[PIN2NUM(I2C0_SCL_ACC)] |= PORT_PCR_MUX(ALT5);
    PORTE->PCR[PIN2NUM(I2C0_SCL_ACC)] |= (PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
    
    PORTE->PCR[PIN2NUM(I2C0_SDA_ACC)] = 0;
    PORTE->PCR[PIN2NUM(I2C0_SDA_ACC)] |= PORT_PCR_MUX(ALT5);
    PORTE->PCR[PIN2NUM(I2C0_SDA_ACC)] |= (PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);

  }
  else
  {
    //Para el I2C1, configuro los pines PTC10 y 11
    PORTC->PCR[PIN2NUM(I2C1_SCL)] = 0;
    PORTC->PCR[PIN2NUM(I2C1_SCL)] |= PORT_PCR_MUX(ALT2);
    PORTC->PCR[PIN2NUM(I2C1_SCL)] |= (PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
    
    PORTC->PCR[PIN2NUM(I2C1_SDA)] = 0;
    PORTC->PCR[PIN2NUM(I2C1_SDA)] |= PORT_PCR_MUX(ALT2);
    PORTC->PCR[PIN2NUM(I2C1_SDA)] |= (PORT_PCR_ODE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
  }

  /*Seteo el baudrate (I2C baud rate = I2C module clock speed (Hz)/(mul × SCL divider))
   *I2C module clock speed (Hz) --> Bus clock --> 50MHz
   *SCL divider --> I2C divider and hold values table --> Pagina 1558 Ref Man
   *ICR = 0x17 --> SCL divider = 128
   *MUL = 2 --> mul = 4
   *Baud Rate = 97656bps
   *CHEQUEAR EN OSCILOSCOPIO QUE TENGA SUFICIENTE HOLD TIME
  */
  I2C_x[i2c_num]->F |= I2C_F_MULT(2);
  I2C_x[i2c_num]->F |= I2C_F_ICR(0x17);

  I2C_x[i2c_num]->C1 |= I2C_C1_IICIE_MASK; //enable interrputs
  I2C_x[i2c_num]->C1 |= I2C_C1_IICEN_MASK; //enable i2c

  if(!num) NVIC_EnableIRQ(I2C0_IRQn);
  else NVIC_EnableIRQ(I2C1_IRQn);
}

void i2cSimpleTransaction(uint8_t address, RW_mode mode, uint8_t bytes, uint8_t* buffer)
{
  rw_mode = mode;
  cant_bytes = bytes;
  data = buffer;
  dev_address = address;

  W_error = false;
  I2C_x[i2c_num]->C1 |= I2C_C1_MST_MASK;  //START
  I2C_x[i2c_num]->C1 |= I2C_C1_TX_MASK;   //TX = 1

  I2C_x[i2c_num]->D = (address<<1) + mode;
}

void i2c_repeat_start(uint8_t address, uint8_t writeBytes, uint8_t* writeBuffer, uint8_t readBytes, uint8_t* readBuffer)
{
  rw_mode = MODE_W;
  cant_bytes = writeBytes;
  R_cant_bytes = readBytes;
  data = writeBuffer;
  Rdata = readBuffer;
  dev_address = address;
  reg_read = true;

  W_error = false;
  I2C_x[i2c_num]->C1 |= I2C_C1_MST_MASK;  //START
  I2C_x[i2c_num]->C1 |= I2C_C1_TX_MASK;   //TX = 1

  I2C_x[i2c_num]->D = (address<<1) + MODE_W;  //address + W/R
}

bool i2c_is_busy(void)
{
  // return (I2C_x[i2c_num]->S & I2C_S_BUSY_MASK);
  return (I2C_x[i2c_num]->C1 & I2C_C1_MST_MASK);
}

bool i2c_write_ok(void)
{
  return !W_error;
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


__ISR__ I2C0_IRQHandler(void)
{
	static bool address_cycle = true;
  I2C0->S |= I2C_S_IICIF_MASK; //clear interrupt flag

  switch(rw_mode)
  {
    case MODE_R:
      //modo Read/RX
      I2C0->C1 &= ~I2C_C1_TX_MASK;  //TX = 0 (Read)
      if(!cant_bytes) //El byte que leí recien era el último?
      {
        I2C0->C1 &= ~I2C_C1_MST_MASK;  //STOP
      }
      else if(cant_bytes == 1)  //Si estoy en el último
      {
        I2C0->C1 |= I2C_C1_TXAK_MASK; //NACK
      }
      else
      {
        I2C0->C1 &= ~I2C_C1_TXAK_MASK;
      }
      *data = I2C0->D;  //Read action
      cant_bytes--;
      if(!address_cycle)
      {
          data++;
      }
      else address_cycle = false;
      break;
    case MODE_W:
      //modo Write/TX
      //I2C0->C1 |= I2C_C1_TX(true);  //No hace falta setearlo porque viene seteado desde el address cycle
      if(!cant_bytes) //El byte que transmití recien era el último?
      {
        if(reg_read)    //Si estoy en Repeat Start
        {
          rw_mode = MODE_R;
          cant_bytes = R_cant_bytes;
          data = Rdata;
          reg_read=false;
          address_cycle = true;
          I2C0->C1 |= I2C_C1_RSTA_MASK;  //RST=1
          //I2C0->C1 &= ~I2C_C1_TX_MASK; //switch to RX (clear TX bit)
          I2C0->D = (dev_address<<1) + MODE_R;  //Mando address para empezar el Read
        }
        else
        {   //Si no estoy en Repeat Start, termina
          I2C0->C1 &= ~I2C_C1_MST_MASK;   //STOP
        }
      }
      else
      {
        if(!(I2C0->S & I2C_S_RXAK_MASK))  //ACK?
        {
          I2C0->D = *data;  //Write action
          data++;
          cant_bytes--;
        }
        else
        {
          if(cant_bytes)  //Si recibio NACK y no termino
          {
            W_error = true; //Levanta flag de error
          }
          I2C0->C1 &= ~I2C_C1_MST_MASK; //STOP
        }
      }
      break;
    default:
    	break;
  }
}
 
__ISR__ I2C1_IRQHandler(void)
{
  I2C1->S |= I2C_S_IICIF_MASK;

  switch(rw_mode)
  {
    case MODE_R:
      //modo Read/RX
      I2C1->C1 &= ~I2C_C1_TX_MASK;  //TX = 0 (Read)
      if(!cant_bytes) //El byte que leí recien era el último?
      {
        I2C1->C1 &= ~I2C_C1_MST_MASK;  //STOP
      }
      else if(cant_bytes == 1)  //Si estoy en el último
      {
        I2C1->C1 |= I2C_C1_TXAK_MASK; //NACK
      }
      *data = I2C1->D;  //Read action
      //data++;   //tiene auto-inc
      cant_bytes--;
      break;
    case MODE_W:
      //modo Write/TX
      //I2C0->C1 |= I2C_C1_TX(true);  //No hace falta setearlo porque viene seteado desde el address cycle
      if(!cant_bytes) //El byte que transmití recien era el último?
      {
        if(reg_read)    //Si estoy en Repeat Start
        {
          I2C1->C1 |= I2C_C1_RSTA_MASK;  //RST=1
          I2C1->C1 &= ~I2C_C1_TX_MASK; //switch to RX (clear TX bit)
          cant_bytes = R_cant_bytes;
          data = Rdata;
          reg_read=false;
          I2C1->D = (dev_address<<1) + MODE_R;  //Mando address para empezar el Read
        }
        else
        {   //Si no estoy en Repeat Start, termina
          I2C1->C1 &= ~I2C_C1_MST_MASK;   //STOP
        }
      }
      else
      {
        if(!(I2C1->S & I2C_S_RXAK_MASK))  //ACK?
        {
          I2C1->D = *data;  //Write action
          data++;
          cant_bytes--;
        }
        else
        {
          if(cant_bytes)  //Si recibio NACK y no termino
          {
            W_error = true; //Levanta flag de error
          }
          I2C1->C1 &= ~I2C_C1_MST_MASK; //STOP
        }
      }
      break;
    default:
    	break;
  }
}
 
