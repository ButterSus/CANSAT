/**
 * @author ButterSus
 * @date May 2022
 * @name L3G4200D
 */

#include <avr/io.h>
#include "I2C.h"
#include "settings.h"
#include <setjmp.h>
#include "axes.h"

axes L3G4200D_axes;

static jmp_buf jmpbuf;

void L3G4200D_init(){
    MODE_I2C;
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS);
    I2C_transmitData(REG_CTRL_1);
    I2C_transmitData(REG_CTRL_1_VALUE);
    I2C_stop();
}

axes*L3G4200D_read(){
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_WRITE);
    I2C_transmitData(READ_MODE(REG_AXES));

    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_READ);
    I2C_sendACK();
    int16_t x = TWDR;
    I2C_sendACK();
    x |= (int16_t)TWDR << 8;

    I2C_sendACK();
    int16_t y = TWDR;
    I2C_sendACK();
    y |= (int16_t)TWDR << 8;

    I2C_sendACK();
    int16_t z = TWDR;
    I2C_sendNACK();
    z |= (int16_t)TWDR << 8;

    L3G4200D_axes.x = x * (250.0f/32768.0f) + CALIBRATION_X;
    L3G4200D_axes.y = y * (250.0f/32768.0f) + CALIBRATION_Y;
    L3G4200D_axes.z = z * (250.0f/32768.0f) + CALIBRATION_Z;

    return &L3G4200D_axes;
}
