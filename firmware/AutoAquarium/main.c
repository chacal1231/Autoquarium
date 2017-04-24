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

/*************************************************************************/ /**
Leer datos de la UART
*****************************************************************************/
void commandProcessing(char *buffer){
    uart_putstr("Iniciando el commandProcessing\r\n");
    //Detectar si no se conecta al WIFI
    int error_wifi = strcmp("FAIL", buffer);
    //Detectar si no hay internet
    int wifi_connect = strcmp("WIFI GOT IP", buffer);
    //Detectar si se desconectó del socket
    int error_server = strcmp("CLOSED",buffer);
    //Detectar si se conectó al socket
    int server_link = strcmp("Linked", buffer);
    if(error_wifi == 0){
        uart_putstr("ESTADO ERROR RED\r\n");
        uart_putstr("AT+RST\r\n");
        mSleep(2000);
        WIFI_INIT();
    }
    else if(wifi_connect == 0){
        uart_putstr("ESTADO CONECTADO RED\r\n");
        mSleep(1000);
        WIFIConnectServer();
    }
    else if(error_server == 0){
        uart_putstr("ESTADO ERROR SERVIDOR\r\n");
        WIFIConnectServer();
    }
    else if(server_link == 0){
        uart_putstr("ESTADO CONECTADO SERVIDOR\r\n");
        WIFIStartSend();
    }
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
        UartBufferPtr = 0;
        return;
    }

    //si se recibe un FINALCHARACTER se procesa el comando, de lo contrario
    //se almacena el caracter si es un caracter imprimible
    if (byte_u8 == FINALCHARACTER1 || byte_u8 == FINALCHARACTER2)
    {
        UartBuffer[UartBufferPtr++] = '\0'; // null character manually added
        commandProcessing(UartBuffer);
        UartBufferPtr = 0;
    }
    else if (byte_u8 >= ' ' && byte_u8 <= '~')
    {
        UartBuffer[UartBufferPtr++] = byte_u8;
    }
}

int main(void)
{
    // Init Commands      
    isr_init();
    //tic_init();
    irq_set_mask(0x00000002);
    irq_enable();
    
    uart_init();
    
    WIFI_INIT();
    //WIFIConnectServer();
    

    while(1){
        commandUart_TaskHandler();
    }
    

    return 0;
}
