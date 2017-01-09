#pragma once
/*
 * init_early - declare functions with these prototypes to be called early
 *
 * These are called prior to bss being zeroed, data being copied to ram, and
 * initializers being called.
 *
 * These limitations mean you don't have a full C environment. Be very careful.
 *
 * Only should be used for things that need to happen very soon after reset
 * (usually to prevent further resets).
 *
 *
 */
void arch_init_early(void);
void board_init_early(void);
void init_early(void);

void arch_init(void);
void board_init(void);
void init(void);
