#define _BMP280_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "BMP280.h"

BMP280::BMP280()
{
    MODE_SPI;
    interfaceSPI.send(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_CONFIG), REG_CONFIG_VALUE);
    interfaceSPI.send(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_CTRL_MEAS), REG_CTRL_MEAS_VALUE);
}

BMP280::data*BMP280::read()
{
    MODE_SPI;
    static data result;
    float dig_T1 = (unsigned short)(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T1), 0xFF)) |
                   (unsigned short)(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T1 + 1), 0xFF) << 8);
    float dig_T2 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T2), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T2 + 1), 0xFF) << 8);
    float dig_T3 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T3), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_T3 + 1), 0xFF) << 8);
    float dig_P1 = (unsigned short)(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P1), 0xFF)) |
                   (unsigned short)(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P1 + 1), 0xFF) << 8);
    float dig_P2 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P2), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P2 + 1), 0xFF) << 8);
    float dig_P3 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P3), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P3 + 1), 0xFF) << 8);
    float dig_P4 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P4), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P4 + 1), 0xFF) << 8);
    float dig_P5 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P5), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P5 + 1), 0xFF) << 8);
    float dig_P6 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P6), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P6 + 1), 0xFF) << 8);
    float dig_P7 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P7), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P7 + 1), 0xFF) << 8);
    float dig_P8 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P8), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P8 + 1), 0xFF) << 8);
    float dig_P9 = short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P9), 0xFF)) |
                   short(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, READ_MODE(REG_DIG_P9 + 1), 0xFF) << 8);
    CS_PORT&=~(1<<CS_NUM);
    interfaceSPI.send(READ_MODE(REG_ADC));
    float adc_P = float(((int32_t)(interfaceSPI.sendR(0xFF)) << 16) |
            ((int32_t)(interfaceSPI.sendR(0xFF)) << 8) | (int32_t)(interfaceSPI.sendR(0xFF)));
    float adc_T = float(((int32_t)(interfaceSPI.sendR(0xFF)) << 16) |
                        ((int32_t)(interfaceSPI.sendR(0xFF)) << 8) | (int32_t)(interfaceSPI.sendR(0xFF)));
    CS_PORT|=(1<<CS_NUM);
    float var1 = (adc_T/16384.0f - dig_T1/1024.0f) * dig_T2;
    float var2 = ((adc_T/131072.0f - dig_T1/8192.0f) * (adc_T/131072.0f - dig_T1/8192.0f)) * dig_T3;
    float t_fine = var1 + var2;
    result.temperature = (var1 + var2) / 5120.0f;
    var1 = t_fine/2.0f - 64000.0f;
    var2 = var1 * var1 * dig_P6 / 32768.0f;
    var2 = var2 + var1 * dig_P5 * 2.0f;
    var2 = var2 / 4.0f + dig_P4 * 65536.0f;
    var1 = (dig_P3 * var1 * var1 / 524288.0f + dig_P2 * var1) / 524288.0f;
    var1 = (1.0f + var1/32768.0f) * dig_P1;
    float p = 1048576.0f - adc_P;
    p = (p - var2 / 4096.0f) * 6250.0f / var1;
    var1 = dig_P9 * p * p / 2147483648.0f;
    var2 = p * dig_P8 / 32768.0f;
    result.pressure = p + (var1 + var2 + dig_P7) / 16.0f;
    return &result;
}
