#include <stdint.h>

#include "stm8s.h"
#include "stm8s_tim2.c"

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
    TIM2->ARRH = 0x03;       //  High byte of 1000.
    TIM2->ARRL = 0xe8;       //  Low byte of 1000.
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

void InitialiseTimer2()
{
    TIM2->CR1 = 0;               // Turn everything TIM2 related off.
    TIM2->IER = 0;
    TIM2->SR2 = 0;
    TIM2->CCER1 = 0;
    TIM2->CCER2 = 0;
    TIM2->CCER1 = 0;
    TIM2->CCER2 = 0;
    TIM2->CCMR1 = 0;
    TIM2->CCMR2 = 0;
    TIM2->CCMR3 = 0;
    TIM2->CNTRH = 0;
    TIM2->CNTRL = 0;
    TIM2->PSCR = 0;
    TIM2->ARRH  = 0;
    TIM2->ARRL  = 0;
    TIM2->CCR1H = 0;
    TIM2->CCR1L = 0;
    TIM2->CCR2H = 0;
    TIM2->CCR2L = 0;
    TIM2->CCR3H = 0;
    TIM2->CCR3L = 0;
    TIM2->SR1 = 0;
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
	TIM2_SetCompare1(R); //R
	TIM2_SetCompare2(G); //G
	TIM2_SetCompare3(B); //B
}

void main()
{

	disableInterrupts();
	InitialiseSystemClock();
	InitialiseTimer2();
	SetupTimer2();
	SetupTimer2_CH1();
	SetupTimer2_CH2();
	SetupTimer2_CH3();
    //    TIM1_OC1Init( TIM1_OCMODE_PWM1 , TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE, 500, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_RESET);
	enableInterrupts()

	delay();
    while(1)
    {
	//wfi();
	setcolor(100, 0, 0);
	delay();
	setcolor(0,100, 0);
	delay();
	setcolor(0, 0, 100);
	delay();
	
    }
}
