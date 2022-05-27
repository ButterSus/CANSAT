/**
 * @author ButterSus
 * @date May 2022
 * @name SETTINGS FOR MMC5883
 */

#ifndef CANSAT_SETTINGS_H
#define CANSAT_SETTINGS_H

#include <stdio.h>

/*! USER INTERFACE */

#define DEVICE_ADDRESS 0x3C

/*! CONFIG */

#define MODE_I2C I2C_jmpbuf=&jmpbuf;if(setjmp(jmpbuf))return

#define REG_CONTROL_A 0x00
#define REG_CONTROL_B 0x01
#define REG_MODE 0x02
#define REG_AXES 0x03

#define REG_CONTROL_A_VALUE 0x70 // 0x70
#define REG_CONTROL_B_VALUE 0xA0 // 0xA0
#define REG_MODE_VALUE 0x01 // 0x00

#endif //CANSAT_SETTINGS_H
