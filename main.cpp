/**
 * @author ButterSus
 * @date 06.05.2022
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
