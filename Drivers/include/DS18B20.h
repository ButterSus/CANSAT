/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_DS18B20_H
#define CANSAT_DRIVER_DS18B20_H

#include "WIRE1.h"

#ifdef _DS18B20_
#define WIRE1_PORT PORTE
#define WIRE1_DDR DDRE
#define WIRE1_PIN PINE
#define WIRE1_NUM 7
#define CMD_READ_SCRATCHPAD 0xBE
#define CMD_CONVERT_T 0x44
#endif // _DS18B20_

class DS18B20 {
private:
    uint8_t*ID;
    WIRE1 interfaceWIRE1 = WIRE1(nullptr, nullptr, nullptr, 0);
    void sendID();
public:
    explicit DS18B20(uint8_t*ID = nullptr);
    void measure();
    float read();
};

#endif //CANSAT_DRIVER_DS18B20_H
