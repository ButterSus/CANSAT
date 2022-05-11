/**
 * @author ButterSus
 * @date 06.05.2022
 * @name BMP280
 */

#ifndef CANSAT_BMP280_H
#define CANSAT_BMP280_H

#include "atmosphere.h"

void BMP280_init();
atmosphere*BMP280_read();

#endif //CANSAT_BMP280_H
