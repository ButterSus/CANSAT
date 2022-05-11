#ifndef CANSAT_SEND_H
#define CANSAT_SEND_H

/**
 * @author ButterSus
 * @date 06.05.2022
 * @name send
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
 * send DATA
 * @param DATA \n
 * byte value
 */

static void send(uint8_t DATA){
    SPDR = DATA;
    while(!(SPSR & (1<<SPIF)));
}

/**
 * @def
 * send DATA with ADRESS
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 */

static void send(uint8_t DATA, uint8_t ADDRESS){
    SPDR = ADDRESS;
    while(!(SPSR & (1<<SPIF)));
    SPDR = DATA;
    while(!(SPSR & (1<<SPIF)));
}

/**
 * @def
 * send DATA and return uint8_t
 * @param DATA \n
 * byte value
 */

static uint8_t sendR(uint8_t DATA){
    SPDR = DATA;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

/**
 * @def
 * send DATA with ADDRESS and return uint8_t
 * @param DATA \n
 * byte value
 * @param ADDRESS \n
 * byte value
 */

static uint8_t sendR(uint8_t DATA, uint8_t ADDRESS){
    SPDR = ADDRESS;
    while(!(SPSR & (1<<SPIF)));
    SPDR = DATA;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

/**
 * @def
 * send DATA on selected port
 * @param DATA \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static void send(uint8_t DATA){
    **port=**port&(~num);
    send(DATA);
    **port=**port|(num);
}

/**
 * @def
 * send DATA with ADDRESS on selected port
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

static void send(uint8_t DATA, uint8_t ADDRESS){
    **port=**port&(~num);
    send(ADDRESS);
    send(DATA);
    **port=**port|(num);
}

/**
 * @def
 * send DATA and return uint8_t on selected port
 * @param DATA \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

static uint8_t sendR(uint8_t DATA){
    **port=**port&(~num);
    uint8_t result = sendR(DATA);
    **port=**port|(num);
    return result;
}

/**
 * @def
 * send DATA with ADDRESS and return uint8_t on selected port
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

static uint8_t sendR(uint8_t DATA, uint8_t ADDRESS){
    **port=**port&(~num);
    send(ADDRESS);
    uint8_t result = sendR(DATA);
    **port=**port|(num);
    return result;
}

#endif //CANSAT_SEND_H
