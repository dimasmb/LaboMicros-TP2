#include "uart_drv.h"
#include <stdio.h>

#define UART_HAL_DEFAULT_BAUDRATE 1000

#define BUFLEN 1000

typedef struct {
	char buffer[BUFLEN];
	int input_index;
	int output_index;
	int distance;
} circbuffer_t;

static circbuffer_t outBuffer = {.input_index = 0,
								.output_index = 0,
								.distance = BUFLEN};

static circbuffer_t inBuffer = {.input_index = 0,
								.output_index = 0,
								.distance = BUFLEN};

void UART_Init (int baudrate){
	//Clock gating
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;


	//Configure UART0 TX and RX PINS

	#define UART0_TX_PIN 17 //PTA2
	#define UART0_RX_PIN 16 //PTA1
	PORTB->PCR[UART0_TX_PIN]=0x0; //Clear all bits
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_MUX(3); //Set MUX to UART0
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_IRQC(0); //Disable Port interrupts

	//Dejo el baudrate en 38400;
	UART_SetBaudRate(UART0, baudrate);

	//Habilitamos UART como transmisor
	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_TIE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK);
	UART0->C1 |= (UART_C1_PE_MASK | UART_C1_PT_MASK);

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


	if(((UART0->S1)& UART_S1_RDRF_MASK)){
		 char temp_ch=UART0->D;
		 inBuffer.buffer[inBuffer.input_index]=temp_ch;
		 if((inBuffer.input_index + 1) != BUFLEN && (inBuffer.input_index + 1) != inBuffer.output_index){
			 inBuffer.input_index++;
			 inBuffer.distance--;
		 }
		 else if((inBuffer.input_index + 1) == BUFLEN){
			 inBuffer.input_index = 0;
		 }
	}
	else if(((UART0->S1) & UART_S1_TDRE_MASK) !=0){
		if(outBuffer.distance==BUFLEN){
			disable_UART_int();
		}
		else{
			UART0->D = outBuffer.buffer[outBuffer.output_index];
			if(outBuffer.output_index==BUFLEN-1){
				outBuffer.output_index=0;
			}
			else{
				outBuffer.output_index++;
			}
		outBuffer.distance--;

		}
	}
}

__ISR__ UART0_ERR_IRQHandler(void)
{


	if(outBuffer.input_index != 0){
		outBuffer.input_index--;
	}
	else{
		outBuffer.input_index==BUFLEN-1;
	}
	outBuffer.distance++;
	enable_UART_int();

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
	if(outBuffer.distance>1){
		for(int i=0; i<datalen; i++){
			outBuffer.buffer[outBuffer.input_index]=tx_data[i];
			if(outBuffer.input_index==BUFLEN-1){
				outBuffer.input_index=0;
			}
			else{
				outBuffer.input_index++;
			}
			outBuffer.distance++;
		}
		enable_UART_int();
	}

}

bool inputEmpty(){
	bool retval;
	(inBuffer.distance!=BUFLEN)?(retval = false) : (retval = true);
	return retval;
}

char retreiveInput(){
	char newInput;
	if(inBuffer.distance!=BUFLEN){
		newInput = inBuffer.buffer[inBuffer.output_index];
		(inBuffer.output_index+1<BUFLEN)?(inBuffer.output_index++):(inBuffer.output_index=0);
		inBuffer.distance++;
	}
	else{
		newInput = '\0';
	}
}
