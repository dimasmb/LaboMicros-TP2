/***************************************************************************//**
  @file     DRV_MCP25625.h
  @brief    Driver to manage the interface and comunication with Controller CAN
  @author   Salta
 ******************************************************************************/

#ifndef _DRV_MCP25625_H_
#define _DRV_MCP25625_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "SPI_DRV.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/




/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/**
 * @brief Funcion que inicializa el MCP , sigue un serie de paso detallos en el .c
 * @param se le pasa las configuraciones de Spi , para q te lo inicialice direnctamente alli
 * @return bool
 */
bool Init_MCP (Spi_config_t Spi);


uint32_t Recepcion(void);

bool StarCANTx(uint8_t *data);

bool RecibCANBx(uint8_t *data);

/*******************************************************************************
 ******************************************************************************/

#endif // DRV_MCP25625.h
