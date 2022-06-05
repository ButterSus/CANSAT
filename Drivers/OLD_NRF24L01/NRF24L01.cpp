/**
 * @author ButterSus
 * @date 06.05.2022
 * @name NRF24L01
 */

#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>

/**
 * @def
 * send multiple data
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

void sendM0(uint8_t*data, uint8_t address, uint8_t size){
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

void NRF24L01_init0(){
    MODE_SPI;
    *CE_PORT |= (1<<CE_NUM);
    _delay_us(CE_DELAY);
    *CE_PORT &= ~(1<<CE_NUM);
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(CMD_FLUSH);
    sendM0<&CSN_PORT, 1<<CSN_NUM>(REG_TXADDR_VALUE, WRITE_MODE(REG_TX), 5);

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_AA_EN_VALUE, WRITE_MODE(REG_EN_AA));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_RXADDR_VALUE, WRITE_MODE(REG_RXADDR));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_CHANNEL_VALUE, WRITE_MODE(REG_CHANNEL));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_RFSET_VALUE, WRITE_MODE(REG_RFSET));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_CONFIG_VALUE, WRITE_MODE(REG_CONFIG));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_SETUP_RETR_VALUE, WRITE_MODE(REG_SETUP_RETR));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_DYNPD_VALUE, WRITE_MODE(REG_DYNPD));
    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_FEATURE_VALUE, WRITE_MODE(REG_FEATURE));

    /*! SETUP CONFIG */

    SPI_send<&CSN_PORT, 1<<CSN_NUM>(REG_STATUS_VALUE, WRITE_MODE(REG_STATUS));
}

/**
 * @def
 * function to send string using NRF24L01
 * @param data \n
 * string value
 */

void NRF24L01_send0(char*data, uint8_t size){
    MODE_SPI;
    *CSN_PORT &= ~(1<<CSN_NUM);
    SPI_send(MODE_UNPROTECTED);
    for(uint8_t iter = 0; iter < size; iter++){
        SPI_send(data[iter]);
    }
    *CE_PORT |=  (1<<CE_NUM);
    _delay_us(CE_DELAY);
    *CE_PORT &= ~(1<<CE_NUM);
    _delay_us(CE_DELAY);
    SPI_send(CMD_FLUSH);
    *CSN_PORT |=  (1<<CSN_NUM);
}
