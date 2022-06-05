/**
 * @author ButterSus
 * @date May 2022
 * @name DS18B20
 */

#ifndef CANSAT_DS18B20_H
#define CANSAT_DS18B20_H

#include <stdint.h>

void DS18B20_ConvertT(uint8_t*id);
float DS18B20_read(uint8_t*id);

#endif //CANSAT_DS18B20_H
