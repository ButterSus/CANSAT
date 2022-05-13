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
    sendR<&CS_PORT, 1 << CS_NUM>(0xB6, WRITE_MODE(0xE0));
    _delay_ms(100);
    uint8_t id = sendR<&CS_PORT, 1 << CS_NUM>(READ_SIGNAL, READ_MODE(0xD0));
    printf("BMP ID: %d\r\n", id);
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
    send<&CS_PORT, 1 << CS_NUM>(0xDA, WRITE_MODE(0xF4));
    _delay_ms(150);
    uint16_t dig_T1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T1));
    int16_t  dig_T2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T2)),
             dig_T3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(READ_MODE(REG_DIG_T3));
    printf("%i %i %i ", dig_T1, dig_T2, dig_T3);

    float dig_P1 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P1),
          dig_P2 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P2),
          dig_P3 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P3),
          dig_P4 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P4),
          dig_P5 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P5),
          dig_P6 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P6),
          dig_P7 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P7),
          dig_P8 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P8),
          dig_P9 = SPI_collect_duo<&CS_PORT, 1 << CS_NUM>(REG_DIG_P9);

    *CS_PORT &= ~(1 << CS_NUM);
    send(READ_MODE(REG_ADC));
    int32_t adc_P = SPI_collect_trio(),
            adc_T = SPI_collect_trio();

    *CS_PORT |=  (1 << CS_NUM);

    auto var1 = ((float)adc_T/16384.0f - (float)dig_T1/1024.0f) * (float)dig_T2;
    auto var2 = (((float)adc_T/131072.0f - (float)dig_T1/8192.0f) * ((float )adc_T/131072.0f - (float)dig_T1/8192.0f)) * (float)dig_T3;
    BMP280_atmosphere.temperature = (var1 + var2)/5120.0f;

    return &BMP280_atmosphere;
}
