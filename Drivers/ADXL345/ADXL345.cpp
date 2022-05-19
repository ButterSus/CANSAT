/**
 * @author ButterSus
 * @date May 2022
 * @name ADXL345
 */

#include "settings.h"
#include "SPI.h"
#include "acceleration.h"

/*! result of ADXL345_read */
acceleration ADXL345_acceleration;

/**
 * @def
 * init ADXL345
 */

void ADXL345_init(){
    MODE_SPI;
    SPI_send<&CS_PORT, 1 << CS_NUM>(REG_DATA_FORMAT_VALUE, WRITE_MODE(REG_DATA_FORMAT));
    SPI_send<&CS_PORT, 1 << CS_NUM>(REG_POWER_CTL_VALUE, WRITE_MODE(REG_POWER_CTL));
}

/**
 * @def
 * ADXL345 data read function
 * @return
 * ADXL345 acceleration result
 */

acceleration*ADXL345_read(){
    MODE_SPI;
    ADXL345_acceleration.X = (short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAX0))) |
                             ((short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAX1))) << 8);
    ADXL345_acceleration.Y = (short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAY0))) |
                             ((short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAY1))) << 8);
    ADXL345_acceleration.Z = (short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAZ0))) |
                             ((short)(SPI_sendR<&CS_PORT, 1 << CS_NUM>(0xFF, READ_MODE(REG_DATAZ1))) << 8);
    return &ADXL345_acceleration;
}
