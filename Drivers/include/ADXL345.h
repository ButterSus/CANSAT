/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_ADXL345_H
#define CANSAT_DRIVER_ADXL345_H

#include "SPI.h"

#ifdef _ADXL345_
#define CS_PORT PORTB
#define CS_NUM 4
#define MODE_SPI SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPHA)|(1<<CPOL)
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
#endif // _ADXL345_

class ADXL345 {
public:
    typedef struct {
        uint16_t X, Y, Z;
    } data;
    ADXL345();
    data*read();
};

#endif //CANSAT_DRIVER_ADXL345_H
