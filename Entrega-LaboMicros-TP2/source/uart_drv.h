#include "MK64F12.h"
#include <stdint.h>
#include "hardware.h"

void UART_Send_Data(unsigned char *tx_data, int datalen);
void UART_Init (void);
