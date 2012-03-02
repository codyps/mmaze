#ifndef STEPPERS_H_
#define STEPPERS_H_


/* stepper_go - send a 'command' to the stepper subsystem.
 *
 * @freq : the number of 'ticks per second' (maybe in fixed point form?)
 * @count: number of overall ticks before stopping (maybe the stop should
 *         trigger some function call to decide what to do next?)
 */
void stepper_go(uint32_t freq, int32_t count);

void stepper_init(void);


#endif
