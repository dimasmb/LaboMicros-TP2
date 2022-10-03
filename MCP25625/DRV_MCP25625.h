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
 * @brief Write any register of the Controller Can.
 * @param address Address of register that i am going to write
 * @param data Information that i´m going to trasmit
 * @return if the access was successfull, it return true. Else false
 */
bool Write_MCP (uint8_t address, uint8_t data);
/**
 * @brief Read any register of the controller can
 * @param address Address of register that i am going to write
 * @return information of the register request 
 */
uint32_t Read_MCP (uint8_t address); //ojo como informo si se leyo erroneamente? -> pasar lugar a donde escribir y el return dejar pa chequear

/**
 * @brief Funcion que inicializa el MCP , sigue un serie de paso detallos en el .c
 * @param se le pasa las configuraciones de Spi , para q te lo inicialice direnctamente alli
 * @return bool
 */
bool Init_MCP (Spi_config_t Spi);
/**
 * @brief Se resetea la configuracion de MCP, es una unica función xq tiene una trama distinta
 * @return bool
 */
bool Reset_MCP(void);



bool Bit_Modify(uint8_t address,uint8_t Mask,uint8_t bit);

/**
 * @brief	Funcion para acceder a los datos
 * @return datos mandados desde placa Can
 */
uint32_t Recepcion(void);

bool StarCANTx(uint8_t *data);

bool RecibCANBx(uint8_t *data);

/*******************************************************************************
 ******************************************************************************/

#endif // DRV_MCP25625.h
