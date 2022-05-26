/**
 * @author ButterSus
 * @date May 2022
 * @name I2C
 */

#include <avr/io.h>
#include "settings.h"
#include <stdio.h>
#include <setjmp.h>

/*!
 * e.g WRITE_MODE:
 * I2C_start();
 * I2C_transmitAddress(WRITE_MODE(device));
 * if(not I2C_wantToGetMore) I2C_error();
 * I2C_transmitData(data);
 * I2C_stop();
 *
 * e.g READ_MODE:
 * I2C_start();
 * I2C_transmitAddress(WRITE_MODE(device));
 * I2C_transmitData(address);
 * I2C_start();
 * I2C_transmitAddress(READ_MODE(device));
 * I2C_sendNACK();
 * uint8_t result = TWDR;
 * I2C_stop();
 */

jmp_buf*I2C_jmpbuf;

/**
 * @def
 * wait while command is unfinished
 */

void I2C_await(...){
    while (!(TWCR & (1<<TWINT)));
}

/**
 * @def
 * return true if got ACK else false
 */

bool I2C_wantToGetMore(){
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    return (status == GOOD_RX_ADDRESS_ACK) or (status == GOOD_RX_DATA_ACK);
}

/**
 * @def
 * init error
 */

void I2C_error(){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    longjmp(*I2C_jmpbuf, true);
}

/**
 * @def
 * stop I2C
 */

void I2C_stop(){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

/**
 * @def
 * send ACK
 */

void I2C_sendACK(){
    I2C_await(TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if(status != GOOD_TX_DATA_ACK)
    {
        I2C_error();
    }
}

/**
 * @def
 * send NACK
 */

void I2C_sendNACK(){
    I2C_await(TWCR = (1<<TWINT)|(1<<TWEN));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if(status != GOOD_TX_DATA_NACK)
    {
        I2C_error();
    }
}

/**
 * @def
 * init I2C
 */

void I2C_init(){
    TWBR = 0x02;
    TWSR &= ~((1<<TWPS0) | (1<<TWPS1));
    TWCR = (1<<TWINT)|(1<<TWEN);
}

/**
 * @def
 * start condition
 */

void I2C_start(){
    I2C_await(TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_START) & (status != GOOD_REPEATED_START)){
        I2C_error();
    }
}

/**
 * @def
 * transmit DATA
 */

void I2C_transmitData(uint8_t data){
    TWDR = data;
    I2C_await(TWCR = (1<<TWINT)|(1<<TWEN));
    int8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_RX_DATA_ACK) & (status != GOOD_RX_DATA_NACK)){
        I2C_error();
    }
}

/**
 * @def
 * transmit SLA_W
 */

void I2C_transmitAddress(uint8_t address){
    TWDR = address;
    I2C_await(TWCR = (1<<TWINT)|(1<<TWEN));
    int8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_RX_ADDRESS_ACK) & (status != GOOD_RX_ADDRESS_NACK) & (status != GOOD_TX_ADDRESS_ACK) & (status != GOOD_TX_ADDRESS_NACK)){
        I2C_error();
    }
    if((status != GOOD_RX_ADDRESS_ACK) & (status != GOOD_TX_ADDRESS_ACK)){
        printf("ack error adr %x ", (status & 0xF8));
        I2C_error();
    }
}