#include <msp430.h> 
#include "msp430g2553.h"
/*
 * main.c
 */
void ADC_initalize();
void Timer_Init();
int main(void) {
	unsigned int ADCValue;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR =0x01;
	P1OUT|=BIT0;

	P1SEL|=BIT3; // port pin select
	BCSCTL1 = CALBC1_12MHZ;
	DCOCTL =CALDCO_12MHZ;
	ADC_initalize();
	Timer_Init();
	__bis_SR_register(GIE);

  	while(1);
   return 0;
}

void ADC_initalize()
{
	ADC10CTL0&=~ENC;
	ADC10CTL0|=	ADC10SHT_2+ADC10ON+MSC;
	ADC10CTL1|=INCH_3 +ADC10DIV_0+ADC10SSEL_2;
    ADC10AE0 |=BIT1; // chaneel enable 1
    ADC10CTL0|=ENC+ADC10SC;
}
void Timer_Init()
{
	TACTL|=MC_0;
	TACTL|=TASSEL_1+TAIE;
	TACCTL0|=(0x01<<4);
	TACTL|=MC_2;
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void)
{
	 static unsigned int i=0;
	 TACTL&=~(0x03<<0);
	 P1OUT^=BIT0;
	 TACTL |=(0x03<<0);
}
