/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "DRV_MCP25625.h"

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
//Direcciones configuration de tiempo de bits e Configuraciones Iniciales
#define CNF1	0b00101010 	//configuration de tiempo de bits Baud (<5-0>Rate Prescaler bits)
#define CNF2	0b00101001	//sample point
#define CNF3	0b00101000 //
#define	TXRTSCTRL	0b00001101//
#define Filter1	0b00000000 // 00h, 04h, 08h, 10h, 14h, 18h
#define RXB0CTRL 0b01100000//
#define RXB1CTRL	0b01110000//
#define CANCTRL	0b00001111
#define CANINTF 0b00101100
#define CANINTE 0b00101011//

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
Spi_config_t SpiMCP;       //como lo inicializo? quien lo inicializa
                        //solucion que ya esten creados y que se inicialicen en este archivo.

uint32_t prepare_frame(uint8_t instruccion,uint8_t address,uint8_t data);



/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//todo Necesito una funcion para apagar el Spi.
bool Write_MCP (uint8_t address, uint8_t data){  //instruccion + Direccion+ Data = 1byte +1byte+1byte

   //bool valid= init_SPI (Spi);      // a q registro tengo q escribir? Frame de 23
    //if (valid==true){
    //    write_SPI(SpiMCP,prepare_frame(WRITE,address,data) );
	write_SPI(SpiMCP,WRITE);
	write_SPI(SpiMCP,address) ;
	write_SPI(SpiMCP,data) ;;
	disable_CS(SpiMCP);
    
        //todo Como chequeo que se envio algo bien?
    //}
    return true;
}

uint8_t Read_MCP (uint8_t address){
   // init_SPI(Spi); //frame de 15
	write_SPI(SpiMCP,READ);
	write_SPI(SpiMCP,address);
	write_SPI(SpiMCP,DATASHIT);
	uint8_t lectura=read_SPI(SpiMCP);
	disable_CS(SpiMCP);

    return lectura;   //todo chequear tpos.
}
bool Init_MCP (Spi_config_t Spi){
	if(init_SPI(Spi)){
		SpiMCP=Spi;
		Write_MCP(CANCTRL,0b10000000);
		Write_MCP(CNF1,0b00000111); //mando como dato  un baudrate de 1 y una sincronizacion de cero( SYNCHRONIZATION JUMP WIDTH)
		Write_MCP(CNF2,0b00010101); // 1+5+2+2
		Write_MCP(CNF3,0b00000010);
		Write_MCP(RXB0CTRL,0b01100001);
		Write_MCP(RXB1CTRL,0b01100001);//TODO falta la mascara
		Write_MCP(CANINTF,0b00000000);//RESET ese Regsitro
		Write_MCP(CANINTE,0b11111111);//habilito interrupciones
		Write_MCP(CANCTRL,0b00000000);//lo pongo en modo Normal.*/
		return true;
	}

	return false;
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
