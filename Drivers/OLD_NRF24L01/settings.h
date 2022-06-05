/**
 * @author ButterSus
 * @date 06.05.2022
 * @name SETTINGS FOR NRF24L01
 *
 * @note
 * uses MACROS as SETTINGS
 */

#ifndef CANSAT_OLD_NRF24L01_SETTINGS_H
#define CANSAT_OLD_NRF24L01_SETTINGS_H

#include <avr/io.h>

/*! USER INTERFACE */

#define CE_PORT lpPORTB
#define CE_NUM 6
#define CE_DELAY 1000
#define CSN_PORT lpPORTB
#define CSN_NUM 7

/*! CONFIG (check it) */

#define REG_CONFIG_VALUE		0x02
#define REG_CHANNEL_VALUE		100
#define REG_RFSET_VALUE		    0x0F
#define REG_AA_EN_VALUE		    0x00
#define REG_RXADDR_VALUE		0x00
#define REG_STATUS_VALUE		0x30
#define REG_SETUP_RETR_VALUE    0x2F
#define REG_DYNPD_VALUE         0x07
#define REG_FEATURE_VALUE       0x07
static uint8_t REG_TXADDR_VALUE[] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE0};

#define MODE_SPI \
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)

#define CMD_FLUSH       0xE1

#define REG_CONFIG	    0x00
#define REG_EN_AA		0x01
#define REG_RXADDR	    0x02
#define REG_SETUP_RETR  0x04
#define REG_CHANNEL 	0x05
#define REG_RFSET	    0x06
#define REG_STATUS	    0x07
#define REG_TX		    0x10
#define REG_DYNPD       0x1C
#define REG_FEATURE     0x1D

#define MODE_PROTECTED      0xA0
#define MODE_UNPROTECTED    0xB0
#define WRITE_MODE(x) ((x) | 0x20)
#define READ_MODE(x) (x)

#endif //CANSAT_OLD_NRF24L01_SETTINGS_H
