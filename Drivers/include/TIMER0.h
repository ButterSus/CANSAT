/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_TIMER0_H
#define CANSAT_TIMER0_H

#include <avr/interrupt.h>
#include <avr/io.h>

class TIMER0 {
public:
    TIMER0() = default;
    TIMER0(int Hz);
    void enable();
    void disable();
};

extern TIMER0 interfaceTimer0;

#endif //CANSAT_TIMER0_H
