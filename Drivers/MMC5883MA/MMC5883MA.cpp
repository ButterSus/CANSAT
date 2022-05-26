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
jmp_buf jmpbuf;

/**
 * @def
 * init MMC5883
 */

void MMC5883_init(){
    MODE_I2C;
    I2C_start();
    I2C_transmitAddress(0b01100000 + I2C_WRITE);
    I2C_transmitData(0b00001000);
    if(not I2C_wantToGetMore()) I2C_error();
    I2C_transmitData(0b00001000);
    I2C_stop();
}

void MMC5883_measure(){
    MODE_I2C;
    I2C_start();
    I2C_transmitAddress(0b01100000 + I2C_WRITE);
    I2C_transmitData(0b00001000);
    if(not I2C_wantToGetMore()) I2C_error();
    I2C_transmitData(0b00000001);
    I2C_stop();
}

face*MMC5883_read(){
    MODE_I2C (face*)1;
    I2C_start();
    I2C_transmitAddress(0b01100000 + I2C_WRITE);
    printf("adr ");
    I2C_transmitData(0b00000000);
    printf("m1 ");
    I2C_start();
    printf("sr ");
    I2C_transmitAddress(0b01100000 + I2C_READ);
    printf("m2 ");
    I2C_sendACK();
    int16_t x = TWDR;
    printf("x1 ");
    I2C_sendACK();
    x |= (int16_t)TWDR << 8;
    printf("x2 ");


    I2C_sendACK();
    int16_t y = TWDR;
    printf("y1 ");

    I2C_sendACK();
    y |= (int16_t)TWDR << 8;
    printf("y2 ");


    I2C_sendACK();
    int16_t z = TWDR;
    printf("z1 ");

    I2C_sendNACK();
    z |= (int16_t)TWDR << 8;
    printf("z2 ");

    I2C_stop();
    printf("%i %i %i\r\n", x, y, z);
    MMC5883MA_face = {
            (float)x,
            (float)y,
            (float)z,
    };
    return &MMC5883MA_face;
}
