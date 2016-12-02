/* Dealing with the FCF:
 *  - define another memory region
 *  - always define this mess
 */

/*
 * Flash config field "LPBOOT"
 *
 * 0 Low-power boot: OUTDIVx values in SIM_CLKDIV1 register are auto-configured
 *   at reset exit for higher divide values that produce lower power consumption at
 *   reset exit.
 * • Core and system clock divider (OUTDIV1) and bus clock divider (OUTDIV2)
 *   are 0x7 (divide by 8)
 * • Flash clock divider (OUTDIV4)is 0xF (divide by 16)
 *
 * 1 Normal boot: OUTDIVx values in SIM_CLKDIV1 register are auto-configured at
 *   reset exit for higher frequency values that produce faster operating frequencies at
 *   reset exit.
 * • Core and system clock divider (OUTDIV1) and bus clock divider (OUTDIV2)
 *   are 0x0 (divide by 1)
 * • Flash clock divider (OUTDIV4)is 0x1 (divide by 2)
 */
struct k20_flash_config_field {
} fcf __attribute__((section(".flash_config_field"),externally_visible)) = {
};
