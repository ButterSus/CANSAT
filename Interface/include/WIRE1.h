/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_1WIRE_H
#define CANSAT_DRIVER_1WIRE_H

#include "Interface/tools.h"

#define WIRE1_SKIPROM 0xCC
#define WIRE1_MATCHROM 0x55

class WIRE1 {
private:
    volatile uint8_t*port;
    volatile uint8_t*ddr;
    volatile uint8_t*pin;
    uint8_t num;
public:
    WIRE1(volatile uint8_t*port, volatile uint8_t*ddr, volatile uint8_t*pin, uint8_t num);
    void reset();
    bool readBit();
    uint8_t read();
    void write(uint8_t data);
};

#endif //CANSAT_DRIVER_1WIRE_H
