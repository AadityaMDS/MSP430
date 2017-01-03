/*
 * driver.c
 *
 *  Created on: Dec 25, 2016
 *      Author: aaditya
 */
/* 1 jiffis =1us
 * please do not touch the timer0 when you use the timer 0
 */
#include<msp430.h>
#include <msp430g2553.h>
void TA0_RunwithInterrupt(unsigned int jiffis)
{
	 TACTL|=MC_0;
	 TA0CCR0 =jiffis;
	 TA0CCTL0 |=CCIE;
	 TACTL |= TASSEL_2 + MC_1 + ID_3;       // timerCTL control

}
void Serial_Init()
{
	UCA0CTL1|=UCSSEL_2; // SMCLK
	UCA0BR0 =106 ; // 8 bit value
	UCA0MCTL=UCOS16 +(3<<4); // Setting is taken by USerguide 9600
	UC0IE |=UCA0RXIE+UCA0TXIE;
	UCA0CTL1 &=~UCSWRST; // reset clear UART is enable for operation
}
void Serial_Transfer(char value)
{
	while(!(UC0IFG&UCA0TXIFG));
	UCA0TXBUF =value;
	UC0IFG&=~UCA0TXIFG;
}
char Serial_Receive(void)
{
	while(!(UC0IFG&UCA0RXIFG));
   	return UCA0RXBUF; // received 8 bit  value
    UC0IFG&=~UCA0RXIFG;
}
void ADC_Init(void)
{
	P1SEL|=BIT3; // port pin select
    ADC10CTL0&=~ENC;// ADC disable
    ADC10CTL0|=	ADC10SHT_2+ADC10ON+MSC; // singal channel multiple conversion
    ADC10CTL1|=INCH_3 +ADC10DIV_0+ADC10SSEL_2;
    ADC10AE0 |=BIT1; // channel enable 1
    ADC10CTL0|=ENC+ADC10SC;	// enable conversion
}

