/***************************************************************************//**
  @file     DRV_MCP25625.h
  @brief    Driver to manage the interface and comunication with Controller CAN
  @author   Salta
 ******************************************************************************/
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
#define RTSTOSENDT0	0b10000001	//Se define y activa para enviar
#define RTSTOSENDT1	0b10000010
#define RTSTOSENDT2	0b10000100
#define READ_STATUS 0b10100000 //Comando pa chequear bit de estados , todavia no se como se usa bien :todo investigar
#define Bit_modify 0b00000101     //modificar algun bit de estado en partidular.

//Direcciones configuration de tiempo de bits e Configuraciones Iniciales
#define CNF1	0b00101010 	//configuration de tiempo de bits Baud (<5-0>Rate Prescaler bits)
#define CNF2	0b00101001	//sample point
#define CNF3	0b00101000 //

#define Filter1	0b00000000 // 00h, 04h, 08h, 10h, 14h, 18h
//Mask para el buffer 0
#define RXM0SIDH 0b00100000
#define RXM0SIDL 0b00100001
//Filtros pal bffer
#define RXF0SIDH 0b00000000
#define RXF0SIDL 0b00000001

#define RXB0CTRL 0b01100000//
#define RXB1CTRL 0b01110000//

#define CANCTRL	0b00001111
#define CANINTF 0b00101100
#define CANINTE 0b00101011//
//Direcciones buffer para transmitir
#define TXB0CTRL 0b00110000
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0DLC	0x35
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3A

#define	TXRTSCTRL	0b00001101//
//Direcciones buffer para recibit
#define RXB0CTRL 0b01100000//
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0DLC	0x65
#define	RXB0D0	0x66
#define	RXB0D1	0x67
#define	RXB0D2	0x68
#define	RXB0D3	0x69
#define	RXB0D4	0x6A



//ID
#define SIDH 0b10000000 // id high
#define SIDL 0b00000011 //id low


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
Spi_config_t SpiMCP;
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

bool Bit_Modify(uint8_t address,uint8_t Mask,uint8_t bit);
/**
 * @brief Se resetea la configuracion de MCP, es una unica función xq tiene una trama distinta
 * @return bool
 */
bool Reset_MCP(void);

bool CheckTXREQ(void); 	//Funcion para chequear si tengo permitido escribir
bool CheckRx(void);		//Lee si hay algo e el buffer
bool RtsToSend(int buffer);	//Avisa que estamos para enviar.
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static uint32_t array[4];	//Arreglo que se usa para guardar los datos leidos.



bool Init_MCP (Spi_config_t Spi){
	if(init_SPI(Spi)){
		SpiMCP=Spi;
		//Write_MCP(CANCTRL,0b10000000); //TEST de para probar recepcion
		//Read_MCP(0b00001110);
		//Reset_MCP();

		//PASOS PARA LA INICIALIZACION DE LA PLACA CAN
		//SE RETEA Y SE PONE UN MODO CONFIGURACION
		Reset_MCP();
		//CONFIGURACION CON RESPECTO A LOS TPOS DE CONFIGURACION
		Write_MCP(CNF1,0b00000111); //mando como dato  un baudrate de 1 y una sincronizacion de cero( SYNCHRONIZATION JUMP WIDTH)
		Write_MCP(CNF2,0b00010101); // 1+5+2+2
		Write_MCP(CNF3,0b00000010);
		//CONFIGURA PARA QUE EL TX0 ANDE
		Write_MCP(TXRTSCTRL,0b00000001); 	//No lo dice la filmina del Profe, pero si en el datashet ,entonces?
		//CONFIGURACION DE LAS MASCARAS Y FILTROS QUE VAN A ACTUAR SOBRE EL BUFFER RX
		Write_MCP(RXF0SIDH,0b00010000);	//se setea filtro
		Write_MCP(RXF0SIDL,0b00000000);										//filter = 0001 0000 0000 0000 ->Busco que solo empiece con el encabezado 0x100
		Write_MCP(RXM0SIDH,0b11111111);	//Se setea la mascara parte alt		//Mask=    1111 1111 1111 0000 -> con cero no chequea ese bit.
		Write_MCP(RXM0SIDL,0b11110000);	//se setea la mascara parte baja
		//CONFIGURO EL BUFFER DE RECEPCION, ACTIVO MASCARAS Y FILTROS RXF0 Y RXM0
		Write_MCP(RXB0CTRL,0b00000000);//Se activa mask y filter(RXF0),
		Write_MCP(RXB1CTRL,0b00000000);//TODO falta la mascara
		//HABILITO INTERRUPCIONES SOLO SOBRE TX0 Y RX0
		//Write_MCP(CANINTF,0b00000000);//RESET ese Regsitro
		Write_MCP(CANINTE,0b00000101);
		//SE COLOCA EN MODO NORMAL
		Write_MCP(CANCTRL,0b00001000);//lo pongo en modo Normal,ABAT=0,One shot,CLKOUT disable
		return true;
	}

	return false;
}
uint32_t Recepcion(void){
	return(array[2]); //xq son los datos validos de la recepción
}

bool StarCANTx(uint8_t *data){		//solo se puede mandar de a 5 bits
	bool ret=false;
	if(CheckTXREQ()){		//hecho para el tx -> expandir
		Write_MCP(TXB0SIDH,SIDH);	//SIDHigh
		Write_MCP(TXB0SIDH,SIDL);	//SIDLow
		Write_MCP(TXB0DLC,0x05);	//Indica el largo de los frames pa enviar.
		Write_MCP(TXB0D0,data[0]); //se llena de los datos aportados
		Write_MCP(TXB0D1,data[1]);
		Write_MCP(TXB0D2,data[2]);
		Write_MCP(TXB0D3,data[3]);
		Write_MCP(TXB0D4,data[4]);
		ret=RtsToSend(0);		//Mando la peticion pa que se mande en algun momento
	}
	return ret;
}
bool RtsToSend(int buffer){
	bool salida=false;
	switch(buffer){
	case 0:writeyread_SPI(SpiMCP,RTSTOSENDT0);disable_CS(SpiMCP);salida=true;break;
	case 1:writeyread_SPI(SpiMCP,RTSTOSENDT1);disable_CS(SpiMCP);salida=true;break;
	case 2:writeyread_SPI(SpiMCP,RTSTOSENDT2);disable_CS(SpiMCP);salida=true;break;
	default:salida=false; break;
	}
	return salida;
}
bool RecibCANBx(uint8_t *data){
	bool salida=false;
	int i=0;
	if(i==CheckRx()){
		data[0]=Read_MCP(RXB0SIDH);
		data[1]=Read_MCP(RXB0SIDL);
		data[2]=Read_MCP(RXB0DLC);
		data[3]=Read_MCP(RXB0D0);
		data[4]=Read_MCP(RXB0D1);
		data[5]=Read_MCP(RXB0D2);
		data[6]=Read_MCP(RXB0D3);
		data[7]=Read_MCP(RXB0D4);
		Bit_Modify(CANINTF,0b00000001,0b00000000);
		salida=true;
	}
	return salida;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
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

uint32_t Read_MCP (uint8_t address){
   	array[0]=writeyread_SPI(SpiMCP,READ);
	array[1]=writeyread_SPI(SpiMCP,address);
	array[2]=writeyread_SPI(SpiMCP,DATASHIT);
	array[3]=read_SPI(SpiMCP);
	disable_CS(SpiMCP);
    return (array[2]);
}

bool CheckTXREQ(void){
	bool ret =true;
	uint8_t tx_register=Read_MCP(TXB0CTRL);		//todo posible error
	uint8_t tem=tx_register;
	if(8==(tem<<5)){
		ret= false;
	}
	return ret;
}
bool CheckRx(void){
	bool salida=false;
	uint8_t rx_register=Read_MCP(CANINTF);
	uint8_t tem=rx_register;
	if(8==(tem<<7)){
		salida= true;
	}

	return salida;
}

/*******************************************************************************
 ******************************************************************************/
