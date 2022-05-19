/**
 * @author ButterSus
 * @date May 2022
 * @name main.cpp
 */

#include "functions.h"

/*! if true -> update runs */
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
