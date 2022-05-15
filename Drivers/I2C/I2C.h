/**
 * @author ButterSus
 * @date 11.05.2022
 * @name I2C
 */

#ifndef CANSAT_I2C_H
#define CANSAT_I2C_H

#include "settings.h"
#include <stdint.h>
#include <avr/io.h>
#include "RTOS.h"

static void I2C_init(){
    TWBR = 2;
    TWSR = 0;
    PORTD = (1<<PD1) | (1<<PD0);
    DDRD = ~(1<<PD1) & (1<<PD0);
    TWCR = (1<<TWINT)|(1<<TWEN);
}

static void I2C_start(){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t statusCode = (TWSR & 0xF8);
    if ((statusCode != 0x10) | (statusCode != 0x08))
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
}

static void I2C_send(uint8_t data){
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x28)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
}

template <uint8_t id>

static void I2C_send(uint8_t data){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    I2C_send(data);
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

template <uint8_t id>

static void I2C_send(uint8_t data, uint8_t address){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    I2C_send(address);
    I2C_send(data);
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

template <uint8_t id>

static void I2C_send(uint8_t*data, uint8_t address, uint8_t size){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    I2C_send(address);
    for(uint8_t iter = 0; iter < size; iter++){
        I2C_send(data[iter]);
    }
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

template <uint8_t id>

static uint8_t I2C_read(uint8_t address){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return 0;
    }
    TWDR = READ_MODE(address);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return 0;
    }
    I2C_start();
    TWDR = READ_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x40)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return 0;
    }
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    uint8_t result = TWDR;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    return result;
}

template <uint8_t id>

static uint8_t*I2C_read(uint8_t address, uint8_t size){
    auto result = static_cast<uint8_t *>(RTOS_calloc(size, sizeof(uint8_t)));
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return nullptr;
    }
    TWDR = READ_MODE(address);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return nullptr;
    }
    I2C_start();
    TWDR = READ_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x40)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return nullptr;
    }
    for(uint8_t iter = 0; iter < (size - 1); iter++){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
        while(!(TWCR & (1<<TWINT)));
        if ((TWSR & 0xF8) != 0x50)
        {
            TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
            return nullptr;
        }
        result[iter] = TWDR;
    }
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x58)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return nullptr;
    }
    result[-1] = TWDR;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    return result;
}

#endif //CANSAT_I2C_H
