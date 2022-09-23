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



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{
  I2C0_SCL_ACC = PORTNUM2PIN(5, 24),
  I2C0_SDA_ACC = PORTNUM2PIN(5, 25),
  I2C0_SCL_EXT = PORTNUM2PIN(2, 2),
  I2C0_SDA_EXT = PORTNUM2PIN(2, 3),
  I2C1_SCL = PORTNUM2PIN(2, 10),
  I2C1_SDA = PORTNUM2PIN(2, 11),
};

// typedef enum{
//   START,
//   REP_START,


// } state_t;


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
static bool rstart = false;
static uint32_t cant_bytes;
static uint8_t* data;
//static uint8_t* Wdata;
static uint8_t* Rdata;
//static uint8_t W_cant_bytes;
static uint8_t R_cant_bytes;
static bool W_error = false;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void init_I2C(i2cx num)
{
  SIM->SCGC4 |= (1<<(6+num)); //clock gating
  i2c_num = num;

  //configuro los pines
  if(!num)
  {
    //Para el I2C0, configuro los pines PTE24 y 25 que son los del acelerómetro
    PORTB->PCR[I2C0_SCL_ACC] = 0;
    PORTB->PCR[I2C0_SCL_ACC] |= PORT_PCR_MUX(5);
    
    PORTB->PCR[I2C0_SDA_ACC] = 0;
    PORTB->PCR[I2C0_SDA_ACC] |= PORT_PCR_MUX(5);

    //configuro los pines PTB2 y 3 para veros externamente
    PORTB->PCR[I2C0_SCL_EXT] = 0;
    PORTB->PCR[I2C0_SCL_EXT] |= PORT_PCR_MUX(2);
    
    PORTB->PCR[I2C0_SDA_EXT] = 0;
    PORTB->PCR[I2C0_SDA_EXT] |= PORT_PCR_MUX(2);
  }
  else
  {
    //Para el I2C0, configuro los pines PTC10 y 11
    PORTC->PCR[PIN2NUM(I2C1_SCL)] = 0;
    PORTC->PCR[PIN2NUM(I2C1_SCL)] |= PORT_PCR_MUX(2);
    
    PORTC->PCR[PIN2NUM(I2C1_SDA)] = 0;
    PORTC->PCR[PIN2NUM(I2C1_SDA)] |= PORT_PCR_MUX(2);
  }

  /*Seteo el baudrate (I2C baud rate = I2C module clock speed (Hz)/(mul × SCL divider))
   *I2C module clock speed (Hz) --> Bus clock --> 50MHz
   *SCL divider --> I2C divider and hold values table --> Pagina 1558 Ref Man
   *ICR = 0x17 --> SCL divider = 128
   *MUL = 0 --> mul = 1
   *Baud Rate = 390625bps
   *CHEQUEAR EN OSCILOSCOPIO QUE TENGA SUFICIENTE HOLD TIME
  */
  I2C_x[i2c_num]->F |= I2C_F_MULT(0);
  I2C_x[i2c_num]->F |= I2C_F_ICR(0x17);

  I2C_x[i2c_num]->C1 |= I2C_C1_IICIE(true); //enable interrputs
  I2C_x[i2c_num]->C1 |= I2C_C1_IICEN(true); //enable i2c

  if(!num) NVIC_EnableIRQ(I2C0_IRQn);
  else NVIC_EnableIRQ(I2C1_IRQn);
}

void i2cSimpleTransaction(uint8_t address, RW_mode mode, uint8_t bytes, uint8_t* buffer)
{
  rw_mode = mode;
  cant_bytes = bytes;
  data = buffer;

  W_error = false;
  I2C_x[i2c_num]->C1 |= I2C_C1_MST(true);
  I2C_x[i2c_num]->C1 |= I2C_C1_TX(true);

  I2C_x[i2c_num]->D = (address<<1) + mode;
}

void i2cWandRTransaction(uint8_t address, uint8_t writeBytes, uint8_t* writeBuffer, uint8_t readBytes, uint8_t* readBuffer)
{
  cant_bytes = writeBytes;
  R_cant_bytes = readBytes;
  data = writeBuffer;
  Rdata = readBuffer;
  rstart = true;

  W_error = false;
  I2C_x[i2c_num]->C1 |= I2C_C1_MST(true);
  I2C_x[i2c_num]->C1 |= I2C_C1_TX(true);

  I2C_x[i2c_num]->D = (address<<1) + MODE_W;
}

bool i2c_is_busy(void)
{
  return (I2C_x[i2c_num]->S & I2C_S_BUSY_MASK);
}

bool i2c_write_check(void)
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
  I2C0->S |= I2C_S_IICIF(true); //clear interrupt flag

  switch(rw_mode)
  {
    case MODE_R:
      //modo Read/RX
      I2C0->C1 |= I2C_C1_TX(false);
      if(!cant_bytes) //El byte que leí recien era el último?
      {
        I2C0->C1 |= I2C_C1_MST(false);
      }
      else if(cant_bytes == 1)  //Si estoy en el último
      {
        I2C0->C1 |= I2C_C1_TXAK_MASK; //seteo como NACK
      }
      *data = I2C0->D;  //Read
      //data++;
      cant_bytes--;
      break;
    case MODE_W:
      //modo Write/TX
      //I2C0->C1 |= I2C_C1_TX(true);  //No hace falta setearlo porque viene seteado desde el address cycle
      if(!cant_bytes) //El byte que transmití recien era el último?
      {
        if(rstart)
        {
          I2C0->C1 |= I2C_C1_RSTA_MASK;  //RST=1
          I2C0->C1 |= I2C_C1_TX(false); //switch to RX
          cant_bytes = R_cant_bytes;
          data = Rdata;
          rstart=false;
        }
        else
        {
          I2C0->C1 |= I2C_C1_MST(false);
        }
      }
      else
      {
        if(!(I2C0->S & I2C_S_RXAK_MASK))
        {
          I2C0->D = *data;  //Write
          data++;
          cant_bytes--;
        }
        else
        {
          if(cant_bytes)
          {
            W_error = true;
          }
          I2C0->C1 |= I2C_C1_MST(false);
        }
      }
      break;
    default:
    	break;
  }
}
 
__ISR__ I2C1_IRQHandler(void)
{
  I2C1->S |= I2C_S_IICIF(true);

  if(rw_mode)
   {
     //modo Read/RX
     I2C1->C1 |= I2C_C1_TX(false);
     if(!cant_bytes) //El byte que leí recien era el último?
     {
       I2C1->C1 |= I2C_C1_MST(false);
     }
     else if(cant_bytes == 1)  //Si estoy en el último
     {
       I2C1->C1 |= I2C_C1_TXAK_MASK; //seteo como NACK
     }
     *data = I2C1->D;  //Read
     data++;
     cant_bytes--;
   }
   else
   {
     //modo Write/TX
     //I2C0->C1 |= I2C_C1_TX(true);  //No hace falta setearlo porque viene seteado desde el address cycle
     if(!cant_bytes) //El byte que transmití recien era el último?
     {
       I2C1->C1 |= I2C_C1_MST(false);
     }
     else
     {
       if(!(I2C1->S & I2C_S_RXAK_MASK))
       {
         I2C1->D = *data;  //Write
         data++;
         cant_bytes--;
       }
       else
       {
         I2C1->C1 |= I2C_C1_MST(false);
       }
     }

   }
}
 
