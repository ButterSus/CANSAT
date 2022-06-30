/**
 * @author ButterSus
 * @date June 2022
 */

#include "TIMER0.h"

void setup();

int main(){
    DDRG |= (1 << PG3);
    PORTG |= (1 << PG3);
    setup();
}
