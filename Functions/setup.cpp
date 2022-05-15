/**
 * @author ButterSus
 * @date 06.05.2022
 * @name setup
 */

#include "NRF24L01.h"
#include "UART.h"
#include "ADXL345.h"
#include "BMP280.h"
#include <util/delay.h>

#define CLEAR DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; DDRG = 0; PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0; PORTG = 0

void portMap(){
    CLEAR;

    /*! UART */
    DDRE &= ~(1<<PE0); /*! 32 - RX0  (READ)   */
    DDRE |=  (1<<PE1); /*! 33 - TX0  (WRITE)  */

    /*! SPI  */
    DDRB |=  (1<<PB0); /*! 8  - SS   (WRITE)  */ /*! FOR OUTPUT */
    DDRB |=  (1<<PB1); /*! 9  - SCK  (WRITE)  */
    DDRB |=  (1<<PB2); /*! 10 - MOSI (WRITE)  */
    DDRB &= ~(1<<PB3); /*! 11 - MISO (READ)   */

    /*! CS   */
    DDRB |=  (1<<PB4); /*! 12 - ADXL345       */
    DDRB |=  (1<<PB5); /*! 13 - BMP280        */
    DDRB |=  (1<<PB6); /*! 14 - NRF24L01 CE   */ /*! RADIO    */
    DDRB |=  (1<<PB7); /*! 15 - NRF24L01 CSN  */ /*! NRF24L01 */

    PORTB &= ~(1<<PB5);
    PORTB |= (1<<PB4);
    PORTB |= (1<<PB5);
    PORTB &= ~(1<<PB6);
    PORTB |= (1<<PB7);
}

void setup(){
    portMap();
    UART_init();
    ADXL345_init();
    NRF24L01_init();
    BMP280_init();
}
