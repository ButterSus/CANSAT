#ifndef CANSAT_SPI_H
#define CANSAT_SPI_H

/**
 * @author ButterSus
 * @date 06.05.2022
 * @name SPI
 */

#include <stdint.h>
#include <avr/io.h>

/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTA = &PORTA;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTB = &PORTB;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTC = &PORTC;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTD = &PORTD;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTE = &PORTE;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTF = &PORTF;
/*! @note use it as CS PORT */
static volatile uint8_t * lpPORTG = &PORTG;

/**
 * @def
 * SPI_send DATA
 * @param DATA \n
 * byte value
 */

static void SPI_send(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

/**
 * @def
 * SPI_send DATA with ADRESS
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 */

static void SPI_send(uint8_t data, uint8_t address){
    SPDR = address;
    while(!(SPSR & (1<<SPIF)));
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

/**
 * @def
 * SPI_send DATA with ADDRESS for SIZE times
 * @param DATA \n
 * pointer to byte value
 * @param SIZE \n
 * byte value
 * @param ADDRESS \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

void SPI_send(uint8_t*data, uint8_t address, uint8_t size){
    **port=**port&(~num);
    SPI_send(address);
    for(uint8_t iter = 0; iter < size; iter++){
        SPI_send(data[iter]);
    }
    **port=**port|(num);
}

/**
 * @def
 * SPI_send DATA and return uint8_t
 * @param DATA \n
 * byte value
 */

static uint8_t SPI_sendR(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

/**
 * @def
 * SPI_send DATA with ADDRESS and return uint8_t
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 */

static uint8_t SPI_sendR(uint8_t data, uint8_t address){
    SPDR = address;
    while(!(SPSR & (1<<SPIF)));
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

/**
 * @def
 * SPI_send DATA on selected port
 * @param DATA \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static void SPI_send(uint8_t data){
    **port=**port&(~num);
    SPI_send(data);
    **port=**port|(num);
}

/**
 * @def
 * SPI_send DATA with ADDRESS on selected port
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static void SPI_send(uint8_t data, uint8_t address){
    **port=**port&(~num);
    SPI_send(address);
    SPI_send(data);
    **port=**port|(num);
}

/**
 * @def
 * SPI_send DATA and return uint8_t on selected port
 * @param DATA \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static uint8_t SPI_sendR(uint8_t data){
    **port=**port&(~num);
    uint8_t result = SPI_sendR(data);
    **port=**port|(num);
    return result;
}

/**
 * @def
 * SPI_send DATA with ADDRESS and return uint8_t on selected port
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static uint8_t SPI_sendR(uint8_t data, uint8_t address){
    **port=**port&(~num);
    SPI_send(address);
    uint8_t result = SPI_sendR(data);
    **port=**port|(num);
    return result;
}

/**
 * @def
 * SPI_send DATA with ADDRESS for SIZE times
 * @param DATA \n
 * pointer to byte value
 * @param SIZE \n
 * byte value
 * @param ADDRESS \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

void SPI_sendR(uint8_t*data, uint8_t address, uint8_t size, uint8_t readSignal){
    **port=**port&(~num);
    SPI_send(address);
    for(uint8_t iter = 0; iter < size; iter++){
        data[iter] = SPI_sendR(readSignal);
    }
    **port=**port|(num);
}

#endif //CANSAT_SPI_H
