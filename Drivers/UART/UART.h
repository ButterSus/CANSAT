/**
 * @author ButterSus
 * @date May 2022
 * @name UART
 */

#ifndef CANSAT_UART_H
#define CANSAT_UART_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @def
 * init UART
 */

void UART_init();

/**
 * @def
 * class to use `cout`
 */

class AVR_iostream{
public:
    AVR_iostream &operator << (AVR_iostream src){
        printf("\r\n");
        return *this;
    }
    AVR_iostream &operator << (const char*src){
        printf("%s", src);
        return *this;
    }
    AVR_iostream &operator << (float src){
        printf("%f", src);
        return *this;
    }
    AVR_iostream &operator << (double src){
        printf("%lf", src);
        return *this;
    }
    template <typename type>
    AVR_iostream &operator << (type src){
        printf("%d", src);
        return *this;
    }
};

/**
 * @def
 * use to leave `\n` at the end
 */

static AVR_iostream endl;

/**
 * @def
 * use it to print value
 */

static AVR_iostream cout;

#endif //CANSAT_UART_H
