/**
 * @author ButterSus
 * @date May 2022
 * @name SETTINGS FOR L3G4200D
 */

#ifndef CANSAT_L3G4200D_SETTINGS_H
#define CANSAT_L3G4200D_SETTINGS_H

/*! USER INTERFACE */

#define DEVICE_ADDRESS 0xD2

#define CALIBRATION_X -0.200075f
#define CALIBRATION_Y -0.220682f
#define CALIBRATION_Z -0.036923f

/*! CONFIG */

#define REG_CTRL_1 0x20
#define REG_AXES 0x28

#define REG_CTRL_1_VALUE 0x0F

#define MODE_I2C I2C_jmpbuf=&jmpbuf;if(setjmp(jmpbuf))return

#define WRITE_MODE(x) (x)
#define READ_MODE(x) (x | (1<<7))

#endif //CANSAT_L3G4200D_SETTINGS_H
