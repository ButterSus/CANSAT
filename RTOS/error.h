/**
 * @author ButterSus
 * @date 11.05.2022
 * @name SYSTEM ERROR
 */

#ifndef CANSAT_SYSTEM_ERROR_H
#define CANSAT_SYSTEM_ERROR_H

#include <stdio.h>

/*! USER INTERFACE */

#define ERROR_PORT PORTG
#define ERROR_NUM 7

/*! CODE */

/**
 * @def
 * raise error
 * @param ERROR_CODE
 * byte value
 */

void RTOS_error(uint8_t ERROR_CODE){
    ERROR_PORT = 1 << ERROR_NUM;
    while(true){
        printf("ERROR: %i\r\n", ERROR_CODE);
    }
}

#endif //CANSAT_SYSTEM_ERROR_H
