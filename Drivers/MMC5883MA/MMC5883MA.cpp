/**
 * @author ButterSus
 * @date May 2022
 * @name MMC5883
 */

#include "I2C.h"
#include "settings.h"
#include "face.h"
#include "setjmp.h"
#include <avr/io.h>

face MMC5883MA_face;

static jmp_buf jmpbuf;

/**
 * @def
 * init MMC5883
 */

void MMC5883_init(){
    MODE_I2C;
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_WRITE);
    I2C_transmitData(REG_CONTROL_A);
    if(not I2C_wantToGetMore()) I2C_error();
    I2C_transmitData(REG_CONTROL_A_VALUE);
    I2C_stop();

    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_WRITE);
    I2C_transmitData(REG_CONTROL_B);
    if(not I2C_wantToGetMore()) I2C_error();
    I2C_transmitData(REG_CONTROL_B_VALUE);
    I2C_stop();
}

void MMC5883_measure(){
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_WRITE);
    I2C_transmitData(REG_MODE);
    if(not I2C_wantToGetMore()) I2C_error();
    I2C_transmitData(REG_MODE_VALUE);
    I2C_stop();
}

face*MMC5883_read(){
    MODE_I2C (face*)1;
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_WRITE);
    I2C_transmitData(REG_AXES);
    I2C_start();
    I2C_transmitAddress(DEVICE_ADDRESS + I2C_READ);

    I2C_sendACK();
    int16_t x = (int16_t)TWDR << 8;
    I2C_sendACK();
    x |= TWDR;

    I2C_sendACK();
    int16_t z = (int16_t)TWDR << 8;
    I2C_sendACK();
    z |= TWDR;

    I2C_sendACK();
    int16_t y = (int16_t)TWDR << 8;
    I2C_sendNACK();
    y |= TWDR;

    I2C_stop();
    MMC5883MA_face = {
            (float)x,
            (float)y,
            (float)z,
    };
    return &MMC5883MA_face;
}
