/***************************************************************************//**
  @file     i2cm.h
  @brief    header de driver i2c
  @author   Dimas Bosch
 ******************************************************************************/

#ifndef _I2CM_H_
#define _I2CM_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{
  I2C_0,
  I2C_1
}i2cx;

typedef enum{
  MODE_W,
  MODE_R
}RW_mode;

typedef struct
{
  uint8_t reg;
  RW_mode mode;
  uint32_t bytes;
  uint8_t* buffer;
}single_address_type;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: Inicializa el módulo de I2C
 * @param num número del módulo a inicializar de tipo i2cx
*/
void I2C_init(i2cx num);

/**
 * @brief TODO: Comienza una transacción Read o Write
 * @param address Address del slave al cual quiero escribir/leer
 * @param mode MODE_W (write) / MODE_R (Read)
 * @param bytes cantidad de bytes a escribir/leer
 * @param buffer puntero al buffer donde se guardan los datos leídos o a escribir
*/
void i2cSimpleTransaction(uint8_t address, RW_mode mode, uint8_t bytes, uint8_t* buffer);

/**
 * @brief TODO: Comienza una transacción Write y Read con Repeat Start
 * @param address Address del slave al cual quiero escribir/leer
 * @param writeBytes cantidad de bytes a escribir
 * @param writeBuffer puntero al buffer con los datos a escribir
 * @param readBytes cantidad de bytes a leer
 * @param readBuffer puntero al buffer donde se guardan los datos leídos
*/
void i2c_repeat_start(uint8_t address, uint8_t writeBytes, uint8_t* writeBuffer, uint8_t readBytes, uint8_t* readBuffer);

/**
 * @brief TODO: Chequea si el bus de I2C está ocupado
 * @return true si está ocupado
*/
bool i2c_is_busy(void);

/**
 * @brief TODO: chequea si la escritura se hizo correctamente (reibe ACK)
 * @return true si no hay error. false si hubo error
*/
bool i2c_write_ok(void);
/*******************************************************************************
 ******************************************************************************/

#endif
