/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_INTERFACE_UART_H
#define CANSAT_INTERFACE_UART_H

#include "Interface/tools.h"

#include <stdio.h>

#define endl "\r\n"
#define UART_REGISTERS(x) &UCSR ##x ##A, &UCSR ##x ##B, &UCSR ##x ##C, &UBRR ##x ##H, &UBRR ##x ##L
#define PUTC_REGISTERS(x) (uint8_t*)(&UCSR ##x ##A), (uint8_t)(UDRE ##x), (uint8_t*)(&UDR ##x)

template <volatile uint8_t**UCSRnA, uint8_t UDREn, volatile uint8_t**UDRn>
int UART_putc(char data, FILE*){
    while(!(**UCSRnA & (1 << UDREn)));
    **UDRn = data;
    return 0;
}

class UART {
private:
    FILE*out;
public:
    UART() = default;
    UART(int (*putc)(char, FILE *), volatile uint8_t*UCSRnA, volatile uint8_t*UCSRnB, volatile uint8_t*UCSRnC,
         volatile uint8_t*UBRRnH, volatile uint8_t*UBRRnL, FILE*FILE_buffer);
    UART &operator << (char*value);
    UART &operator << (const char*value);
    UART &operator << (float value);
    UART &operator << (double value);
    UART &operator << (int value);

    template<typename type>
    UART &operator << (type value);
};

extern UART interfaceUART0;
extern UART interfaceUART1;

#endif //CANSAT_INTERFACE_UART_H
