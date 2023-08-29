/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "FXOS8700CQ.h"
#include "SysTick.h"
#include <math.h>
#include "i2cm.h"
// +Incluir el header propio (ej: #include "template.h")+
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+
static uint8_t Buffer[FXOS8700CQ_READ_LEN]; // read buffer
static bool reading = false;
static angular_data_t prev_ang;
/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+

static void delay(void);
static void resetDelay(void);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
// function configures FXOS8700CQ combination accelerometer and magnetometer sensor 
int accel_mag_init(void)
{
  I2C_init(I2C_0);
  static uint8_t databyte;
  static uint8_t reg8;

  //*********************START RESET****************************************
  /*******************
  //ACCELEROMETER CONTROL REG2
  ***************************/
  // write 0100 0000 = 0x00 to accelerometer control register 2 for reset
  //The host application should allow 1 ms between issuing a software (setting rst bit) or hardware (pulsing RST
  //pin) reset and attempting communications with the device over the I2C or SPI interfaces.
  //Note: The I2C and SPI communication systems are also reset to avoid corrupted data transactions. On
  //issuing a software reset command over an I2C interface, the device immediately resets and does not send
  //any acknowledgment (ACK) of the written byte to the master. The host application has to implement the I2C
  //driver in such a way that it does not look for an ACK following a soft reset command.
  databyte = 0x40;
  uint8_t reg16[] = {FXOS8700CQ_CTRL_REG2, databyte};
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  resetDelay();

  //*************************************************************
  /*******************
  //MAGNETOMETER CONTROL REG1
  ***********************************/
  // write 0101 1111 = 0x1F to magnetometer control register 1
  // [7]: m_acal=0 --> auto calibration disabled
  // [6]: m_rst=1 --> one-shot magnetic reset
  // [5]: m_ost=0 --> no one-shot magnetic measurement
  // [4-2]: m_os=111=7 --> Oversample Ratio (OSR) 2x oversampling (for 800Hz) to reduce magnetometer noise
  // [1-0]: m_hms=11=3 --> select hybrid mode with accel and magnetometer activ
  
  databyte = 0x5F;
  reg16[0] = FXOS8700CQ_M_CTRL_REG1;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, reg16);
  while(i2c_is_busy());
  resetDelay();
  //*********************RESET FINISHED****************************************
  
  /* **************************
    read and check the FXOS8700CQ WHOAMI register
  *********************/
  reg8 = FXOS8700CQ_WHOAMI;
  i2c_repeat_start((uint8_t)FXOS8700CQ_SLAVE_ADDR, 1, &reg8, 1, &databyte);
  while(i2c_is_busy());
  delay();
  if((!i2c_write_ok()) || (databyte != FXOS8700CQ_WHOAMI_VAL))
  {
    return (init_ERROR);
  }
  
  //*************************************************************
  /*******************
  //ACCELEROMETER CONTROL REG1
  ***************************/
  // write 0000 0000 = 0x00 to accelerometer control register 1 to place FXOS8700CQ into
  // standby (must be in standby mode for config)
  // [7-1] = 0000 000 --> Sleep Rate: 50Hz ; Output Data Rate (ODR): 800Hz (400Hz for Hybrid)
  // [0]: active = 0 --> stanby mode
  databyte = 0x00;
  reg16[0] = FXOS8700CQ_CTRL_REG1;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  delay();

 /*******************
  //MAGNETOMETER CONTROL REG1
  ***********************************/
  // write 0001 1111 = 0x1F to magnetometer control register 1
  // [7]: m_acal=0 --> auto calibration disabled
  // [6]: m_rst=0 --> no one-shot magnetic reset
  // [5]: m_ost=0 --> no one-shot magnetic measurement
  // [4-2]: m_os=111=7 --> Oversample Ratio (OSR) 2x oversampling (for 800Hz) to reduce magnetometer noise
  // [1-0]: m_hms=11=3 --> select hybrid mode with accel and magnetometer active
  /*
  When m_hms[1:0] = 2'b11,
  magnetic output data is available in registers:
  M_OUT_X_MSB(0x33), M_OUT_X_LSB (0x34), M_OUT_Y_MSB (0x35), M_OUT_Y_LSB (0x36), M_OUT_Z_MSB (0x37), and M_OUT_Z_LSB (0x38) 
  along with the time synchronized accelerometer data in:
  CMP_X_MSB (0x39), CMP_X_LSB (0x3A), CMP_Y_MSB (0x3B), CMP_Y_LSB (0x3C), CMP_Z_MSB (0x3D), and CMP_Z_LSB (0x3E).
  */
  databyte = 0x1F;
  reg16[0] = FXOS8700CQ_M_CTRL_REG1;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, reg16);
  while(i2c_is_busy());
  delay();

  /*******************
  //MAGNETOMETER CONTROL REG2
  ************************************/
  // write 0010 0000 = 0x20 to magnetometer control register 2
  // [7]: reserved
  // [6]: reserved
  // [5]: hyb_autoinc_mode=1 --> to map the magnetometer registers to follow the accelerometer registers
  // [4]: m_maxmin_dis = 0 --> to retain default min/max latching even though not used
  // [3]: m_maxmin_dis_ths=0 --> No impact to magnetic min/max detection function on a magnetic threshold event
  // [2]: m_maxmin_rst=0 --> No reset sequence is active
  // [1-0]: m_rst_cnt=00 --> to enable magnetic reset each cycle
  databyte = 0x20;
  reg16[0] = FXOS8700CQ_M_CTRL_REG2;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  delay();

  //*************************************************************
  /*******************/
  // write 0000 0001= 0x01 to XYZ_DATA_CFG register
  // [7]: reserved
  // [6]: reserved
  // [5]: reserved
  // [4]: hpf_out=0 --> high-pass filter disabled (eliminates low freq changes)
  // [3]: reserved
  // [2]: reserved
  // [1-0]: fs=01 --> for accelerometer range of +/-4g range with 0.488mg/LSB
  databyte = 0x01;
  reg16[0] = FXOS8700CQ_XYZ_DATA_CFG;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  delay();

    //*************************************************************
  /*******************/
  // write 0000 0000= 0x00 to F_SETUP register
  // [1-0]: f_mode = 0 --> FIFO disabled
  databyte = 0x00;
  reg16[0] = FXOS8700CQ_F_SETUP;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  delay();

  //*************************************************************
  /*******************
  //ACCELEROMETER CONTROL REG1
  *************************/
  // write 0000 1101 = 0x0D to accelerometer control register 1
  // [7-6]: aslp_rate=00
  // [5-3]: dr=001 --> for 200Hz data rate (when in hybrid mode)
  // [2]: lnoise=1 --> for low noise mode
  // [1]: f_read=0 --> for normal 16 bit reads
  // [0]: active=1 --> to take the part out of standby and enable sampling
  databyte = 0x0D;
  reg16[0] = FXOS8700CQ_CTRL_REG1;
  reg16[1] = databyte;
  i2cSimpleTransaction((uint8_t)FXOS8700CQ_SLAVE_ADDR, MODE_W, 2, &(reg16[0]));
  while(i2c_is_busy());
  delay();

  prev_ang.pitch = 0;
  prev_ang.roll = 0;
  // normal return
  return (init_OK);
}

// read status and the three channels of accelerometer and magnetometer data from FXOS8700CQ (13 bytes)
void read_accel_data(void)
{
  static uint8_t reg = FXOS8700CQ_STATUS;
  // read FXOS8700CQ_READ_LEN=13 bytes (status byte and the six channels of data)
  if(!reading)
  {
	  i2c_repeat_start((uint8_t)FXOS8700CQ_SLAVE_ADDR, 1, &reg, FXOS8700CQ_READ_LEN, &Buffer[0]);
	  reading = true;
  }

  /*
  The DR_STATUS registers, OUT_X_MSB, OUT_X_LSB, OUT_Y_MSB, OUT_Y_LSB,
  OUT_Z_MSB, and OUT_Z_LSB are located in the auto-incrementing address range of
  0x00 to 0x06, allowing all of the acceleration data to be read in a single-burst read of six
  bytes starting at the OUT_X_MSB register. If the device is operating in hybrid mode and
  M_CTRL_REG2[hyb_autoinc_mode] = 1, the magnetometer data can also be read out in
  the same axis and endian order by executing a burst read of 12 bytes starting at register
  OUT_X_MSB.  
  */
}

bool is_accel_data_ready(SRAWDATA *pAccelData, SRAWDATA *pMagnData)
{
  if((!i2c_is_busy()) && reading)
  {
	reading = false;
    // copy the 14 bit accelerometer byte data into 16 bit words
    pAccelData->x = (int16_t)(((Buffer[1] << 8) | Buffer[2]))>> 2;
    pAccelData->y = (int16_t)(((Buffer[3] << 8) | Buffer[4]))>> 2;
    pAccelData->z = (int16_t)(((Buffer[5] << 8) | Buffer[6]))>> 2;

    // copy the magnetometer byte data into 16 bit words
    pMagnData->x = (Buffer[7] << 8) | Buffer[8];
    pMagnData->y = (Buffer[9] << 8) | Buffer[10];
    pMagnData->z = (Buffer[11] << 8) | Buffer[12];

    return true;
  }
  else return false;
  
}

angular_data_t raw_2_angles(SRAWDATA *pAccelData, SRAWDATA *pMagnData)
{
  angular_data_t data_ang;
  data_ang.roll = 180 * atan(pAccelData->x/ sqrt(pAccelData->y*pAccelData->y + pAccelData->z*pAccelData->z))/M_PI;
  data_ang.pitch = 180 * atan(pAccelData->y/ sqrt(pAccelData->x*pAccelData->x + pAccelData->z*pAccelData->z))/M_PI;

  //data_ang.roll = (180/M_PI) * atan2(pAccelData->x, pAccelData->z);
  //data_ang.pitch = (180/M_PI) * atan2(pAccelData->y, sqrt(pAccelData->x*pAccelData->x + pAccelData->z*pAccelData->z));

  int16_t mag_x = pMagnData->x*cos(data_ang.roll) + pMagnData->y*sin(data_ang.pitch)*sin(data_ang.roll) + pMagnData->z*cos(data_ang.pitch)*sin(data_ang.roll);
  int16_t mag_y = pMagnData->y * cos(data_ang.pitch) - pMagnData->z * sin(data_ang.pitch);
  data_ang.yaw = 180 * atan(-mag_y/mag_x)/M_PI;
  /*
  If in Quadrant 1 = arctan (AX/AY)
  If in Quadrant 2 = arctan (AX/AY) + 180
  If in Quadrant 3 = arctan (AX/AY) + 180
  If in Quadrant 4 = arctan (AX/AY) + 360
  */

  if(pAccelData->z <0)
  {
    if((pAccelData->x > 0))
    {
      data_ang.roll = 180 - abs(data_ang.roll);
    }
    else
    {
      data_ang.roll = abs(data_ang.roll) - 179;
    }

  }

  return data_ang;
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delay(void)
{
	int cont=100;
	while(cont)
	{
	  cont--;
	}
}

static void resetDelay(void)
{
	int cont=10000;
	while(cont)
	{
	  cont--;
	}
}

 
