/**
 * @author ButterSus
 * @date 06.05.2022
 * @name UART
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int UART_connect(char symbol, FILE*);

/**
 * @def
 * stream for stdout
 */

static FILE UART_stream = FDEV_SETUP_STREAM(UART_connect, nullptr, _FDEV_SETUP_WRITE);

/**
 * @def
 * instead of stdout function
 */

int UART_connect(char symbol, FILE*){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = symbol;
    return 0;
}

/**
 * @def
 * init UART
 */

void UART_init(){
    sei();
    UCSR0A = 0x0;
    UCSR0B = 0b10011000;
    UCSR0C = 0b110;
    UBRR0H = 0x0;
    UBRR0L = 0xC;
    stdout = &UART_stream; /*! connecting stdout */
}

/**
 * @def
 * connect interrupts to io
 */

ISR(USART0_RX_vect){
    printf("%c",UDR0);
}