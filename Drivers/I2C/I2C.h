/**
 * @author ButterSus
 * @date 11.05.2022
 * @name I2C
 */

#ifndef CANSAT_I2C_H
#define CANSAT_I2C_H

#include <stdint.h>

/**
 * @def
 * init I2C
 */

void I2C_init();

void I2C_send(uint8_t data);

void I2C_send(uint8_t id, uint8_t data);

void I2C_send(uint8_t id, uint8_t data, uint8_t address);

void I2C_send(uint8_t id, uint8_t*data, uint8_t address, uint8_t size);

uint8_t I2C_read(uint8_t id, uint8_t address);

void I2C_read(uint8_t id, uint8_t address, uint8_t size, uint8_t*result);

void I2C_end();

void I2C_start();

#endif //CANSAT_I2C_H
