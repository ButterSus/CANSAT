/**
 * @author ButterSus
 * @date June 2022
 */

#include "UART.h"
#include "TIMER0.h"

void setup();

int main(){
    DDRG |= (1 << PG3);
    PORTG |= (1 << PG3);
    _delay_ms(3000);
    asm volatile("sei");
    setup();
    while(1);
}
