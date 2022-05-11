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

void update(){
    printf("%d", (int16_t)(100 * BMP280_read()->temperature));
}
