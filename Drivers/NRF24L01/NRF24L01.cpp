/**
 * @author ButterSus
 * @date May 2022
 * @name NRF24L01
 */

#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "settings.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * @def
 * SPI_send multiple data
 * @param DATA \n
 * pointer to byte value
 * @param SIZE \n
 * byte value
 * @param ADDRESS \n
 * byte value
 * @tparam PORT \n
 * CS port
 * @tparam NUM \n
 * CS num
 */

template <volatile uint8_t**port, uint8_t num>

void sendM(uint8_t*data, uint8_t address, uint8_t size){
    **port=**port&(~num);
    SPI_send(WRITE_MODE(address));
    for(uint8_t iter = 0; iter < size; iter++){
        SPI_send(data[iter]);
    }
    **port=**port|(num);
}

/**
 * @def
 * init NRF24L01
 */

void NRF24L01_init(){
    MODE_SPI;
    *CE_PORT |= (1<<CE_NUM);
    _delay_us(CE_DELAY);
    *CE_PORT &= ~(1<<CE_NUM);
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(CMD_FLUSH);
    sendM<&CSN_PORT, 1<<CSN_NUM>(REG_TXADDR_VALUE, WRITE_MODE(REG_TX), 5);
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_STATUS_VALUE, WRITE_MODE(REG_STATUS));

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_AA_EN_VALUE, WRITE_MODE(REG_EN_AA));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_RXADDR_VALUE, WRITE_MODE(REG_RXADDR));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_CHANNEL_VALUE, WRITE_MODE(REG_CHANNEL));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_RFSET_VALUE, WRITE_MODE(REG_RFSET));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_CONFIG_VALUE, WRITE_MODE(REG_CONFIG));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_SETUP_RETR_VALUE, WRITE_MODE(REG_SETUP_RETR));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_DYNPD_VALUE, WRITE_MODE(REG_DYNPD));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_FEATURE_VALUE, WRITE_MODE(REG_FEATURE));

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_STATUS_VALUE, WRITE_MODE(REG_STATUS));
}

/**
 * @def
 * function to SPI_send string using NRF24L01
 * @param data \n
 * string value
 */

void NRF24L01_transmit(char*data, int size){
    MODE_SPI;
    *CSN_PORT &= ~(1<<CSN_NUM);
    SPI_send(MODE_UNPROTECTED);
    for(int iter = 0; iter < size; iter++){
        SPI_send(data[iter]);
    }
    *CE_PORT |=  (1<<CE_NUM);
    _delay_us(CE_DELAY);
    *CE_PORT &= ~(1<<CE_NUM);
    SPI_send(CMD_FLUSH);
    *CSN_PORT |=  (1<<CSN_NUM);
}

char NRF24L01_buffer[33];

void NRF24L01_send(const char*__string, ...){
    va_list vl;
    int iter = 0, stringIter = 0;
    va_start(vl, __string);
    while(__string[iter] != '\0'){
        if(__string[iter] == '%'){
            iter++;
            switch(__string[iter]){
                case 'c':
                case '1':{
                    NRF24L01_buffer[stringIter++] = va_arg(vl, uint16_t);
                    break;
                }
                case 'i':
                case '2':{
                    union{
                        char bytes[2];
                        uint16_t value;
                    }result;
                    result.value = va_arg(vl, uint16_t);
                    NRF24L01_buffer[stringIter++] = result.bytes[0];
                    NRF24L01_buffer[stringIter++] = result.bytes[1];
                    break;
                }
                case 'z':{
                    iter++;
                    if(__string[iter]!='u') break;
                }
                case 'f':
                case '4':{
                    union{
                        char bytes[4];
                        uint32_t value;
                    }result;
                    result.value = va_arg(vl, uint32_t);
                    NRF24L01_buffer[stringIter++] = result.bytes[0];
                    NRF24L01_buffer[stringIter++] = result.bytes[1];
                    NRF24L01_buffer[stringIter++] = result.bytes[2];
                    NRF24L01_buffer[stringIter++] = result.bytes[3];
                    break;
                }
                case 's':{
                    uint8_t length = va_arg(vl, uint8_t);
                    char*result = va_arg(vl, char*);
                    for(uint8_t iterator = 0; iterator < (length - 1); iterator++){
                        NRF24L01_buffer[stringIter++] = result[iterator];
                    }
                    break;
                }
            }
        }
        else{
            NRF24L01_buffer[stringIter++] = __string[iter];
        }
        iter++;
    }
    va_end(vl);
    NRF24L01_buffer[stringIter] = '\0';
    NRF24L01_transmit(NRF24L01_buffer, stringIter + 1);
}
