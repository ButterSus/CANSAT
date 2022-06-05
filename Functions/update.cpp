/**
 * @author ButterSus
 * @date May 2022
 * @name update
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "UART.h"

#include "OLD_NRF24L01/NRF24L01.h"
#include "ADXL345.h"
#include "BMP280.h"
#include "DS18B20.h"
#include "MMC5883MA.h"
#include "L3G4200D.h"

char PAKET1[32];
char PAKET2[32];
char PAKET3[32];
char PAKET4[32];
uint8_t T_iter;

void update(){
    T_iter++;
    acceleration*ADXL345 = ADXL345_read();
    sprintf(PAKET1, "A: %d %d %d\n", ADXL345->X, ADXL345->Y, ADXL345->Z);
    printf("%s", PAKET1);
    NRF24L01_send0(PAKET1, strlen(PAKET1) + 1);
    axes*L3G = L3G4200D_read();
    sprintf(PAKET2, "G:%.2f %.2f %.2f\n", L3G->x, L3G->y, L3G->z);
    printf("%s", PAKET2);
    NRF24L01_send0(PAKET2, strlen(PAKET2) + 1);
    MMC5883_measure();
    _delay_ms(10);
    face*HMC = MMC5883_read();
    sprintf(PAKET3, "M:%.2f %.2f %.2f\n", HMC->x, HMC->y, HMC->z);
    printf("%s", PAKET3);
    NRF24L01_send0(PAKET3, strlen(PAKET3) + 1);
    atmosphere*BMP280 = BMP280_read();
    _delay_ms(500);
    sprintf(PAKET4, "W:%.2f %.2f %.2f\n", DS18B20_read(nullptr), BMP280->TEMP, BMP280->PRESS);
    printf("%s", PAKET4);
    NRF24L01_send0(PAKET4, strlen(PAKET4) + 1);
    if(T_iter > 2)
    {
        DS18B20_ConvertT(nullptr);
        T_iter = 0;
    }
//    NRF24L01_send0(":Hello world", 13);
//    _delay_ms(100);
}
