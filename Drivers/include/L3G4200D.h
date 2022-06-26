/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_L3G4200D_H
#define CANSAT_DRIVER_L3G4200D_H

#include "I2C.h"

#ifdef _L3G4200D_
#define DEVICE_ADDRESS 0xD2
#define CALIBRATION_X -0.200075f
#define CALIBRATION_Y -0.220682f
#define CALIBRATION_Z -0.036923f
#define REG_CTRL_1 0x20
#define REG_AXES 0x28
#define REG_CTRL_1_VALUE 0x0F
#define WRITE(x) (x)
#define READ(x) (x | (1<<7))
#endif // _L3G4200D_

class L3G4200D {
public:
    typedef struct {
        float X, Y, Z;
    } data;
    L3G4200D();
    data*read();
};

#endif //CANSAT_DRIVER_L3G4200D_H
