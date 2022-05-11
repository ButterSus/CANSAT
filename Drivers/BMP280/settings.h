/**
 * @author ButterSus
 * @date 06.05.2022
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

#define REG_CTRL_MEAS_VALUE 0xDB

#define READ_SIGNAL 0xff

#endif //CANSAT_BMP280_SETTINGS_H
