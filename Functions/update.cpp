/**
 * @author ButterSus
 * @date May 2022
 * @name update
 */

#include <util/delay.h>
#include <stdio.h>
#include <math.h>

#include "NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"
#include "DS18B20.h"
#include "MMC5883MA.h"
#include "L3G4200D.h"

template <typename T, size_t N>
constexpr size_t array_size(T (&)[N]) {
    return N;
}

acceleration ADXL345[5];
static uint32_t iter = -300;

void update(){
//    acceleration*ADXL345_result = ADXL345_read();
//    ADXL345[iter % array_size(ADXL345)].X = ADXL345_result->X;
//    ADXL345[iter % array_size(ADXL345)].Y = ADXL345_result->Y;
//    ADXL345[iter % array_size(ADXL345)].Z = ADXL345_result->Z;
//    printf("source:%i %i %i\r\n", ADXL345_result->X, ADXL345_result->Y, ADXL345_result->Z);
//    ADXL345_result ->X = 0;
//    ADXL345_result ->Y = 0;
//    ADXL345_result ->Z = 0;
//    for(size_t i = 0; i < array_size(ADXL345); i++){
//        ADXL345_result->X += ADXL345[i].X;
//        ADXL345_result->Y += ADXL345[i].Y;
//        ADXL345_result->Z += ADXL345[i].Z;
//    }
//    ADXL345_result->X /= array_size(ADXL345);
//    ADXL345_result->Y /= array_size(ADXL345);
//    ADXL345_result->Z /= array_size(ADXL345);
//    printf("result:%i %i %i\r\n", ADXL345_result->X, ADXL345_result->Y, ADXL345_result->Z);
//    iter++;
    _delay_ms(500);
}
