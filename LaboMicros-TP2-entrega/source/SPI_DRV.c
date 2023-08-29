/***************************************************************************//**
  @file     SPI_DRV.c
  @brief
  @author   Salta
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "SPI_DRV.h"
#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_MODULE_SPI 3
#define MAX_SIGNALS_SPI0 9	//ojo que hay un pin que no esta en el mismo puerto		
#define MAX_SIGNALS_SPI1 7		
#define MAX_SIGNALS_SPI2 16 //ojo el maximo en realidad es 5 pero a fines practicos pongo 16 xq los pines arrancan de 11


#define ALT2 2
#define ALT3 3

static SPI_Type* spi_pointer[]=SPI_BASE_PTRS;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void init_Clk_Nvinc(Module_Spi_t module); //habilito el clock gating y las posibles interrupciones
bool config_CTAR(Spi_config_t Spi); 		//se configuran los atributos del clock (clock and Transfer Atributes Register)
bool config_MCR(Spi_config_t Spi);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
bool init_SPI ( Spi_config_t Spi){
  bool ok;
  init_Clk_Nvinc(Spi.module_spi);
  ok=config_MCR(Spi);
  ok=(ok & (config_CTAR(Spi) ) );	//se configuran los atributos del clock, dependiendo el modo.
  if (ok == true){
	switch (Spi.module_spi){
  	  case spi_0:
		PORTD->PCR[0]|=0; //PCS0, SS
		PORTD->PCR[0]|=PORT_PCR_MUX(ALT2);
		PORTD->PCR[1]|=0; //SCLK
		PORTD->PCR[1]|=PORT_PCR_MUX(ALT2);
		PORTD->PCR[2]|=0;	//SOUT
		PORTD->PCR[2]|=PORT_PCR_MUX(ALT2);
	   	PORTD->PCR[3]|=0; //SIN
	   	PORTD->PCR[3]|=PORT_PCR_MUX(ALT2);
	   	//modo runnig
	   	spi_pointer[spi_0]->MCR = (spi_pointer[spi_0]->MCR & ~SPI_MCR_HALT_MASK) | SPI_MCR_HALT(0);
	   	break;
  	  case spi_1:
	  	for (int i = 0; i <MAX_SIGNALS_SPI1 ; i++){ //reseteo todos los pcr que voy a usar
			PORTE->PCR[i]=0;						//Los seteo en ALt 2 que es pa poderlos usar como SPI
			PORTE->PCR[i]|=PORT_PCR_MUX(ALT2) ;		//todo En caso de usar Interrupcion usar agreggar aca
	  	}break;
  	  case spi_2:
	  	for (int i = 11; i < MAX_SIGNALS_SPI2; i++){
			PORTD->PCR[i]=0;
			PORTD->PCR[i]|=PORT_PCR_MUX(ALT2);
	  	}break;
  	  default:
	  	ok=false;
  		break; 
	}
  	return ok;
  }
 return ok;
}
uint8_t writeyread_SPI(Spi_config_t Spi, uint16_t msg ){
	spi_pointer[Spi.module_spi]->SR |= SPI_SR_TCF(1); //borro el tranfer flag complete

	while (!(spi_pointer[Spi.module_spi]->SR & SPI_SR_TFFF_MASK)) // Si TFFF = 1 (TxFifo no esta full, hay al menos un bit disponible), sale del while
    {
		spi_pointer[Spi.module_spi]->SR |= SPI_SR_TFFF_MASK; // asumo que está llena, entonces hasta que no se haya ido al menos un bit, no va a cambiar TFFF a 1
    }

	uint32_t PUSHR_Value = 0;
	PUSHR_Value|=SPI_PUSHR_CONT(1); //pa probar.
	PUSHR_Value |=SPI_PUSHR_PCS(1);
	PUSHR_Value |=SPI_PUSHR_CTAS(0b001); 		//elijo que ctar estoy configurando pa mandar.
	PUSHR_Value |=SPI_PUSHR_CTCNT(1);
	PUSHR_Value	&=~SPI_PUSHR_EOQ(1);
	PUSHR_Value |= SPI_PUSHR_TXDATA(msg);
	spi_pointer[Spi.module_spi]->PUSHR = PUSHR_Value;
	spi_pointer[Spi.module_spi]->SR |= SPI_SR_TFFF_MASK;
    /*while (!(spi_pointer[Spi.module_spi]->SR & SPI_SR_TCF_MASK)) // si TCF = 1 (transferencia completa), sale del while
    {												// es decir espero a que se shifteen todos los bits del frame
    }*/
   return (spi_pointer[Spi.module_spi]->POPR);
}
uint32_t read_SPI(Spi_config_t Spi){
	return (spi_pointer[Spi.module_spi]->POPR & SPI_POPR_RXDATA_MASK) >> SPI_POPR_RXDATA_SHIFT ;

}
void disable_CS(Spi_config_t Spi ){
	uint8_t msg=0b00000000;
	spi_pointer[Spi.module_spi]->SR |= SPI_SR_TCF(1); //borro el tranfer flag complete

	while (!(spi_pointer[Spi.module_spi]->SR & SPI_SR_TFFF_MASK)) // Si TFFF = 1 (TxFifo no esta full, hay al menos un bit disponible), sale del while
    {
		spi_pointer[Spi.module_spi]->SR |= SPI_SR_TFFF_MASK; // asumo que está llena, entonces hasta que no se haya ido al menos un bit, no va a cambiar TFFF a 1
    }

	uint32_t PUSHR_Value = 0;
	PUSHR_Value&=~SPI_PUSHR_CONT(1); //apago el keepcs
	PUSHR_Value &=~SPI_PUSHR_PCS(1);	//apago el chip selec.
	PUSHR_Value	|=SPI_PUSHR_EOQ(1);
	PUSHR_Value |=SPI_PUSHR_CTCNT(1);
	PUSHR_Value |=SPI_PUSHR_CTAS(0b001); 		//elijo que ctar estoy configurando pa mandar.
	PUSHR_Value |= SPI_PUSHR_TXDATA(msg);
	spi_pointer[Spi.module_spi]->PUSHR = PUSHR_Value;
	spi_pointer[Spi.module_spi]->SR |= SPI_SR_TFFF_MASK;
    /*while (!(spi_pointer[Spi.module_spi]->SR & SPI_SR_TCF_MASK)) // si TCF = 1 (transferencia completa), sale del while
    {												// es decir espero a que se shifteen todos los bits del frame
    }*/
    spi_pointer[Spi.module_spi]->POPR;

	return;
}

bool SPI_TransferComplet(Spi_config_t Spi)
{
	return (spi_pointer[Spi.module_spi]->SR & SPI_SR_TCF_MASK) >> SPI_SR_TCF_SHIFT;
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void init_Clk_Nvinc(Module_Spi_t module){ //se habilita el clock gating de los SPI y ademas las interrupciones
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
  	switch (module){
   	 case spi_0:SIM->SCGC6|=SIM_SCGC6_SPI0_MASK;
    		NVIC_EnableIRQ( SPI0_IRQn  );
      	break;
    	case spi_1: SIM->SCGC6|=SIM_SCGC6_SPI1_MASK ;
    		NVIC_EnableIRQ( SPI1_IRQn  );
     	break;
    	case spi_2: SIM->SCGC3|=SIM_SCGC3_SPI2_MASK;
    		NVIC_EnableIRQ(SPI2_IRQn );
     	break;
    	default:
      	break;
  }
  	return;
}
bool config_CTAR(Spi_config_t Spi){		//Se configuran los atributos del spi elegido.
int ctrl=Spi.CONT_CLK;
if (Spi.mode<Disable)
{
	if(Spi.mode == Master ){		// CTAR es una union de dos arreglos , en la parte ALTA se configura el master mode(lo cambio pa usar sck continuo)
		 spi_pointer[Spi.module_spi]->CTAR[ctrl]=0;
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_DBR(Spi.DBR);
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_FMSZ(Spi.FMSZ);
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_CPOL(Spi.CPOL);
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |=SPI_CTAR_CPHA(Spi.CPHA);
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_LSBFE(Spi.LSBFE);
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_PBR(Spi.PBR);

		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_BR(0b0110) ;
		 //Agrego delays extras pa poder detectar mejor los numeros
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_PCSSCK(0b11); //5us delay pa que arranque
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |=SPI_CTAR_CSSCK(0b0010);
		 //delay min entre transfer.
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |= SPI_CTAR_PDT(0b11); //Delay entre transferencias 5us
		 spi_pointer[Spi.module_spi]->CTAR[ctrl] |=SPI_CTAR_DT(0b0010);

	}
	else{
		spi_pointer[Spi.module_spi]->CTAR[0]=0;
		spi_pointer[Spi.module_spi]->CTAR[0] |=SPI_CTAR_SLAVE_FMSZ(Spi.FMSZ);// todo probar que pasa si uso CTAR_Slave[0] creo que tendria que ser lo mismo
		spi_pointer[Spi.module_spi]->CTAR[0] |=SPI_CTAR_SLAVE_CPOL(Spi.CPOL);
		spi_pointer[Spi.module_spi]->CTAR[0] |=SPI_CTAR_SLAVE_CPHA(Spi.CPHA);
		
	}
	return true;
}// spi esta desactivado, no tiene sentido configurar el CTAR
return false; 
}

bool config_MCR(Spi_config_t Spi){ //todo podria agregar el PCSIS , Peropheral Chip Slecet x Inactive State
	if (Spi.module_spi<= MAX_MODULE_SPI){
		spi_pointer[Spi.module_spi]->MCR= 0; 	//Reset el MCR
  	  	spi_pointer[Spi.module_spi]->MCR|=SPI_MCR_HALT(true); //seteo el halt por uqe asi lo aconseja el reset
		spi_pointer[Spi.module_spi]->MCR|=SPI_MCR_MSTR(Spi.mode);	//seteo el modo
		spi_pointer[Spi.module_spi]->MCR&=~SPI_MCR_CONT_SCKE(1); //pa controlar el clock continuo.

		spi_pointer[Spi.module_spi]->MCR|=SPI_MCR_PCSIS(Spi.PCSIS);
		if(Spi.mode==Slave){spi_pointer[Spi.module_spi]->MCR|=SPI_MCR_MDIS(0); } //recomendacion del Reference
		return true;
	}
	return false;	 
}


/*******************************************************************************
 ******************************************************************************/



