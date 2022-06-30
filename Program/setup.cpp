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

UART interfaceUART0;
UART interfaceUART1;
I2C interfaceI2C;
extern uint32_t taskPoint;

int putc0(char data, FILE*){
    while(!(UCSR0A & (1<<UDRE0)));
    interfaceTimer0.disable();
    UDR0 = data;
    interfaceTimer0.enable();
    return 0;
}

int putc1(char data, FILE*){
    while(!(UCSR1A & (1<<UDRE1)));
    interfaceTimer0.disable();
    UDR1 = data;
    interfaceTimer0.enable();
    return 0;
}

void main1(){
    while (1){
        PORTG |= (1 << PG3);
        interfaceUART0 << "hello furlaries!" << " " << (int)SP << " " << (int)taskPoint << endl;
    }
}

void main2(){
    while (1){
        PORTG &=~(1 << PG3);
        interfaceUART0 << "hallo guys!" << " " << (int)SP << " " << (int)taskPoint << endl;
    }
}

TIMER0 interfaceTimer0;
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

    interfaceUART0 = UART(putc0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0H, &UBRR0L, &UART_buf0);
    interfaceUART1 = UART(putc1, &UCSR1A, &UCSR1B, &UCSR1C, &UBRR1H, &UBRR1L, &UART_buf1);
    Thread(main1, 100);
    Thread(main2, 100);
    interfaceTimer0 = TIMER0(128);
    Thread::go(interfaceTimer0, main2);
}
