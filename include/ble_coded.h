#pragma once

// coded phy has additional restrictions
static 
bool ble_access_addr_valid_coded(uint32_t addr)
{
	// at least 3 1s in the least significant 8 bits
	// no more than 11 transitions in the least significant 16 bits
	abort();
}



