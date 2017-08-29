#pragma once
#include <abort.h>

// BT 5.0, 6.A, 2, Fig 2.1
static inline
unsigned ble_chan_to_mhz(uint8_t channel_idx)
{
	// valid channels are from 0 to 39
	if (channel_idx > 39)
		abort();

	return 2402 + channel_idx * 2;
}

// BT 5.0, 6.B, 1.1
enum BLE_LL_STATE {
	BLE_LL_STATE_STANDBY,
	BLE_LL_STATE_SCANNING,
	BLE_LL_STATE_ADVERTISING,
	BLE_LL_STATE_INITIALIZING,
	BLE_LL_STATE_CONNECTION,
};

// BT 5.0, 6.B, 1.3
struct ble_addr {
	uint8_t bytes[6];
};

// BT 5.0, 6.B, 1.3.2.1
static inline
bool ble_addr_is_static(struct ble_addr *ba)
{
	// address is static if the top 2 bits are '1'
	return (ba->bytes[0] & 0xC0) == 0xC0
}

// BT 5.0, 6.B, 1.3.2.2, Fig 1.3
static inline
bool ble_addr_is_non_resolvable_private(struct ble_addr *ba)
{
	return (ba->bytes[0] & 0xC0) == 0;
}

// BT 5.0, 6.B, 1.3.2.2, Fig 1.4
static inline
bool ble_addr_is_resolvable_private(struct ble_addr *ba)
{
	return (ba->bytes[0] & 0xC0) == 0x80;
}

// 24-bits of this
static
uint32_t ble_addr_rp__hash(struct ble_addr *ba)
{
	abort();
	// lower 24 bits
}

// 24-bits of this
static
uint32_t ble_addr_rp__prand(struct ble_addr *ba)
{
	abort();
	// upper 24 bits, with the 2msbits set to 0b10
}

static
bool ble_addr_is_valid(struct ble_addr *ba)
{
	if (ble_addr_is_resolvable_private(ba)) {
		// TODO: require that at least 1 bit in the random part of prand is 0
		// require that at least 1 bit in the random part of prand is 1
	} else if (ble_addr_is_non_resolvable_private(ba) || ble_addr_is_static(ba)) {
		// require that at least 1 bit is 0
		// require that at least 1 bit is 1
	}

	return true;
}

#if 0
// BT 5.0, 3.H, 2.2.1
void ble_e(uint8_t key[static 16], uint8_t data[static 16], uint8_t out[static 16])
{
	// aes-128
}
#endif

// For calculating the hash portion of a resolvable private address
// hash = ah(IRK, prand)
// TODO: consider if uint32_t or a (uint8_t *) is more convenient to work with.
// BT 5.0, 3.H, 2.2.2
static
uint32_t ble_address_hash(uint8_t *irk, uint8_t *prand)
{
	abort();
#if 0
	// pad prand to 128 bits with zeros
	// then call `e`
	uint8_t out[16];
	ble_e(irk, prand, out);

	// truncate 128 bit output to 24 bits.
	return out[0] | (out[1] << 8) | (out[2] << 16);
#endif
}

// All channels are either for advertising, or data+secondary advertising.
// BT 5.0, 6.B, 1.4.1, Tbl 1.2
bool ble_chan_is_adv(uint8_t chan_idx)
{
	if (chan_idx > 39)
		abort();

	switch (chan_idx) {
	case 0:
	case 12:
	case 39:
		return true;
	default:
		return false;
	}
}

#if 0
// BT 5.0, 6.B, 2.1
// 1Mbps & 2Mbps
struct ble_packet {
	// if 1Mbps, x = 1
	// if 2Mbps, x = 2
	uint8_t preamble[x];
	uint8_t access_addr[4];
	uint8_t pdu[y]; // where y is 2 to 257
	uint8_t crc[3];
};
#endif

// BT 5.0, 6.B, 2.1.2
// access address for advertising
#define BLE_AADDR_ADV 0x8E89BED6

static 
bool ble_access_addr_valid(uint32_t addr)
{

	// not the advertising channel access addr
	// not a sequence that differs from BLE_AADDR_ADV by only 1 bit
	if (popcount(addr ^ BLE_AADDR_ADV) < 2)
		return false;

	// not all 4 octets are equal
	uint8_t *b = (uint8_t *)&addr;
	if (b[0] == b[1] && b[2] == b[3] && b[2] == b[1])
		return false;

	// no more than 6 consecutive 0s or 1s.
	// no more than 24 transitions
	// at least 2 transistions in the most significant 6 bits
	
	uint8_t i;
	uint32_t msk = 1 << 31;
	bool last = addr & msk;
	uint8_t run = 0;
	uint8_t trans = 0;
	for (i = 1; i < 32; i++) {
		uint32_t nmsk = msk >> 1;
		bool curr = addr & nmsk;
		if (curr == last) {
			run ++;
			if (run > 6)
				return false;
		} else {
			run = 0;
			trans ++;
		}

		if (i == 6 && trans < 2)
			return false;
	}

	if (trans > 24)
		return false;

	return true;
}

// transmit times in micro seconds
#define BLE_PACKET_US_MIN 44
#define BLE_PACKET_US_MAX 2120

// BT 5.0, 6.B, 2.3
// adv pdu has a 16 bit header
#if 0
struct ble_adv_pdu_header {
	uint8_t pdu_type:4;
	uint8_t rfu:1;
	uint8_t ch_sel:1;
	uint8_t tx_add:1;
	uint8_t rx_add:1;
	uint8_t length;
};
#endif

// BT 5.0, 6.B, 2.3
// pdu-types
#define BLE_ADV_IND 0
#define BLE_ADV_DIRECT_IND 1
#define BLE_ADV_NONCONN_IND 2
#define BLE_SCAN_REQ 3
#define BLE_AUX_SCAN_REQ 3
#define BLE_SCAN_RSP 4
#define BLE_CONNECT_IND 5
#define BLE_AUX_CONNECT_REQ 5
#define BLE_ADV_SCAN_IND 6
#define BLE_ADV_EXT_IND 7
#define BLE_AUX_ADV_IND 7
#define BLE_AUX_SCAN_RSP 7
#define BLE_AUX_SYNC_IND 7
#define BLE_AUX_CHAIN_IND 7
#define BLE_AUX_CONNECT_RSP 8

//

