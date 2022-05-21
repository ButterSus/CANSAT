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

void update(){
    printf("%f\r\n", DS18B20_read(nullptr));
    _delay_ms(1000);
}
