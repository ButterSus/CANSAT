/**
 * @author ButterSus
 * @date June 2022
 */

#include "TIMER0.h"

TIMER0::TIMER0(int Hz)
{
    if(Hz<31) Hz=31;
    TCCR0 &=~(0x07);
    switch(Hz){
        case 31 ... 122:{
            TCCR0 |= (1<<CS02)|(1<<CS01)|(1<<CS00);
            OCR0 = 7813/Hz;
            break;
        }
        case 123 ... 244:{
            TCCR0 |= (1<<CS02)|(1<<CS01);
            OCR0 = 31250/Hz;
            break;
        }
        case 245 ... 489:{
            TCCR0 |= (1<<CS02)|(1<<CS00);
            OCR0 = 62500/Hz;
            break;
        }
        case 490 ... 977:{
            TCCR0 |= (1<<CS02);
            OCR0 = 125000/Hz;
            break;
        }
        case 978 ... 3907:{
            TCCR0 |= (1<<CS01)|(1<<CS00);
            OCR0 = 250000/Hz;
            break;
        }
        case 3908 ... 31250:{
            TCCR0 |= (1<<CS01);
            OCR0 = 1000000/Hz;
            break;
        }
        default:{
            TCCR0 |= (1<<CS00);
            OCR0 = 8000000/Hz;
            break;
        }
    }
}

void TIMER0::enable()
{
    TIMSK |= (1<<OCIE0);
}

void TIMER0::disable() {
    TIMSK &= ~(1<<OCIE0);
}
