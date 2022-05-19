/**
 * @author ButterSus
 * @date May 2022
 * @name PORTS
 */

#ifndef CANSAT_PORTS_H
#define CANSAT_PORTS_H

#include <avr/io.h>
#include <stdint.h>

/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTA;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTB;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTC;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTD;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTE;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTF;
/*! @note use it as CS PORT */
extern volatile uint8_t * lpPORTG;

/*! @note use it as DDR */
extern volatile uint8_t * lpDDRA;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRB;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRC;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRD;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRE;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRF;
/*! @note use it as DDR */
extern volatile uint8_t * lpDDRG;

/*! @note use it as PIN */
extern volatile uint8_t * lpPINA;
/*! @note use it as PIN */
extern volatile uint8_t * lpPINB;
/*! @note use it as PIN */
extern volatile uint8_t * lpPINC;
/*! @note use it as PIN */
extern volatile uint8_t * lpPIND;
/*! @note use it as PIN */
extern volatile uint8_t * lpPINE;
/*! @note use it as PIN */
extern volatile uint8_t * lpPINF;
/*! @note use it as PIN */
extern volatile uint8_t * lpPING;

#endif //CANSAT_PORTS_H
