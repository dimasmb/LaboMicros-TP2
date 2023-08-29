#include "uart_drv.h"
#include <stdio.h>

#define UART_HAL_DEFAULT_BAUDRATE 1000

#define BUFLEN 3000

static char buffer[BUFLEN];
static int input_index = 0;
static int output_index = 0;

static int distance = BUFLEN;


void UART_SetBaudRate (UART_Type *uart, uint32_t baudrate);

void UART_Init (void){
	//Clock gating
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

	//Configure UART0 TX and RX PINS

	#define UART0_TX_PIN 17 //PTB 17
	#define UART0_RX_PIN 16 //PTB 16
	PORTB->PCR[UART0_TX_PIN]=0x0; //Clear all bits
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_MUX(3); //Set MUX to UART0
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_IRQC(0); //Disable Port interrupts

	//Dejo el baudrate en 115200;
	UART_SetBaudRate(UART0, 115200);

	//Habilitamos UART como transmisor
	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_TIE_MASK);

}


void enable_UART_int(){
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);
	NVIC_SetPriority(UART0_RX_TX_IRQn,0);
	NVIC_EnableIRQ(UART0_ERR_IRQn);
	NVIC_SetPriority(UART0_ERR_IRQn,0);
}

void disable_UART_int(){
	NVIC_DisableIRQ(UART0_RX_TX_IRQn);
	NVIC_DisableIRQ(UART0_ERR_IRQn);
}

__ISR__ UART0_RX_TX_IRQHandler (void)
{

	 if(((UART0->S1) & UART_S1_TDRE_MASK) !=0){ //Puedo Transmitir ?
		 if(distance==BUFLEN){
		 			 disable_UART_int();
		 }
		 else{

			UART0->D = buffer[output_index]; // Transmito '!'
			if(output_index==BUFLEN-1){
				output_index=0;
			}
			else{
				output_index++;
			}
			distance++;

		 }


	 }

}

__ISR__ UART0_ERR_IRQHandler(void)
{

}


void UART_SetBaudRate (UART_Type *uart, uint32_t mybaudrate) {

uint16_t sbr, brfa; 
uint32_t clock; 

#define __BASE_CLOCK__ 100000000U

clock = ((uart == UART0) || (uart == UART1))?(__BASE_CLOCK__):(__BASE_CLOCK__ >> 1);

uint32_t baudrate;
baudrate = ((mybaudrate == 0)?(UART_HAL_DEFAULT_BAUDRATE):((mybaudrate > __BASE_CLOCK__/2)?(UART_HAL_DEFAULT_BAUDRATE):(mybaudrate)));

sbr = clock / (baudrate<<4);
brfa = (clock << 1) / baudrate - (sbr<<5);

uart-> BDH = UART_BDH_SBR(sbr>>8);
uart-> BDL = UART_BDL_SBR(sbr);
uart-> C4 = (uart->C4 & ~UART_C4_BRFA_MASK) | UART_C4_BRFA(brfa);

}


void UART_Send_Data(unsigned char *tx_data, int datalen)
{
	if(distance>80){
		for(int i=0; i<datalen; i++){
			buffer[input_index]=tx_data[i];
			if(input_index==BUFLEN-1){
				input_index=0;
			}
			else{
				input_index++;
			}
			distance--;
		}
		enable_UART_int();
	}



}
