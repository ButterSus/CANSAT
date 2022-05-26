/**
 * @author ButterSus
 * @date May 2022
 * @name update
 */

#include <util/delay.h>
#include <stdio.h>

#include "NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"
#include "DS18B20.h"
#include "MMC5883MA.h"

void update(){
    MMC5883_measure();
    _delay_ms(1000);
    face*result = MMC5883_read();
    if(result == (face*)1)printf("error");
    printf("lol: %f %f %f\r\n", result->x, result->y, result->z);
}
