#include <stdint.h>

#include "stm8s.h"

void InitialiseSystemClock()
{
    CLK->ICKR = 0;                       //  Reset the Internal Clock Register.
    CLK->ICKR |= CLK_ICKR_HSIEN;          //  Enable the HSI.
    CLK->ECKR = 0;                       //  Disable the external clock.
    while (CLK->ICKR & CLK_FLAG_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
    CLK->CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
    CLK->PCKENR1 = 0xff;                 //  Enable all peripheral clocks.
    CLK->PCKENR2 = 0xff;                 //  Ditto.
    CLK->CCOR = 0;                       //  Turn off CCO.
    CLK->HSITRIMR = 0;                   //  Turn off any HSIU trimming.
    CLK->SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
    CLK->SWR = 0xe1;                     //  Use HSI as the clock source.
    CLK->SWCR = 0;                       //  Reset the clock switch control register.
    CLK->SWCR = CLK_SWCR_SWEN;                  //  Enable switching.
    while (CLK->SWCR & CLK_SWCR_SWBSY != 0 );        //  Pause while the clock switch is busy.
}

void SetupTimer2()
{
    TIM2->PSCR = 0x00;       //  Prescaler = 1.
    TIM2->ARRH = 0x10;       //  High byte of 4096
    TIM2->ARRL = 0x00;       //  Low byte of 4096
    TIM2->CR1 = TIM2_CR1_CEN;       //  Finally enable the timer.
}

void SetupTimer2_CH1()
{
    TIM2->CCR1H = 0x00;      //  High byte
    TIM2->CCR1L = 0x00;      //  Low byte 
    //TIM2->CCER1 |= TIM2_CCER1_CC1P;    //  Active high.
    TIM2->CCER1 |= TIM2_CCER1_CC1E;    //  Enable compare mode for channel 1
    TIM2->CCMR1 =  TIM2_OCMODE_PWM1;    //  PWM Mode 1 - active if counter < CCR1, inactive otherwise.
}
void SetupTimer2_CH2()
{
    TIM2->CCR2H = 0x00;      //  High byte 
    TIM2->CCR2L = 0x00;      //  Low byte 
    //TIM2->CCER1 |= TIM2_CCER1_CC2P;    //  Active high.
    TIM2->CCER1 |= TIM2_CCER1_CC2E;    //  Enable compare mode for channel 1
    TIM2->CCMR2 =  TIM2_OCMODE_PWM1;    //  PWM Mode 1 - active if counter < CCR1, inactive otherwise.
}

void SetupTimer2_CH3()
{
    TIM2->CCR3H = 0x00;      //  High byte
    TIM2->CCR3L = 0x00;      //  Low byte 
    //TIM2->CCER2 |= TIM2_CCER2_CC3P;    //  Active high.
    TIM2->CCER2 |= TIM2_CCER2_CC3E;    //  Enable compare mode for channel 1
    TIM2->CCMR3 =  TIM2_OCMODE_PWM1;    //  PWM Mode 1 - active if counter < CCR1, inactive otherwise.
}

void delay()
{

	uint16_t c = 0;
        uint16_t i = 0;
	for( i=0; i<10; i++)
		while( --c ) nop();
}

void setcolor( uint16_t R, uint16_t G, uint16_t B )
{
	// (2<<16-1) / 4096 ~= 16	
	//therefore to rescale 16bit channels to 12 we right shift 4
	TIM2_SetCompare1(R>>4); //R
	TIM2_SetCompare2(G>>4); //G
	TIM2_SetCompare3(B>>4); //B
}



void uarttx_str( char* str )
{
	char* ch = str;

	while( *ch )
	{
		UART1->DR = (unsigned char) *ch;
		while( ( UART1->SR & UART1_SR_TXE ) == 0); // DR to be transfered to shift register
		ch++;
	}

	//Wait for shift register to empty
	while( ( UART1->SR & UART1_SR_TC ) == 0) nop();
} 

void main()
{
	uint8_t RGB[6];
	uint8_t offset = 0;
	uint8_t tmp = 0;

	disableInterrupts();
	InitialiseSystemClock();
	TIM2_DeInit();

	SetupTimer2();
	SetupTimer2_CH1();
	SetupTimer2_CH2();
	SetupTimer2_CH3();

	UART1_DeInit();
	UART1_Init( 1000000, 0, 0, 0, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

	enableInterrupts()

        setcolor(100, 100, 100);

	uarttx_str( "READY\n");

    while(1)
    {
	while( ( UART1->SR & UART1_SR_RXNE == 0 ) && ( UART1->SR & UART1_SR_IDLE == 0 ) );

	if( UART1->SR & UART1_SR_RXNE  )
	{
		//RX Byte
		if( offset < 6 )
		{
			RGB[ offset++ ] = UART1->DR;
		}
		else
		{
			tmp = UART1->DR; 
			UART1->DR = tmp;
		}
	}
	if( UART1->SR & UART1_SR_IDLE )
	{
		uint16_t R,G,B;
		//CLEAR IDLE FLAG - READ SR then DR
		tmp = UART1->SR;
		tmp = UART1->DR;

		R = ((uint16_t)RGB[1]) << 8 | RGB[0];
		G = ((uint16_t)RGB[3]) << 8 | RGB[2];
		B = ((uint16_t)RGB[5]) << 8 | RGB[4];

		//WAIT FOR TX TO FINISH - so next controller can shift in data
		while( ( UART1->SR & UART1_SR_TC ) == 0);
		
		//DRAW
		setcolor( R,G,B );
		offset=0;
	}

    }

}
