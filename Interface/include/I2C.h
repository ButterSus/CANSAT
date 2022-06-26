/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_DRIVER_I2C_H
#define CANSAT_DRIVER_I2C_H

#include "Interface/tools.h"

#define I2C_WRITE 0
#define I2C_READ 1
#define GOOD_START 0x08
#define GOOD_REPEATED_START 0x10
#define GOOD_RX_ADDRESS_ACK 0x18
#define GOOD_RX_ADDRESS_NACK 0x20
#define GOOD_RX_DATA_ACK 0x28
#define GOOD_RX_DATA_NACK 0x30
#define GOOD_TX_ADDRESS_ACK 0x40
#define GOOD_TX_ADDRESS_NACK 0x48
#define GOOD_TX_DATA_ACK 0x50
#define GOOD_TX_DATA_NACK 0x58
#define WRITE_MODE(x) (x &~ 1)
#define READ_MODE(x) (x | 1)

class I2C {
public:
    I2C() = default;
    I2C(overloaded);
    void error();
    void start();
    void stop();
    bool gotACK();
    void sendACK();
    void sendNACK();
    void transmitDATA(uint8_t DATA);
    void transmitDATA(uint8_t ADDRESS, uint8_t DATA);
    void transmitSLA_W(uint8_t SLA_W);
};

extern I2C interfaceI2C;

#endif //CANSAT_DRIVER_I2C_H
