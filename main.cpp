/**
 * @author ButterSus
 * @date May 2022
 * @name main.cpp
 */

#include "functions.h"
#include <avr/io.h>

/*! if it's true update runs */
bool run = true;

/**
 * @def main function
 */

int main(){
    setup();
    while(run){
        update();
    }
}
