#define _ADXL345_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "ADXL345.h"

ADXL345::ADXL345()
{
    MODE_SPI;
    interfaceSPI.send(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATA_FORMAT), REG_DATA_FORMAT_VALUE);
    interfaceSPI.send(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_POWER_CTL), REG_POWER_CTL_VALUE);
}

ADXL345::data*ADXL345::read()
{
    MODE_SPI;
    static data result;
    result.X = sb2b(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAX0), 0xFF),
                    interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAX1), 0xFF));
    result.Y = sb2b(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAY0), 0xFF),
                    interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAY1), 0xFF));
    result.Z = sb2b(interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAZ0), 0xFF),
                    interfaceSPI.sendR(&CS_PORT, 1 << CS_NUM, WRITE_MODE(REG_DATAZ1), 0xFF));
    return &result;
}
