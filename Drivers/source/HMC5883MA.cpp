#define _HMC5883MA_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "HMC5883MA.h"

HMC5883MA::HMC5883MA()
{
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.transmitDATA(REG_CONTROL_A, REG_CONTROL_A_VALUE);
    interfaceI2C.stop();
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.transmitDATA(REG_CONTROL_B, REG_CONTROL_B_VALUE);
    interfaceI2C.stop();
}

void HMC5883MA::measure()
{
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.transmitDATA(REG_MODE, REG_MODE_VALUE);
    interfaceI2C.stop();
}

HMC5883MA::data*HMC5883MA::read()
{
    static data result;
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.transmitDATA(REG_AXES);
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.sendACK();
    int16_t x = (int16_t)TWDR << 8;
    interfaceI2C.sendACK();
    x |= TWDR;
    interfaceI2C.sendACK();
    int16_t z = (int16_t)TWDR << 8;
    interfaceI2C.sendACK();
    z |= TWDR;
    interfaceI2C.sendACK();
    int16_t y = (int16_t)TWDR << 8;
    interfaceI2C.sendNACK();
    y |= TWDR;
    interfaceI2C.stop();
    result = {
            (float)x,
            (float)y,
            (float)z,
    };
    return &result;
}
