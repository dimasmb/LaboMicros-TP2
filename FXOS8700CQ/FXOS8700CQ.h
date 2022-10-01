/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _FXOS8700CQ_H_
#define _FXOS8700CQ_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
// FXOS8700CQ I2C address
#define FXOS8700CQ_SLAVE_ADDR 0x1D // I2C Addres in Kinetis

// FXOS8700CQ internal register addresses
#define FXOS8700CQ_STATUS 0x00
#define FXOS8700CQ_F_SETUP 0x09
#define FXOS8700CQ_WHOAMI 0x0D
#define FXOS8700CQ_XYZ_DATA_CFG 0x0E
#define FXOS8700CQ_CTRL_REG1 0x2A
#define FXOS8700CQ_M_CTRL_REG1 0x5B
#define FXOS8700CQ_M_CTRL_REG2 0x5C
#define FXOS8700CQ_WHOAMI_VAL 0xC7

// number of bytes to be read from the FXOS8700CQ
#define FXOS8700CQ_READ_LEN 13 // status plus 6 channels = 13 bytes

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} SRAWDATA;

typedef struct
{
  int16_t pitch;
  int16_t roll;
  int16_t yaw;
} angular_data_t;

enum
{
  init_ERROR,
  init_OK
};
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: Inicializa la comunicación con el acelerómetro y el magnetómetro
*/
int accel_mag_init(void);

/**
 * @brief TODO: Inicia la lectura de los valores del acelerómetro y el magnetómetro
*/
void ReadAccelMagnData(void);

/**
 * @brief TODO: Si se terminó la lectura, guarda los valores
 * @param pAccelData Puntero a un SRAWDATA donde se guardan los datos del acelerómetro
 * @param pMagnData Puntero a un SRAWDATA donde se guardan los datos del magnetómetro
 * @return true si pudo leer
*/
bool AccelMagnData_ready(SRAWDATA *pAccelData, SRAWDATA *pMagnData);

/**
 * @brief TODO: Convierte los datos recibidos del acelerómetro y el magnetómetro a ángulos de cabeceo, rolido y orientación
 * @param pAccelData Puntero a un SRAWDATA donde están guardados los datos del acelerómetro
 * @param pMagnData Puntero a un SRAWDATA donde están guardados los datos del magnetómetro
 * @return Un angular_data_t con los angulos
*/
angular_data_t get_angles(SRAWDATA *pAccelData, SRAWDATA *pMagnData);

/*******************************************************************************
 ******************************************************************************/

#endif // _TEMPLATE_H_
