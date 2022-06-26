/**
 * @author ButterSus
 * @date June 2022
 */

#include "UART.h"

UART::UART(int (*putc)(char, FILE *), volatile uint8_t*UCSRnA, volatile uint8_t*UCSRnB, volatile uint8_t*UCSRnC,
           volatile uint8_t*UBRRnH, volatile uint8_t*UBRRnL)
{
    FILE*UART_stream = static_cast<FILE *>(malloc(sizeof(FILE)));
    UART_stream->buf = nullptr;
    UART_stream->unget = 0;
    UART_stream->flags = _FDEV_SETUP_WRITE;
    UART_stream->size = 0;
    UART_stream->len = 0;
    UART_stream->put = putc;
    UART_stream->get = nullptr;
    UART_stream->udata = nullptr;
    *UCSRnA = 0x0;
    *UCSRnB = 0b10011000;
    *UCSRnC = 0b110;
    *UBRRnH = 0x0;
    *UBRRnL = 0xC;
    this->out = UART_stream;
}

UART &UART::operator<<(char*value)
{
    fprintf(this->out, "%s", value);
    return *this;
}

UART &UART::operator<<(const char*value)
{
    fprintf(this->out, "%s", value);
    return *this;
}

UART &UART::operator<<(float value)
{
    fprintf(this->out, "%f", value);
    return *this;
}

UART &UART::operator<<(double value)
{
    fprintf(this->out, "%lf", value);
    return *this;
}

template <typename type>
UART &UART::operator<<(type value)
{
    fprintf(this->out, "%d", value);
    return *this;
}
