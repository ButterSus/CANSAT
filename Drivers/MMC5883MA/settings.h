/**
 * @author ButterSus
 * @date May 2022
 * @name SETTINGS FOR MMC5883
 */

#ifndef CANSAT_SETTINGS_H
#define CANSAT_SETTINGS_H

#include <stdio.h>

/*! USER INTERFACE */

static void MMC5883_I2C_error(){
    printf("oh no we have a problem with a protocol named as I2C!!!\r\n");
}

/*! CONFIG */

#define MODE_I2C I2C_jmpbuf=&jmpbuf;if(setjmp(jmpbuf))return

#endif //CANSAT_SETTINGS_H
