/**
 * @author ButterSus
 * @date 06.05.2022
 * @name BMP280
 */

#ifndef CANSAT_BMP280_H
#define CANSAT_BMP280_H

#include "atmosphere.h"

/**
 * @def
 * init BMP280
 */

void BMP280_init();

/**
 * @def
 * BMP280 data read function
 * @return
 * BMP280 atmosphere result
 */

atmosphere*BMP280_read();

#endif //CANSAT_BMP280_H
