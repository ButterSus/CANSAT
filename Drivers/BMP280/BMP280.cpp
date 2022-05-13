/**
 * @author ButterSus
 * @date 06.05.2022
 * @name BMP280
 */

#include <stdint.h>
#include <util/delay.h>
#include "settings.h"
#include "SPI.h"
#include "atmosphere.h"
#include <stdio.h>

atmosphere BMP280_atmosphere;

/**
 * @def
 * init BMP280
 */

void BMP280_init(){
    MODE_SPI;
    send<&CS_PORT, 1<<CS_NUM>(REG_CONFIG_VALUE, WRITE_MODE(REG_CONFIG));
    send<&CS_PORT, 1<<CS_NUM>(REG_CTRL_MEAS_VALUE, WRITE_MODE(REG_CTRL_MEAS));
}

template <volatile uint8_t**port, uint8_t num>

inline int16_t SPI_collect_duo(uint8_t address){
    int16_t result =   sendR<port, num>(READ_SIGNAL, READ_MODE(address));
    result |= (int16_t)sendR<port, num>(READ_SIGNAL, READ_MODE(address + 1)) << 8;
    return result;
}

inline int32_t SPI_collect_trio(){
    int32_t result = (int32_t)sendR(READ_SIGNAL) << 16;
    result |= (int32_t)sendR(READ_SIGNAL) << 8;
    result |= sendR(READ_SIGNAL);
    return result >> 4;
}

atmosphere*BMP280_read(){
    MODE_SPI;
    float dig_T1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T1)),
          dig_T2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T2)),
          dig_T3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T3));

    float dig_P1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P1)),
          dig_P2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P2)),
          dig_P3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P3)),
          dig_P4 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P4)),
          dig_P5 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P5)),
          dig_P6 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P6)),
          dig_P7 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P7)),
          dig_P8 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P8)),
          dig_P9 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_P9));

    *CS_PORT &= ~(1 << CS_NUM);
    send(READ_MODE(REG_ADC));
    auto adc_P = (float)SPI_collect_trio(),
         adc_T = (float)SPI_collect_trio();

    *CS_PORT |=  (1 << CS_NUM);

    auto var1 = (adc_T/16384.0f - dig_T1/1024.0f) * dig_T2;
    auto var2 = ((adc_T/131072.0f - dig_T1/8192.0f) * (adc_T/131072.0f - dig_T1/8192.0f)) * dig_T3;
    auto t_fine = var1 + var2;
    BMP280_atmosphere.temperature = (var1 + var2)/5120.0f;

    var1 = t_fine/2.0f - 64000.0f;
    var2 = var1 * var1 * dig_P6 / 32768.0f;
    var2 = var2 + var1 * dig_P5 * 2.0f;
    var2 = var2 / 4.0f + dig_P4 * 65536.0f;
    var1 = (dig_P3 * var1 * var1 / 524288.0f + dig_P2 * var1) / 524288.0f;
    var1 = (1.0f + var1/32768.0f) * dig_P1;
    auto p = 1048576.0f - adc_P;
    p = (p - var2 / 4096.0f) * 6250.0f / var1;
    var1 = dig_P9 * p * p / 2147483648.0f;
    var2 = p * dig_P8 / 32768.0f;
    BMP280_atmosphere.pressure = p + (var1 + var2 + dig_P7) / 16.0f;

    return &BMP280_atmosphere;
}
