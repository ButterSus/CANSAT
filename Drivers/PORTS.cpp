/**
 * @author ButterSus
 * @date May 2022
 * @name PORTS
 */

#include <avr/io.h>
#include <stdint.h>

/*! @note use it as PORT */
volatile uint8_t * lpPORTA = &PORTA;
/*! @note use it as PORT */
volatile uint8_t * lpPORTB = &PORTB;
/*! @note use it as PORT */
volatile uint8_t * lpPORTC = &PORTC;
/*! @note use it as PORT */
volatile uint8_t * lpPORTD = &PORTD;
/*! @note use it as PORT */
volatile uint8_t * lpPORTE = &PORTE;
/*! @note use it as PORT */
volatile uint8_t * lpPORTF = &PORTF;
/*! @note use it as PORT */
volatile uint8_t * lpPORTG = &PORTG;

/*! @note use it as DDR */
volatile uint8_t * lpDDRA = &DDRA;
/*! @note use it as DDR */
volatile uint8_t * lpDDRB = &DDRB;
/*! @note use it as DDR */
volatile uint8_t * lpDDRC = &DDRC;
/*! @note use it as DDR */
volatile uint8_t * lpDDRD = &DDRD;
/*! @note use it as DDR */
volatile uint8_t * lpDDRE = &DDRE;
/*! @note use it as DDR */
volatile uint8_t * lpDDRF = &DDRF;
/*! @note use it as DDR */
volatile uint8_t * lpDDRG = &DDRG;

/*! @note use it as PIN */
volatile uint8_t * lpPINA = &PINA;
/*! @note use it as PIN */
volatile uint8_t * lpPINB = &PINB;
/*! @note use it as PIN */
volatile uint8_t * lpPINC = &PINC;
/*! @note use it as PIN */
volatile uint8_t * lpPIND = &PIND;
/*! @note use it as PIN */
volatile uint8_t * lpPINE = &PINE;
/*! @note use it as PIN */
volatile uint8_t * lpPINF = &PINF;
/*! @note use it as PIN */
volatile uint8_t * lpPING = &PING;
