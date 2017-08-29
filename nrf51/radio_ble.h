#pragma once

/**
 * configure the radio into ble mode
 *
 * This does not begin rx or tx, but means we're prepared to do them.
 */
void nrf51_radio_ble_init(void);

// tune radio to specific channel
// NOTE: does not start rx or tx, simply preps
// TODO: consider combining with rx/tx instead of seperate control
void nrf51_radio_ble_channel(uint8_t channel_num);

// recv
// TODO: need timeout & hooks for PDU rx
void nrf51_radio_ble_rx(void);

// ble PDU formatting
// ble adv formatting
// ble scan recv
// ble adv transmit
// ble scan resp transmit
