/**
 * @author ButterSus
 * @date 11.05.2022
 * @name I2C
 */

#ifndef CANSAT_I2C_H
#define CANSAT_I2C_H

#include <stdint.h>
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

#define I2C_WRITE 0
#define I2C_READ 1

extern jmp_buf*I2C_jmpbuf;

/**
 * @def
 * return true if got ACK else false
 */

bool I2C_wantToGetMore();

/**
 * @def
 * init error
 */

void I2C_error();

/**
 * @def
 * stop I2C
 */

void I2C_stop();

/**
 * @def
 * send ACK
 */

void I2C_sendACK();

/**
 * @def
 * send NACK
 */

void I2C_sendNACK();

/**
 * @def
 * init I2C
 */

void I2C_init();

/**
 * @def
 * start condition
 */

void I2C_start();

/**
 * @def
 * transmit DATA
 */

void I2C_transmitData(uint8_t data);

/**
 * @def
 * transmit SLA_W
 */

void I2C_transmitAddress(uint8_t address);

#endif //CANSAT_I2C_H