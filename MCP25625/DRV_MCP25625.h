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
//agregar libreria que incluye uint8_t
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
uint8_t Read_MCP (uint8_t address); //ojo como informo si se leyo erroneamente? -> pasar lugar a donde escribir y el return dejar pa chequear

/**
 * @brief Configures the specified pin to behave either as an input or an output
 * @param pin the pin whose mode you wish to set (according PORTNUM2PIN)
 * @param mode INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN.
 */
void FuncionEXTra_MCP (pin_t pin, uint8_t mode);



/*******************************************************************************
 ******************************************************************************/

#endif // DRV_MCP25625.h
