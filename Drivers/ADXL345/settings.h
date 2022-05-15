/**
 * @author ButterSus
 * @date 06.05.2022
 * @name SETTINGS FOR ADXL345
 */

#ifndef CANSAT_ADXL345_SETTINGS_H
#define CANSAT_ADXL345_SETTINGS_H

#include <avr/io.h>

/*! USER INTERFACE */

#define CS_PORT lpPORTB
#define CS_NUM 4

/*! CONFIG */

#define MODE_SPI \
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPHA)|(1<<CPOL)

#define REG_DATA_FORMAT 0x31
#define REG_POWER_CTL 0x2D
#define REG_DATAX0 0x32
#define REG_DATAX1 0x33
#define REG_DATAY0 0x34
#define REG_DATAY1 0x35
#define REG_DATAZ0 0x36
#define REG_DATAZ1 0x37

#define REG_DATA_FORMAT_VALUE 0x00
#define REG_POWER_CTL_VALUE 0x08

#define WRITE_MODE(x) ((x) & 0x7F)
#define READ_MODE(x) ((x) | 0x80)

#endif //CANSAT_ADXL345_SETTINGS_H
