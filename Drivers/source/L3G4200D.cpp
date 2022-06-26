#define _L3G4200D_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "L3G4200D.h"

L3G4200D::L3G4200D()
{
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS);
    interfaceI2C.transmitDATA(REG_CTRL_1, REG_CTRL_1_VALUE);
    interfaceI2C.stop();
}

L3G4200D::data*L3G4200D::read()
{
    static data result;
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.transmitDATA(READ(REG_AXES));
    interfaceI2C.start();
    interfaceI2C.transmitSLA_W(DEVICE_ADDRESS + I2C_WRITE);
    interfaceI2C.sendACK();
    int16_t x = TWDR;
    interfaceI2C.sendACK();
    x |= (int16_t)TWDR << 8;
    interfaceI2C.sendACK();
    int16_t y = TWDR;
    interfaceI2C.sendACK();
    y |= (int16_t)TWDR << 8;
    interfaceI2C.sendACK();
    int16_t z = TWDR;
    interfaceI2C.sendNACK();
    z |= (int16_t)TWDR << 8;
    result.X = x * (250.0f/32768.0f) + CALIBRATION_X;
    result.Y = y * (250.0f/32768.0f) + CALIBRATION_Y;
    result.Z = z * (250.0f/32768.0f) + CALIBRATION_Z;
    return &result;
}
