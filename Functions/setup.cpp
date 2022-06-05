/**
 * @author ButterSus
 * @date May 2022
 * @name setup
 */

#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "OLD_NRF24L01/NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"
#include "DS18B20.h"
#include "MMC5883MA.h"
#include "I2C.h"
#include "WIRE1.h"
#include "L3G4200D.h"

#define CLEAR DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; DDRG = 0; PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0; PORTG = 0

void portMap(){
    CLEAR;

    /*! UART */
    DDRE &= ~(1<<PE0); /*! 32 - RX0  (READ)   */
    DDRE |=  (1<<PE1); /*! 33 - TX0  (WRITE)  */
    DDRE !=  (1<<PE2); /*! 34 - XCK0 (USELESS)*/
    DDRE |=  (1<<PE3); /*! 35 - OC3A (WRITE)  */
    DDRE |=  (1<<PE4); /*! 36 - 0C3B (WRITE)  */
    DDRE |=  (1<<PE5); /*! 37 - 0C3C (WRITE)  */
    DDRE |=  (1<<PE6); /*! 38 - 1WIRE(WRITE)  */
    DDRE |=  (1<<PE7); /*! 39 - 1WIRE(WRITE)  */

    /*! SPI */
    DDRB |=  (1<<PB0); /*! 8  - SS   (WRITE)  */ /*! FOR OUTPUT */
    DDRB |=  (1<<PB1); /*! 9  - SCK  (WRITE)  */
    DDRB |=  (1<<PB2); /*! 10 - MOSI (WRITE)  */
    DDRB &= ~(1<<PB3); /*! 11 - MISO (READ)   */

    /*! CS */
    DDRB |=  (1<<PB4); /*! 12 - ADXL345       */
    DDRB |=  (1<<PB5); /*! 13 - BMP280        */
    DDRB |=  (1<<PB6); /*! 14 - NRF24L01 CE   */ /*! RADIO    */
    DDRB |=  (1<<PB7); /*! 15 - NRF24L01 CSN  */ /*! NRF24L01 */

    /*! I2C */
    DDRD &= ~(1<<PD0); /*! 25 - SCL   (READ)  */
    DDRD &= ~(1<<PD1); /*! 26 - SDA   (READ)  */
}

void setup(){
    portMap();
    UART_init();
    I2C_init();

    NRF24L01_init0();
    ADXL345_init();
    BMP280_init();
    MMC5883_init();
    L3G4200D_init();
}
