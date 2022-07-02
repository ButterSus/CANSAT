/**
 * @author ButterSus
 * @date June 2022
 */

#include "RTOS/RTOS.h"
#include "TIMER0.h"
#include "UART.h"
#include "I2C.h"

#define CLEAR DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; DDRG = 0; \
        PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0; PORTG = 0

void main1(){
    while(1){
        interfaceUART0 << "hello furlaries!" << endl;
    }
}

void main2(){
    while(1){
        interfaceUART1 << "cringe" << endl;
    }
}

I2C interfaceI2C;
TIMER0 interfaceTimer0;
UART interfaceUART0;
UART interfaceUART1;
FILE UART_buf0;
FILE UART_buf1;

volatile void setup(){
    CLEAR;

    /*! UART 1 */
    DDRE &= ~(1<<PE0); /*! 32 - RX0  (READ)   */
    DDRE |=  (1<<PE1); /*! 33 - TX0  (WRITE)  */

    /*! UART 2 */
    PORTE &= ~(1<<PD2);
    PORTE |= (1<<PD3);

    /*! ANOTHER */
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
    DDRD |= (1<<PD4);

    /*! I2C */
    DDRD &= ~(1<<PD0); /*! 25 - SCL   (READ)  */
    DDRD &= ~(1<<PD1); /*! 26 - SDA   (READ)  */

    /*! DEBUG */
    DDRG |=  (1<<PG3);

    static volatile uint8_t*lUCSR0A = &UCSR0A,
                           *lUDR0 = &UDR0;
    auto p = &UART_putc<&lUCSR0A, UDRE0, &lUDR0>(char('0'), (FILE*)(nullptr));
    interfaceUART0 = UART(p,
            &UCSR0A,
            &UCSR0B,
            &UCSR0C,
            &UBRR0H,
            &UBRR0L,
            &UART_buf0);

    Thread(main1, 256, 3);
    Thread(main2, 256, 3).go(TIMER0(256));
}
