#pragma once

#define DWT_CTRL   MMIO_32(0xE0001000)

#define DWT_CYCCNT MMIO_32(0xE0001004)

/* reset = 0, rw, power on reset only  */
#define SCB_DFSR   MMIO_32(0xE000ED30)

/* debug halting control & status; reset = 0, rw */
#define SCB_DHCSR  MMIO_32(0xE000EDF0)
/* debug core register selector; wo */
#define SCB_DCRSR  MMIO_32(0xE000EDF4)
/* debug core register data; rw */
#define SCB_DCRDR  MMIO_32(0xE000EDF8)
/* debug exception & monitor control; rw; reset = 0 */
#define SCB_DEMCR  MMIO_32(0xE000EDFC)

#define CSC_DWT MMIO_32(0xE000FF004)
