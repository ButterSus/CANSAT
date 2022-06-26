/**
 * @author ButterSus
 * @date June 2022
 */

#include "SPI.h"

void SPI::send(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

void SPI::send(uint8_t address, uint8_t data){
    SPDR = address;
    while(!(SPSR & (1<<SPIF)));
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI::sendR(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

uint8_t SPI::sendR(uint8_t data, uint8_t address){
    SPDR = address;
    while(!(SPSR & (1<<SPIF)));
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

void SPI::send(volatile uint8_t*port, uint8_t num, uint8_t data){
    *port&=~num;
    send(data);
    *port|=num;
}

void SPI::send(volatile uint8_t*port, uint8_t num, uint8_t address, uint8_t data){
    *port&=~num;
    send(address);
    send(data);
    *port|=num;
}

uint8_t SPI::sendR(volatile uint8_t*port, uint8_t num, uint8_t data){
    *port&=~num;
    uint8_t result = sendR(data);
    *port|=num;
    return result;
}

uint8_t SPI::sendR(volatile uint8_t*port, uint8_t num, uint8_t address, uint8_t data){
    *port&=~num;
    send(address);
    uint8_t result = sendR(data);
    *port|=num;
    return result;
}

SPI interfaceSPI = SPI();
