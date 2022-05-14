/**
 * @author ButterSus
 * @date 06.05.2022
 * @name NRF24L01
 */

#ifndef CANSAT_NRF24L01_H
#define CANSAT_NRF24L01_H

/**
 * @def
 * init NRF24L01
 */

void NRF24L01_init();

/**
 * @def
 * function to SPI_send string using NRF24L01
 * @param data \n
 * string value
 */

void NRF24L01_send(char*data);

#endif //CANSAT_NRF24L01_H
