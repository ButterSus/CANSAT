/**
 * @author ButterSus
 * @date June 2022
 */

#include "TIMER0.h"
#include "UART.h"

UART::UART(int (*putc)(char, FILE *), volatile uint8_t*UCSRnA, volatile uint8_t*UCSRnB, volatile uint8_t*UCSRnC,
           volatile uint8_t*UBRRnH, volatile uint8_t*UBRRnL, FILE*FILE_buffer)
{
    safeModeBegin();
    FILE_buffer->buf = nullptr;
    FILE_buffer->unget = 0;
    FILE_buffer->flags = _FDEV_SETUP_WRITE;
    FILE_buffer->size = 0;
    FILE_buffer->len = 0;
    FILE_buffer->put = putc;
    FILE_buffer->get = nullptr;
    FILE_buffer->udata = nullptr;
    *UCSRnA = 0x0;
    *UCSRnB = 0b10011000;
    *UCSRnC = 0b110;
    *UBRRnH = 0x0;
    *UBRRnL = 0xC;
    this->out = FILE_buffer;
    safeModeEnd();
}

UART &UART::operator<<(char*value) {
    safeModeBegin();
        fprintf(this->out, "%s", value);
    safeModeEnd();
    return *this;
}

UART &UART::operator<<(const char*value)
{
    safeModeBegin();
        fprintf(this->out, "%s", value);
    safeModeEnd();
    return *this;
}

UART &UART::operator<<(float value)
{
    safeModeBegin();
        fprintf(this->out, "%f", value);
    safeModeEnd();
    return *this;
}

UART &UART::operator<<(double value)
{
    safeModeBegin();
        fprintf(this->out, "%lf", value);
    safeModeEnd();
    return *this;
}

UART &UART::operator<<(int value)
{
    safeModeBegin();
        fprintf(this->out, "%d", value);
    safeModeEnd();
    return *this;
}

template <typename type>
UART &UART::operator<<(type value)
{
    safeModeBegin();
        fprintf(this->out, "%d", value);
    safeModeEnd();
    return *this;
}
