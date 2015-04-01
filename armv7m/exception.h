#pragma once

struct armv7m_exception_frame {
	uint32_t r0,
		 r1,
		 r2,
		 r3,
		 r12,
		 lr,
		 ra,
		 xpsr,
		 sp_a,
		 sp_b;
};
