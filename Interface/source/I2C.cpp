/**
 * @author ButterSus
 * @date June 2022
 */

#include "I2C.h"

I2C::I2C(overloaded)
{
    TWBR = 0x02;
    TWSR &= ~((1<<TWPS0) | (1<<TWPS1));
    TWCR = (1<<TWINT)|(1<<TWEN);
}

void I2C::error()
{
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void I2C::start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_START) & (status != GOOD_REPEATED_START))
        error();
}

void I2C::stop()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

bool I2C::gotACK()
{
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    return (status == GOOD_RX_ADDRESS_ACK) or (status == GOOD_RX_DATA_ACK);
}

void I2C::sendACK()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if(status != GOOD_TX_DATA_ACK)
        error();
}

void I2C::sendNACK()
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    uint8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if(status != GOOD_TX_DATA_NACK)
        error();
}

void I2C::transmitDATA(uint8_t DATA)
{
    TWDR = DATA;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    int8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_RX_DATA_ACK) & (status != GOOD_RX_DATA_NACK))
        error();
}

void I2C::transmitDATA(uint8_t ADDRESS, uint8_t DATA)
{
    transmitDATA(ADDRESS);
    if(not gotACK()) error();
    transmitDATA(DATA);
}

void I2C::transmitSLA_W(uint8_t SLA_W)
{
    TWDR = SLA_W;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    int8_t status = TWSR & ~((1<<TWPS0) | (1<<TWPS1));
    if((status != GOOD_RX_ADDRESS_ACK) & (status != GOOD_RX_ADDRESS_NACK) & (status != GOOD_TX_ADDRESS_ACK) & (status != GOOD_TX_ADDRESS_NACK))
        error();
    if((status != GOOD_RX_ADDRESS_ACK) & (status != GOOD_TX_ADDRESS_ACK))
        error();
}
