
/*- Includes ---------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soc-hw.h"

/*- Definitions ------------------------------------------------------------*/
#ifndef UART_COMMANDS_BUFFER_SIZE
#define UART_COMMANDS_BUFFER_SIZE 100
#endif

#define FINALCHARACTER1 '\r'
#define FINALCHARACTER2 '\n'

/*- Variables --------------------------------------------------------------*/
char UartBuffer[UART_COMMANDS_BUFFER_SIZE];
uint32_t UartBufferPtr = 0;

char *itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char *p = b;
    if (i < 0)
    {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do
    { //Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do
    { //Move back, inserting digits as u go
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);
    return b;
}

/*************************************************************************/ /**
Función que implementa una calculadora sencilla
*****************************************************************************/
void commandProcessing(const char *buffer)
{

    int rgbw = atoi(buffer);
    SK6812RGBW_rgbw(rgbw);

    return;
}

/*************************************************************************/ /**
*****************************************************************************/
void commandUart_TaskHandler(void)
{

    //lee un byte del buffer de la UART
    char byte_u8 = uart_getchar();

    //verifica que no se ha exedido el buffer de comandos UART_COMMANDS_BUFFER_SIZE
    //Si se exede se envia una alerta y se borran los datos del buffer
    if (UartBufferPtr >= UART_COMMANDS_BUFFER_SIZE)
    {
        uart_putstr("\r\nUartBuffer size exceeded:serial commands\r\n-->");
        UartBufferPtr = 0;
        return;
    }

    //si se recibe un FINALCHARACTER se procesa el comando, de lo contrario
    //se almacena el caracter si es un caracter imprimible
    if (byte_u8 == FINALCHARACTER1 || byte_u8 == FINALCHARACTER2)
    {
        UartBuffer[UartBufferPtr++] = '\0'; // null character manually added
        uart_putstr("\r\n");
        commandProcessing(UartBuffer);
        uart_putstr("-->");
        UartBufferPtr = 0;
    }
    else if (byte_u8 >= ' ' && byte_u8 <= '~')
    {
        UartBuffer[UartBufferPtr++] = byte_u8;
        //Se hace un echo de caracteres almacenados
        uart_putchar(byte_u8);
    }
}
/*************************************************************************/ /**
Función inicialización WIFI
*****************************************************************************/
void Esp8266StartListen(void){
    mSleep(5000);
    uart_putstr("AT\r\n");
    mSleep(1000);
    uart_putstr("AT+CIPMUX=0\r\n");
    mSleep(1000);
    uart_putstr("AT+CIPMODE=1\r\n");
    mSleep(1000);
    uart_putstr("AT+CIPSTART=\"TCP\",\"200.112.210.132\",7777\r\n");
    mSleep(1000);
    uart_putstr("AT+CIPSEND\r\n");
    mSleep(1000);
}
/*************************************************************************/ /**
*****************************************************************************/
int main(void)
{

    // Init Commands
    isr_init();
    //tic_init();
    irq_set_mask(0x00000002);
    irq_enable();

    uart_init();

    SK6812RGBW_init();
    Esp8266StartListen();

    while (1)
    {
        commandUart_TaskHandler();
    }

    return 0;
}
