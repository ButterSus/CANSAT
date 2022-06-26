/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_INTERFACE_UART_H
#define CANSAT_INTERFACE_UART_H

#include "Interface/tools.h"

#include <stdio.h>

#define endl "\r\n"

class UART {
private:
    FILE*out;
public:
    UART() = default;
    UART(int (*putc)(char, FILE *), volatile uint8_t*UCSRnA, volatile uint8_t*UCSRnB, volatile uint8_t*UCSRnC,
         volatile uint8_t*UBRRnH, volatile uint8_t*UBRRnL);
    UART &operator << (char*value);
    UART &operator << (const char*value);
    UART &operator << (float value);
    UART &operator << (double value);

    template<typename type>
    UART &operator << (type value);
};

extern UART interfaceUART0;
extern UART interfaceUART1;

#endif //CANSAT_INTERFACE_UART_H
