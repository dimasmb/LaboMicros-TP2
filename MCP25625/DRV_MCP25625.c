/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "DRV_MCP25625.h"
#include "SPI_DRV.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define DATASHIT 0b00000000 //define usada pa rellenar
//Instruccion
#define WRITE 0b11000000
#define READ  0b00000011
#define RESET 0b11000000 
#define READ_STATUS 0b10100000 //Comando pa chequear bit de estados , todavia no se como se usa bien :todo investigar
#define Bit_modify 0b00000101     //modificar algun bit de estado en partidular.





/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
Spi_config_t Spi;       //como lo inicializo? quien lo inicializa
                        //solucion que ya esten creados y que se inicialicen en este archivo.
uint32_t prepare_frame(uint8_t instruccion,uint8_t address,uint8_t data);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//todo Necesito una funcion para apagar el Spi.
bool Write_MCP (uint8_t address, uint8_t data){  //instruccion + Direccion+ Data = 1byte +1byte+1byte
   bool valid= init_SPI (Spi);      // a q registro tengo q escribir? Frame de 23
    if (valid==true){
        valid=write_SPI(Spi,prepare_frame(WRITE,address,data) );
        //todo Como chequeo que se envio algo bien?
    }
    return false
}

uint8_t Read_MCP (uint8_t address){
    init_SPI(Spi); //frame de 15
    bool valid= write_SPI(Spi,prepare_frme(READ,address,DATASHIT));
    return read_SPI(Spi);   //todo chequear tpos.
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
uint32_t prepare_frame(uint8_t instruccion,uint8_t address,uint8_t data){ //enviar MSB
    uint32_t frame=data;
    uint32_t address_aux=address;
    uint32_t instr=instruccion;
    frame= (frame)|(address_aux<<8);
    frame=(frame)|(instr<<16);
    return(frame);
}

/*******************************************************************************
 ******************************************************************************/
