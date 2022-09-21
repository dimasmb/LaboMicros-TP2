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
#include "i2cm.h"
#include "timer.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

//static void delayLoop(uint32_t veces);
//static void blinkInt(void);
static void sendData(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	init_I2C(I2C_1);
  timerInit();
  timerStart(timerGetId(), TIMER_MS2TICKS(1000), TIM_MODE_PERIODIC, sendData);
	//initTransciever();
	//initAccel();
	//initUART();
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	
	/*if(getTransRxFlag() || getPCRxFlag()) //Si el transiever tiene info o si la PC me pide que le mande
    {
      GetAccData();
      GetTrnsceiverDataPckg();
      SendDataPckg();
    }*/
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
void sendData(void)
{
  uint8_t text []= "hola";
	i2cSimpleTransaction(0x0f, MODE_W, 4, text);
}