/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_TIMER0_H
#define CANSAT_TIMER0_H

#include <avr/io.h>

class TIMER0 {
public:
    TIMER0() = default;
    TIMER0(int Hz);
    void enable();
    void disable();
};

#endif //CANSAT_TIMER0_H
