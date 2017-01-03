/*
 * timer.c
 *
 *  Created on: Dec 18, 2016
 *      Author: aaditya
 */

#include <msp430.h>
#include <msp430g2553.h>
#include "driver.h"

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop WDT

    P1DIR &= 0x00;                        // P1DIR reset
    P1OUT &= 0x00;                        // P1OUT reset
    P1DIR |= (1 << 0);                    // P1DIR P1.0 -- LED
    DCOCTL =CAL_DCO_16MHZ ;                        // DC0 CTL     = 1110 0000
    BCSCTL1 =CAL_BC1_16MHZ;                    // BCS CTL1     = 1000 0111
    TA0_RunwithInterrupt(32100);
    ADC_Init();
    _BIS_SR(GIE);
    while(1);
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
	TACCTL0 &=~CCIE;
	P1OUT^=0x01;
	ADC10CTL0|=ENC+ADC10SC;	// enable conversion
	TACCTL0|=CCIE;
}
