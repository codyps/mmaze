/* Dealing with the FCF:
 *  - define another memory region
 *  - always define this mess
 */
struct k20_flash_config_field {
} fcf __attribute__((section(".flash_config_field"),externally_visible)) = {
};
