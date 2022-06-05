/**
 * @author ButterSus
 * @date 06.05.2022
 * @name NRF24L01
 */

#ifndef CANSAT_OLD_NRF24L01_H
#define CANSAT_OLD_NRF24L01_H

#include <stdint.h>

/**
 * @def
 * init NRF24L01
 */

void NRF24L01_init0();

/**
 * @def
 * function to send string using NRF24L01
 * @param data \n
 * string value
 */

void NRF24L01_send0(char*data, uint8_t size);

/**
 * @def
 * class to use `NRF24L01_cout`
 */


void nRF_send_other(char * data);

class NRF24L01_iostream{
private:
    char string[33] = {};
    int stringIter = 1, iter = 0;
public:
    NRF24L01_iostream &operator<<(uint8_t src){
        this->string[this->stringIter++] = (char)src;
        return *this;
    }
    NRF24L01_iostream &operator<<(int8_t src){
        return this->operator<<((uint8_t)src);
    }
    NRF24L01_iostream &operator<<(char src){
        return this->operator<<((uint8_t)src);
    }

    NRF24L01_iostream &operator<<(uint16_t src){
        this->string[this->stringIter++] = (char)(src >> 8);
        this->string[this->stringIter++] = (char)(src & 0xFF);
        return *this;
    }
    NRF24L01_iostream &operator<<(int16_t src){
        return this->operator<<((uint16_t)src);
    }

    NRF24L01_iostream &operator<<(uint32_t src){
        this->string[this->stringIter++] = (char)(src >> 24);
        this->string[this->stringIter++] = (char)((src >> 16) & 0xFF);
        this->string[this->stringIter++] = (char)((src >> 8) & 0xFF);
        this->string[this->stringIter++] = (char)(src & 0xFF);
        return *this;
    }
    NRF24L01_iostream &operator<<(int32_t src){
        return this->operator<<((uint32_t)src);
    }
    NRF24L01_iostream &operator<<(float src){
        return this->operator<<((uint32_t)src);
    }
    NRF24L01_iostream &operator<<(double src){
        return this->operator<<((uint32_t)src);
    }

    NRF24L01_iostream &operator<<(char*src){
        this->iter = 0;
        while(src[this->iter] != '\0'){
            this->string[this->stringIter++] = src[this->iter++];
        }
        return *this;
    }

    NRF24L01_iostream &operator<<(NRF24L01_iostream src){
        NRF24L01_send0(this->string, this->stringIter);
        cout << (const char*) this->string << endl;
        this->stringIter = 1;
        return *this;
    }
};

/**
 * @def
 * use to leave `\n` at the end
 */

static NRF24L01_iostream NRF24L01_endl;

/**
 * @def
 * use it to print value
 */

static NRF24L01_iostream NRF24L01_cout;

#endif //CANSAT_OLD_NRF24L01_H
