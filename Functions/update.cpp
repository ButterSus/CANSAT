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

char format[32];

void update(){
    printf("%f\n", (BMP280_read()->temperature));
   // acceleration*result = ADXL345_read();
   // sprintf(format, "F6 3 3 1 1 1 1 %i %i %i\r\n", result->X, result->Y, result->Z);
   // NRF24L01_send(format);
    _delay_ms(100);
}
