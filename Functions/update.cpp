/**
 * @author ButterSus
 * @date 06.05.2022
 * @name update
 */

#include <util/delay.h>
#include <stdio.h>
#include "NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"

#include "SPI.h"

void update(){
    printf("%i\n", (int16_t)(BMP280_read()->temperature));
    _delay_ms(1000);
}
