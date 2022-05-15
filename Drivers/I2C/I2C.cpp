/**
 * @author ButterSus
 * @date 11.05.2022
 * @name I2C
 */

#include <avr/io.h>
#include "settings.h"
#include <stdio.h>
#include "RTOS.h"

void I2C_end(){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

/**
 * @def
 * init I2C
 */

void I2C_init(){
    TWBR = 2;
    TWSR = 0;
    PORTD = (1<<PD1) | (1<<PD0);
    DDRD = ~(1<<PD1) & ~(1<<PD0);
    TWCR = (1<<TWINT)|(1<<TWEN);
}

/**
 * @def
 * I2C -> start
 */

uint8_t I2C_start(){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t statusCode = (TWSR & 0xF8);
    if ((statusCode != 0x10) & (statusCode != 0x08))
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return 0;
    }
    return 1;
}

void I2C_send(uint8_t data){
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x28)
    {
        I2C_end();
        return;
    }
}

void I2C_send(uint8_t id, uint8_t data){
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
    I2C_end();
}

void I2C_send(uint8_t id, uint8_t data, uint8_t address){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t stat = TWSR;
    if ((stat & 0xF8) != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        printf("%x %x %d sla+w no ack\r\n", stat, data, address);
        return;
    }
    I2C_send(address);
    I2C_send(data);
    I2C_end();
}

void I2C_send(uint8_t id, uint8_t*data, uint8_t address, uint8_t size){
    if(!I2C_start())
        return;
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
    I2C_end();
}

uint8_t I2C_read(uint8_t id, uint8_t address){
    I2C_start();
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18)
    {
        I2C_end();
        return 0;
    }
    TWDR = READ_MODE(address);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x28)
    {
        I2C_end();
        return 0;
    }
    I2C_start();
    TWDR = READ_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x40)
    {
        I2C_end();
        return 0;
    }
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    uint8_t result = TWDR;
    I2C_end();
    return result;
}

void I2C_read(uint8_t id, uint8_t address, uint8_t size, uint8_t*result){
    if(!I2C_start())
        return;
    /*! ID */
    TWDR = WRITE_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t stat = TWSR & 0xF8;
    if (stat != 0x18)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    /*! ID */

    /*! REGISTER */
    TWDR = READ_MODE(address);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    stat = TWSR & 0xF8;
    if (stat != 0x28)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    /*! REGISTER */

    /*! ID */
    if(!I2C_start())
        RTOS_error(5);
    TWDR = READ_MODE(id);
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x40)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        return;
    }
    /*! ID */

    /*! SENDING ACK */
    for(uint8_t iter = 0; iter < size - 1; iter++){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
        while(!(TWCR & (1<<TWINT)));
        if ((TWSR & 0xF8) != 0x50)
        {
            TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
            return;
        }
        result[iter] = TWDR;
        printf("%x ", result[iter]);
    }
    /*! SENDING ACK */

    /*! SENDING NACK */
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x58)
    {
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

        return;
    }
    result[size - 1] = TWDR;
    printf("%x ", result[size - 1]);
    /*! SENDING NACK */

    I2C_end();
}
