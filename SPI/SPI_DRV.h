/***************************************************************************//**
  @file     SPI_DRV.h
  @brief    Spi's Driver
  @author   Salta
 ******************************************************************************/

#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "gpio.h" //va en el c

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/




/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{	//modos de Spi
	Slave,
	Master,//Tiene atributos especiales como controlar el clock
	Disable,
}Mode_Spi_t;

typedef enum{	//hay 3 modulos de Spi en FRDM //TODO  si bien son 3 o toy flayando nazi
	spi_0,
	spi_1,
	spi_2,
}Module_Spi_t;

typedef struct {
	Mode_Spi_t mode;
	Module_Spi_t module_spi;
	uint8_t FMSZ;//investigar que es
	uint8_t PCS; //chip select  // solo hay  4 pcs posibles
	bool PCSIS;// indica si es activo alto o bajo , ejplo si le ponemos high es activo bajo
	bool DBR; //double Baud Rate o es clocl de 50/50
	bool CPOL;//Clock polarity , tiene que estar con la misma polaridad
	bool CPHA; //clock phase
	bool LSBFE; //si es 0 MSB primero ,1 al reves
	bool CONT_CLK; //activa un clock continuo. Es activo Bajo
	uint8_t PBR; //baud Rate Prescaler tiene 2 bits.
}Spi_config_t;
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Se inicializa el modulo Spi de la MCU ,con todos los parametros aportados por el usuario
 * @param Se le pasa una variable tipo Spi_config_t.
 * @return bool , true en el caso de ser exitosa
 */
bool init_SPI (Spi_config_t Spi);

/**
 * @brief Función que escribe y lee
 * @param se le pasa Spi_config_t y el mensaje a transmitir .
 * @return void
 */
uint8_t  writeyread_SPI(Spi_config_t Spi, uint16_t msg );	//todo : Arreglar el void

/**
 * @brief Se inicializa el modulo Spi de la MCU ,con todos los parametros aportados por el usuario
 * @param Se le pasa una variable tipo Spi_config_t.
 * @return bool , true en el caso de ser exitosa
 */
uint32_t read_SPI(Spi_config_t Spi);

/**
 * @brief Funcion para deshabilitar el cs de la transmición
 * @param Se le pasa le spi
 */
void disable_CS(Spi_config_t Spi);
bool SPI_TransferComplet(Spi_config_t Spi);//todo chequear pa eliminar



/*******************************************************************************
 ******************************************************************************/

#endif // _TEMPLATE_H_
