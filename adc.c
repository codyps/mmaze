#include "lm3s.h"


void adcInit(){
/* module init */
// Enable the ADC clock by writing a value of 0x0001.0000 to the RCGC0 register (pg 222)
SYSCTL->rcgc[0] = 0x00010000;
//Must wait at least 3 clock cycles befor accessing ADC registers after init

// Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to the appropriate bits of the GPIOAMSEL register (pg 393) in the associated GPIO block.

GPIO_AHB->F.amsel |= 0;
GPIO_AHB->E.amsel |= 0;

// If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI register. THe default configuration has SS0 with the highest priority and SS3 as the lowest priority.

//set sampling rate of ADC
SYSCTL->rcgc[0] = (SYSCTL->rcgc[0] & ~(0x300)) | 0x300; //1M samples per second
/*
1M samples/second - 0x3
500K samples/second - 0x2
250K samples/second - 0x1
125K samples/second - 0x0
*/

//Set the harware averaging rate
ADC->sac = (ADC->sac & ~(0x6)) | 0x6; //64x oversampling

/*
No hardware oversampling - 0x0
2x hardware oversampling - 0x1
4x hardware oversampling - 0x2
8x hardware oversampling - 0x3
16x hardware oversampling - 0x4
32x hardware oversampling - 0x5
64x hardware oversampling - 0x6
 */

/* sample sequencer config */
// Ensure the SS is disable by writing a 0 to the corresponding ASENn bit in the ADCACTSS reg. Programming of the SSs is allowed without having the SSs enabled. Disabling the SS during prog. prevents erroneous exec if a trigger ev. were to occur durring the config process.
ADC->actss = (ADC->actss & ~(0x0));

// Config trigger event for the SS in the ADCEMUX reg.
//constant sampling enabled
ADC->emux = (ADC->emux & ~(0xF)) | 0xF;

// For each sample in the SS, config the corresponding input src in the ADCSSMUXn reg.
ADC->ssmux0 = (ADC->ssmux0 & ~(0x0)) | 0x0;
ADC->ssmux0 = (ADC->ssmux0 & ~(0x10)) | 0x10;
ADC->ssmux0 = (ADC->ssmux0 & ~(0x200)) | 0x200;
ADC->ssmux0 = (ADC->ssmux0 & ~(0x3000)) | 0x3000;
ADC->ssmux0 = (ADC->ssmux0 & ~(0x40000)) | 0x40000;

// For each sample in the SS, config the sample control bits in the corresponding nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit is set. Failure to set the END bit causes unpredicatable behavior.
ADC->ssctl0 = (ADC->ssctl0 & ~(0x4)) | 0x4;
ADC->ssctl0 = (ADC->ssctl0 & ~(0x40)) | 0x40;
ADC->ssctl0 = (ADC->ssctl0 & ~(0x400)) | 0x400;
ADC->ssctl0 = (ADC->ssctl0 & ~(0x4000)) | 0x4000;
ADC->ssctl0 = (ADC->ssctl0 & ~(0x60000)) | 0x60000;

// If interrupts are to be used, write a 1 to the corresponding MASK bit in the ADCIM reg.
ADC->im |= 0x1;

// Enable the sample sequencer logic by writing a 1 to the corresponding ASENn bit in the ADCACTSS reg.
ADC->actss |= 0x1;

//ADC values: 0x000 at 0V to 0x3FF at 3V
}
