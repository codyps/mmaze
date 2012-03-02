#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define ISR(vector_name) __attribute__((interrupt)) void vector_name(void)

#endif
