#include "MK64F12.h"
#include <stdint.h>
#include "hardware.h"
#include <stdbool.h>


void UART_SetBaudRate (UART_Type *uart, uint32_t baudrate);
void UART_Send_Data(unsigned char *tx_data, int datalen);
void UART_Init (int baudrate);
bool inputEmpty();
char retreiveInput();

