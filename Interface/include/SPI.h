/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_INTERFACE_SPI_H
#define CANSAT_INTERFACE_SPI_H

#include "Interface/tools.h"

class SPI{
public:
    void send(uint8_t data);
    void send(uint8_t address, uint8_t data);
    uint8_t sendR(uint8_t data);
    uint8_t sendR(uint8_t address, uint8_t data);

    void send(volatile uint8_t*port, uint8_t num, uint8_t data);
    void send(volatile uint8_t*port, uint8_t num, uint8_t address, uint8_t data);
    uint8_t sendR(volatile uint8_t*port, uint8_t num, uint8_t data);
    uint8_t sendR(volatile uint8_t*port, uint8_t num, uint8_t address, uint8_t data);
};

extern SPI interfaceSPI;

#endif //CANSAT_INTERFACE_SPI_H
