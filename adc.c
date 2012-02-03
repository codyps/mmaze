
/* module init */
// Enable the ADC clock by writing a value of 0x0001.0000 to the RCGC0 register (pg 222)
SYSCTL->rcgc0 |= 0x00010000;
// Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to the appropriate bits of the GPIOAMSEL register (pg 393) in the associated GPIO block.

GPIO_AHB->F.amsel |= 0;
GPIO_AHB->E.amsel |= 0;

// If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI register. THe default configuration has SS0 with the highest priority and SS3 as the lowest priority.

/* sample sequencer config */
// Ensure the SS is disable by writing a 0 to the corresponding ASENn bit in the ADCACTSS reg. Programming of the SSs is allowed without having the SSs enabled. Disabling the SS during prog. prevents erroneous exec if a trigger ev. were to occur durring the config process.
// Config trigger event for the SS in the ADCEMUX reg.
// For each sample in the SS, config the corresponding input src in the ADCSSMUXn reg.
// For each sample in the SS, config the sample control bits in the corresponding nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit is set. Failure to set the END bit causes unpredicatable behavior.
// If interrupts are to be used, write a 1 to the corresponding MASK bit in the ADCIM reg.
// Enable the sample sequencer logic by writing a 1 to the corresponding ASENn bit in the ADCACTSS reg.


