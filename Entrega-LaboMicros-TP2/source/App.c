/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "uart_drv.h"
#include <string.h>
#include "i2cm.h"
#include "timer.h"
#include "FXOS8700CQ.h"
#include "SPI_DRV.h"
#include "DRV_MCP25625.h"




/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define STATION_NUM 6

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);
void create_pc_string(int cant, char*out_str);
void create_send_string(char*out_str);
void printUartData();
void package_own_data(void);
int send_own_info(void);
int receive_info(void);
void decodeMessage(int groupnum, char* array);
int power(int pow, int num);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{

	//init_I2C(I2C_0);
	int a = accel_mag_init();
	while(a == init_ERROR)
	{
		a = accel_mag_init();
	}
	UART_Init();
	timerInit();
	timerStart(timerGetId(), TIMER_MS2TICKS(30), TIM_MODE_PERIODIC, printUartData);

//CONFIGURACION NECESARIA PARA QUE SE COMUNIQUE BIEN CON LA PLACA CAN
	//IMPORTANTE MODO 0,0(CPOL=0,CPHA=0)

	Spi_config_t Spi;
	Spi.module_spi=spi_0;
	Spi.mode=Master;
	Spi.PCS=0;		//elijo el Spi Modulo 0
	Spi.DBR=0;
	Spi.FMSZ=7;		//Elijo un frame size de 7 , en realidad es 7+1
	Spi.PCSIS=1; 	//el estado inactivo es el alto, lo pide la placa CAN
	Spi.LSBFE=0;	//Bit mas significativo primero en salir MSB
	Spi.CPOL=0;		//cuando es 1 el estado inactivo del clock es el high
	Spi.CPHA=0; 	//los datos se guardan en el flanco de suida
	Spi.PBR=0b00;	//Prescalar Baundrate.
	Spi.CONT_CLK =true;	//Continuous Clock , con true esta desactivado.
	//init_SPI(Spi);		//Se puede inicializar solo Spi sin la placa can
	Init_MCP(Spi);			//se inicializa Spi y ademas la placa CAN

	//timerStart(timerGetId(), TIMER_MS2TICKS(1000), TIM_MODE_PERIODIC, sendData);
	//initTransciever();
	//initAccel();
	//initUART();
	//delayLoop(10000000UL);

}

/* Función que se llama constantemente en un ciclo infinito */


static char numerstring[4*3*STATION_NUM+1];
static int numbers [3*STATION_NUM]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void App_Run (void)
{

		package_own_data();
		create_pc_string(3*STATION_NUM, numerstring);
		send_own_info();
		receive_info();

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void package_own_data(){

	static SRAWDATA accel;
	static SRAWDATA magn;
	static angular_data_t angs;
	read_accel_data();
	int a = is_accel_data_ready(&accel, &magn);
	if (a)
	{
		angs = raw_2_angles(&accel, &magn);

	}
	numbers[0+2*3]=angs.roll;
	numbers[1+2*3]=angs.pitch;
	numbers[2+2*3]=0;

}

static void delayLoop(uint32_t veces)
{
    while (veces--);
}

void printUartData(){
	UART_Send_Data(numerstring, 4*3*STATION_NUM+1);
}

void create_pc_string(int cant, char*out_str){

    char* currChar = out_str;
    int digit1, digit2, digit3;
    *currChar='-';
    currChar++;

    for(int i=0; i<cant; i++){
        if((*(numbers+i))>=0){
        	*currChar='P';
        }
        else{
        	*currChar='N';
        	(*(numbers+i)) = -(*(numbers+i));
        }

        digit1=(*(numbers+i))/100;
        digit2=(*(numbers+i))/10-digit1*10;
        digit3=(*(numbers+i))-digit1*100-digit2*10;

        *(currChar+1)=digit1+'0';
        *(currChar+2)=digit2+'0';
        *(currChar+3)=digit3+'0';
        currChar = currChar+4;
    }

    *currChar='\0';
    return;
}

void create_send_string(char*out_str){

    char* currChar = out_str;
    int digit1, digit2, digit3;

    for(int i=0; i<3; i++){

		switch(i){

			case 0:
				*(currChar)='R';
				break;
			case 1:
				*(currChar)='C';
				break;
			case 2:
				*(currChar)='O';
				break;
		}

    	if((*(numbers+i))>=0){
        	*(currChar+1)='+';
        }
        else{
        	*(currChar+1)='-';
        	(*(numbers+i)) = -(*(numbers+i));
        }

        digit1=(*(numbers+i))/100;
        digit2=(*(numbers+i))/10-digit1*10;
        digit3=(*(numbers+i))-digit1*100-digit2*10;

        *(currChar+2)=digit1+'0';
        *(currChar+3)=digit2+'0';
        *(currChar+4)=digit3+'0';
        currChar = currChar+5;
    }

    *currChar='\0';
    return;
}

int send_own_info(void){
	static char message[15];

	create_send_string(message);

	static char message_1[5];
	static char message_2[5];
	static char message_3[5];

	for(int i=0; i<5; i++){
		message_1[i] = message[i];
	}
	StarCANTx(message_1);
	for(int i=5; i<10; i++){
		message_2[i] = message[i+5];
	}
	StarCANTx(message_2);
	for(int i=10; i<15; i++){
		message_3[i] = message[i+10];
	}
	StarCANTx(message_3);

	return 1;
}
int receive_info(void){
	static char message[8];
	if(RecibCANBx(message)){
		char groupnum = message[1];
		char cant_chars = message[2];

		decodeMessage(groupnum, message+2);
	}


	return 1;
}

void decodeMessage(int groupnum, char* array) {
	int sign = 1;
	int cant_bits;

	cant_bits = array[0];

	char reading_number;
	int R_num = 0;
	int C_num = 0;
	int O_num = 0;

	int r_flag = 0;
	int c_flag = 0;
	int o_flag = 0;


	for (int i = 1; i <= cant_bits; i++) {
		if (array[i] == 'R') {
			r_flag = 1;
			int offset;
			if (array[i + 1] == '-') {
				sign = -1;
				offset = 1;
			}
			else if (array[i + 1] == '+') {
				sign = 1;
				offset = 1;
			}
			else {
				sign = 1;
				offset = 0;
			}
			int counter = 0;

			for (int f = i + offset + 1; array[f] <= '9' && f != cant_bits + 1; f++) {
				counter++;
			}
			int pow_count = counter-1;
			for (int j = i + offset + 1; j < i+ counter + offset +1; j++) {
				R_num += power(pow_count, 10) * (array[j]-'0');
				pow_count--;
			}
			R_num *= sign;
			i += offset + counter;
		}
		else if (array[i] == 'C') {
			c_flag = 1;
			int offset;
			if (array[i + 1] == '-') {
				sign = -1;
				offset = 1;
			}
			else if (array[i + 1] == '+') {
				sign = 1;
				offset = 1;
			}
			else {
				sign = 1;
				offset = 0;
			}
			int counter = 0;

			for (int f = i + offset + 1; array[f] <= '9' && f != cant_bits + 1; f++) {
				counter++;
			}
			int pow_count = counter - 1;
			for (int j = i + offset + 1; j < i + counter + offset + 1; j++) {
				C_num += power(pow_count, 10) * (array[j] - '0');
				pow_count--;
			}
			C_num *= sign;
			i += offset + counter;
		}
		else if (array[i] == 'O') {
			o_flag = 1;
			int offset;
			if (array[i + 1] == '-') {
				sign = -1;
				offset = 1;
			}
			else if (array[i + 1] == '+') {
				sign = 1;
				offset = 1;
			}
			else {
				sign = 1;
				offset = 0;
			}
			int counter = 0;

			for (int f = i + offset + 1; array[f] <= '9' && f != cant_bits + 1; f++) {
				counter++;
			}
			int pow_count = counter - 1;
			for (int j = i + offset + 1; j < i + counter + offset + 1; j++) {
				O_num += power(pow_count, 10) * (array[j] - '0');
				pow_count--;
			}
			O_num *= sign;
			i += offset + counter;
		}
	}
	if (r_flag) {
		numbers[(groupnum-1) * 3] = R_num;
	}
	if (o_flag) {
		numbers[(groupnum-1) * 3 + 1] = C_num;
	}
	if (c_flag) {
		numbers[(groupnum-1) * 3 + 2] = O_num;
	}

	return;
}

int power(int pow, int num) {
	int res = 1;
	for (int i = 0; i < pow; i++) {
		res = res * num;
	}
	return res;
}
