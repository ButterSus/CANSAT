/**
 * @author ButterSus
 * @date May 2022
 * @name Navigation System
 */

#include <stdio.h>
#include <avr/io.h>
#include <string.h>

#include "ADXL345.h"
#include "L3G4200D.h"
#include "MMC5883MA.h"

char ISR_string[128];
static uint8_t iter = 0;

void ISR_handler(char value){
    if(value != '$'){
        ISR_string[iter++] = value;
        return;
    }
    ISR_string[iter] = '\0';
    iter = 0;

    printf("%s", ISR_string);
    strtok(ISR_string, ","); // id
    strtok(nullptr, ","); // time
    char*lol=strtok(nullptr, ",");
    if(lol[0] != 'A'){
        printf("%s", lol);
        return;
    } // veracity
    printf("ok");
}
