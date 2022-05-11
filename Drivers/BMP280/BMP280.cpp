/**
 * @author ButterSus
 * @date 06.05.2022
 * @name BMP280
 */

#include "settings.h"
#include "SPI.h"

/**
 * @def
 * init BMP280
 */

void BMP280_init(){
    MODE_SPI;
    send<&CS_PORT, 1<<CS_NUM>(REG_CTRL_MEAS, REG_CTRL_MEAS_VALUE);
}

void BMP280_read(){

}
