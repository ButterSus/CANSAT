/**
 * @author ButterSus
 * @date May 2022
 * @name settings for DS18B20
 */

#ifndef CANSAT_DS18B20_SETTINGS_H
#define CANSAT_DS18B20_SETTINGS_H

#include <WIRE1.h>
#include <stdint.h>

/*! USER INTERFACE */

#define WIRE1_PORT lpPORTE
#define WIRE1_DDR lpDDRE
#define WIRE1_PIN lpPINE
#define WIRE1_NUM 6

/*! CONFIG */

#define CMD_READ_SPD 0xBE
#define CMD_CONVERT_T 0x44

#endif //CANSAT_DS18B20_SETTINGS_H
