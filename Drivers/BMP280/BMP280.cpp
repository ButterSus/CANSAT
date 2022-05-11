/**
 * @author ButterSus
 * @date 06.05.2022
 * @name BMP280
 */

#include <stdint.h>
#include "settings.h"
#include "SPI.h"
#include "atmosphere.h"

atmosphere BMP280_atmosphere;

/**
 * @def
 * init BMP280
 */

void BMP280_init(){
    MODE_SPI;
    send<&CS_PORT, 1<<CS_NUM>(REG_CTRL_MEAS, REG_CTRL_MEAS_VALUE);
}

template <volatile uint8_t**port, uint8_t num>

inline int16_t SPI_collect_duo(uint8_t address){
    int16_t result =   sendR<port, num>(address,     READ_SIGNAL);
    result |= (int16_t)sendR<port, num>(address + 1, READ_SIGNAL) << 8;
    return result;
}

template <volatile uint8_t**port, uint8_t num>

inline int32_t SPI_collect_trio(uint8_t address){
    int32_t result =   sendR<port, num>(address,     READ_SIGNAL);
    result |= (int32_t)sendR<port, num>(address + 1, READ_SIGNAL) << 8;
    result |= (int32_t)sendR<port, num>(address + 2, READ_SIGNAL) << 8;
    return result;
}

atmosphere*BMP280_read(){
    MODE_SPI;
    float dig_T1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_T2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_T3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1);

    float dig_P1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P4 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P5 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P6 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P7 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P8 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1),
          dig_P9 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(1);

    auto adc_T = (float)SPI_collect_trio<&CS_PORT, 1 << CS_NUM>(1),
         adc_P = (float)SPI_collect_trio<&CS_PORT, 1 << CS_NUM>(1);

    auto var1 = (adc_T/16384.0f - dig_T1/1024.0f) * dig_T2;
    auto var2 = ((adc_T/131072.0f - dig_T1/8192.0f) * (adc_T/131072.0f - dig_T1/8192.0f)) * dig_T3;
    BMP280_atmosphere.temperature = (var1 + var2)/5120.0f;

    return &BMP280_atmosphere;
}
