/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "DRV_MCP25625.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define DATASHIT 0b00000000 //define usada pa rellenar
//Instruccion
#define WRITE 0b00000010
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
Spi_config_t SpiMCP;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static uint32_t array[4];	//Arreglo que se usa para guardar los datos leidos.
bool Reset_MCP(){
	writeyread_SPI(SpiMCP,RESET);
	disable_CS(SpiMCP);
	return true;
}

bool Write_MCP (uint8_t address, uint8_t data){  //instruccion + Direccion+ Data = 1byte +1byte+1byte
	writeyread_SPI(SpiMCP,WRITE);		//se de 8bits
	writeyread_SPI(SpiMCP,address);
	writeyread_SPI(SpiMCP,data);
	disable_CS(SpiMCP);					//se levanta el cs
    return true;
}
bool Bit_Modify(uint8_t address,uint8_t Mask,uint8_t bit){
	writeyread_SPI(SpiMCP,0b00000101);
	writeyread_SPI(SpiMCP,address);
	writeyread_SPI(SpiMCP,Mask);
	writeyread_SPI(SpiMCP,bit);
	disable_CS(SpiMCP);
	return true;
}


uint8_t Read_MCP (uint8_t address){
   	array[0]=writeyread_SPI(SpiMCP,READ);
	array[1]=writeyread_SPI(SpiMCP,address);
	array[2]=writeyread_SPI(SpiMCP,DATASHIT);
	array[3]=read_SPI(SpiMCP);
	disable_CS(SpiMCP);
    return 1;
}
bool Init_MCP (Spi_config_t Spi){
	if(init_SPI(Spi)){
		SpiMCP=Spi;
		//PASOS PARA LA INICIALIZACION DE LA PLACA CAN
		Reset_MCP();
		Write_MCP(CANCTRL,0b10000000); //TEST de para probar recepcion
		Read_MCP(0b00001110);
		Reset_MCP();
		Write_MCP(CNF1,0b00000111); //mando como dato  un baudrate de 1 y una sincronizacion de cero( SYNCHRONIZATION JUMP WIDTH)
		Write_MCP(CNF2,0b00010101); // 1+5+2+2
		Write_MCP(CNF3,0b00000010);
		Write_MCP(RXB0CTRL,0b01100001);
		Write_MCP(RXB1CTRL,0b01100001);//TODO falta la mascara
		Write_MCP(CANINTF,0b00000000);//RESET ese Regsitro
		Write_MCP(CANINTE,0b11111111);//habilito interrupciones
		Write_MCP(CANCTRL,0b00000000);//lo pongo en modo Normal.*/
		//printf("%x\n",array[0]);
		//printf("%x\n",array[1]);
		//printf("%x\n",array[2]);
		//printf("%x\n",array[3]);
		return true;
	}

	return false;
}
uint32_t Recepcion(void){
	return(array[2]); //xq son los datos validos de la recepción
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
