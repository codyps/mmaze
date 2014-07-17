/* Bleh 
 *
 */

#include "lm3s.h"

.macro FUNC_DECL name
	.thumb_func
	.global \name
\name:
.endm

.macro FUNC_START name
	.func     \name
	FUNC_DECL \name
.endm

.macro vector name
	.if (. - __vectors < _VECTORS_SIZE)
	.weak __vector_\name
	.set  __vector_\name, __bad_interrupt
	.long __vector_\name
	.endif
.endm

	.section .isr_vector,"ax",%progbits
	.func   __vectors
	.global __vectors
__vectors:
	.long  __stack_high__
	.long  __vector_1
	vector 2
	vector 3
	vector 4
	vector 5
	vector 6
	vector 7
	vector 8
	vector 9
	vector 10
	vector 11
	vector 12
	vector 13
	vector 14
	vector 15
	vector 16
	vector 17
	vector 18
	vector 19
	vector 20
	vector 21
	vector 22
	vector 23
	vector 24
	vector 25
	vector 26
	vector 27
	vector 28
	vector 29
	vector 30
	vector 31
	vector 32
	vector 33
	vector 34
	vector 35
	vector 36
	vector 37
	vector 38
	vector 39
	vector 40
	vector 41
	vector 42
	vector 43
	vector 44
	vector 45
	vector 46
	vector 47
	vector 48
	vector 49
	vector 50
	vector 51
	vector 52
	vector 53
	vector 54
	vector 55
	vector 56
	vector 57
	vector 58
	vector 59
	vector 60
	vector 61
	vector 62
	vector 63
	.endfunc

	.text
	.weak  __vector_1
	.set   __vector_1, __init
	.weak __bad_interrupt
	.set  __bad_interrupt, __vector_1
