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
    sendM<&CSN_PORT, 1<<CSN_NUM>(REG_TXADDR_VALUE, WRITE_MODE(REG_TXADDR), 5);
    sendM<&CSN_PORT, 1<<CSN_NUM>(REG_RXADDR_VALUE, WRITE_MODE(REG_RXADDR), 5);
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_STATUS_VALUE, WRITE_MODE(REG_STATUS));

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_EN_AA_VALUE, WRITE_MODE(REG_EN_AA));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_EN_RXADDR_VALUE, WRITE_MODE(REG_EN_RXADDR));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_SETUP_AW, WRITE_MODE(REG_SETUP_AW_VALUE));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_CHANNEL_VALUE, WRITE_MODE(REG_CHANNEL));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_RFSET_VALUE, WRITE_MODE(REG_RFSET));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_CONFIG_VALUE, WRITE_MODE(REG_CONFIG));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_SETUP_RETR_VALUE, WRITE_MODE(REG_SETUP_RETR));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_DYNPD_VALUE, WRITE_MODE(REG_DYNPD));
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_FEATURE_VALUE, WRITE_MODE(REG_FEATURE));

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_STATUS_VALUE, WRITE_MODE(REG_STATUS));
}

bool NRF24L01_isDone(){
    if(SPI_sendR<&CSN_PORT, 1 << CSN_NUM>(0xFF, READ_MODE(0x07)) & (1<<5)){
        SPI_send<&CSN_PORT, 1 << CSN_NUM>(0b00100000, WRITE_MODE(0x07));
        return true;
    }
    return false;
}

uint8_t NRF24L01_iter;

/**
 * @def
 * function to SPI_send string using NRF24L01
 * @param data \n
 * string value
 */

void NRF24L01_transmit(char*data, int size){
    MODE_SPI;
    NRF24L01_iter = 0;
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_CHANNEL_VALUE,REG_CHANNEL);
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(REG_STATUS_VALUE, REG_STATUS);
    SPI_send<&CSN_PORT, 1 << CSN_NUM>(0xE2);
    *CSN_PORT &= ~(1<<CSN_NUM);
    SPI_send(MODE_PROTECTED);
    for(int iter = 0; iter < size; iter++){
        SPI_send(data[iter]);
    }
    do{
        if(SPI_sendR<&CSN_PORT, 1 << CSN_NUM>(0xFF, READ_MODE(0x17)) & (1<<4)){
            break;
        }
        *CE_PORT |=  (1<<CE_NUM);
        _delay_us(CE_DELAY);
        *CE_PORT &= ~(1<<CE_NUM);
        SPI_send(CMD_FLUSH);
        *CSN_PORT |=  (1<<CSN_NUM);
        NRF24L01_iter++;
    }
    while(not NRF24L01_isDone() and (NRF24L01_iter < 90));
}
