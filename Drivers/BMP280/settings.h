/**
 * @author ButterSus
 * @date May 2022
 * @name settings for BMP280
 */

#ifndef CANSAT_BMP280_SETTINGS_H
#define CANSAT_BMP280_SETTINGS_H

#include "avr/io.h"

/*! USER INTERFACE */

#define CS_PORT lpPORTB
#define CS_NUM 5

/*! CONFIG */

#define MODE_SPI \
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPHA)|(1<<CPOL)

#define REG_CTRL_MEAS 0xF4
#define REG_DIG_T1 0x88
#define REG_DIG_T2 0x8A
#define REG_DIG_T3 0x8C
#define REG_DIG_P1 0x8E
#define REG_DIG_P2 0x90
#define REG_DIG_P3 0x92
#define REG_DIG_P4 0x94
#define REG_DIG_P5 0x96
#define REG_DIG_P6 0x98
#define REG_DIG_P7 0x9A
#define REG_DIG_P8 0x9C
#define REG_DIG_P9 0x9E
#define REG_ADC 0xF7
#define REG_CONFIG 0xF5

#define REG_CTRL_MEAS_VALUE 0xDB
#define REG_CONFIG_VALUE 0x40

#define READ_SIGNAL 0xff

#define WRITE_MODE(x) (x & ~(1<<7))
#define READ_MODE(x) (x | (1<<7))

#endif //CANSAT_BMP280_SETTINGS_H
