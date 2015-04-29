#pragma once
#include <stdint.h>

struct sam3_pdc {
	uint32_t receive_pointer,
		 receive_counter,
		 transmit_pointer,
		 transmit_counter,
		 receive_next_pointer,
		 receive_next_counter,
		 transmit_next_pointer,
		 trasnmit_next_counter,
		 trasnfer_control,
		 transfer_status;
};

#define SAM3_PDC_BASE(base) ((char *)(base) + 0x100)
#define SAM3_PDC(base) (*(volatile struct sam3_pdc)SAM3_PDC_BASE(base))
