#pragma once
/*
 * generic chip watchdog api
 *
 * Assumes:
 *  - only a single watchdog exists
 */

/**
 * watchdog_disable - if possible, disable the watchdog so it does not reset the chip
 *
 * Note: it's only advisable to use this durring development. In most cases,
 * one should adjust the timeout length and feed the watchdog as needed.
 *
 */
void watchdog_disable(void);
