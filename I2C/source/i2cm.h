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


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
void init_I2C(i2cx num);

void i2cSimpleTransaction(uint8_t address, RW_mode mode, uint8_t bytes, uint8_t* buffer);
void i2cWandRTransaction(uint8_t address, uint8_t writeBytes, uint8_t* writeBuffer, uint8_t readBytes, uint8_t* readBuffer);



/*******************************************************************************
 ******************************************************************************/

#endif
