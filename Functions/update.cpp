/**
 * @author ButterSus
 * @date May 2022
 * @name update
 */

#include <util/delay.h>
#include <stdio.h>
#include <math.h>

#define ACCENT 25

#include "NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"
#include "DS18B20.h"
#include "MMC5883MA.h"

void update(){
    NRF24L01_send("%f", 0.3f);
}
