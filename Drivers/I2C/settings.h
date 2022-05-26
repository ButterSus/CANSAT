/**
 * @author ButterSus
 * @date 11.05.2022
 * @name settings for I2C
 */

#ifndef CANSAT_I2C_SETTINGS_H
#define CANSAT_I2C_SETTINGS_H

/*! CONFIG */

#define WRITE_MODE(x) (x &~ 1)
#define READ_MODE(x) (x | 1)

#define GOOD_START 0x08
#define GOOD_REPEATED_START 0x10
#define GOOD_RX_ADDRESS_ACK 0x18
#define GOOD_RX_ADDRESS_NACK 0x20
#define GOOD_RX_DATA_ACK 0x28
#define GOOD_RX_DATA_NACK 0x30
#define GOOD_TX_ADDRESS_ACK 0x40
#define GOOD_TX_ADDRESS_NACK 0x48
#define GOOD_TX_DATA_ACK 0x50
#define GOOD_TX_DATA_NACK 0x58

#endif //CANSAT_I2C_SETTINGS_H