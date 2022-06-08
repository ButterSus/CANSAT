/**
 * @author ButterSus
 * @date May 2022
 * @name update
 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

int getSqrt(int val){
    asm(
            "\r\n"
            :
            [a]"=&r"(val)
            :
            "r"(val)
            );
}

void update(){
    cout << getSqrt(1) << endl;
}

