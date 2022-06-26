/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_MMC5883MA_H
#define CANSAT_DRIVER_MMC5883MA_H

#include "I2C.h"

#ifdef _HMC5883MA_
#define DEVICE_ADDRESS 0x3C
#define REG_CONTROL_A 0x00
#define REG_CONTROL_B 0x01
#define REG_MODE 0x02
#define REG_AXES 0x03
#define REG_CONTROL_A_VALUE 0x70 // 0x70
#define REG_CONTROL_B_VALUE 0xA0 // 0xA0
#define REG_MODE_VALUE 0x01 // 0x00
#endif // _HMC5883MA_

class HMC5883MA {
public:
    typedef struct {
        float X, Y, Z;
    } data;
    HMC5883MA();
    void measure();
    data*read();
};

#endif //CANSAT_DRIVER_MMC5883MA_H
