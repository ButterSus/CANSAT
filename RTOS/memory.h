/**
 * @author ButterSus
 * @date 11.05.2022
 * @name SYSTEM MEMORY
 */

#ifndef CANSAT_SYSTEM_MEMORY_H
#define CANSAT_SYSTEM_MEMORY_H

#include <stdlib.h>

static void*RTOS_malloc(size_t size){
    return malloc(size);
}

static void*RTOS_calloc(size_t nele, size_t size){
    return calloc(nele, size);
}

#endif //CANSAT_SYSTEM_MEMORY_H
