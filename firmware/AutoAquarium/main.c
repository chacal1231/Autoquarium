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
void commandProcessing(const char *buffer){
    //Detectar si no se conecta al WIFI
    char *error_wifi_s = strstr(buffer, "FAIL");
    //Detectar si no se conecta al WIFIx2
    char *error_wifi_s_1 = strstr(buffer, "No AP");
    //Se desconectó del WIFI
    char *error_wifi_s_2 = strstr(buffer, "STATUS:5");
    //Detectar si no se conecta al WIFIx3
    char *error_wifi_s_3 = strstr(buffer, "WIFI GOT IP");
    //Detectar si se conectó al WIFI
    char *wifi_connect_s = strstr(buffer,"+CWJAP:");
    //Detectar si se desconectó del socket
    char *error_server_s = strstr(buffer, "CLOSED");
    //Detectar si se conectó al socket
    char *server_link_s = strstr(buffer, "STATUS:3");
    //Detectar si se conectó al socket
    char *server_link_s_1 = strstr(buffer, "STATUS:2");
    //Detectar si se conectó al socket
    char *server_link_s_2 = strstr(buffer, "STATUS:4");
    //Petición para enviar los datos
    char *server_send = strstr(buffer, "Send");
    //Activar filtro
    char *Filtro_UP = strstr(buffer, "Command1");
    //Desactivar filtro
    char *Filtro_Down = strstr(buffer, "Command2");
    //Tomar foto
    char *TakePhoto = strstr(buffer, "Command3");
    //Alimentar peces
    char *AlimentarPe = strstr(buffer, "Command4");
    //Condicionales para verificación
    if(error_wifi_s != NULL || error_wifi_s_1 != NULL || error_wifi_s_2 != NULL || error_wifi_s_3 != NULL){
        WIFI_INIT();
    }
    if(wifi_connect_s != NULL){
        mSleep(1000);
        WIFIConnectServer();
    }
    if(error_server_s != NULL){
        WIFIConnectServer();
    }
    if(server_link_s != NULL){
        WIFIStartSend();
    }
    if (server_link_s_1 != NULL || server_link_s_2 != NULL){
        WIFIConnectServer();        
    }
    if(Filtro_UP != NULL){
        SK6812RGBW_nBits(35 * 32);
        mSleep(1000);
        SK6812RGBW_rgbw(0x00ff0000);

    }
    if(Filtro_Down != NULL){
        SK6812RGBW_nBits(35 * 32);
        mSleep(1000);
        SK6812RGBW_rgbw(0xff000000);
        
    }
    if(TakePhoto != NULL){
        SK6812RGBW_nBits(35 * 32);
        mSleep(1000);
        SK6812RGBW_rgbw(0x0000ff00);
        
    }
    if(AlimentarPe != NULL){
        SK6812RGBW_nBits(35 * 32);
        mSleep(1000);
        SK6812RGBW_rgbw(0x000000ff);        
    }
    if(server_send != NULL){
        WIFIStartSend();
    }
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
        UartBufferPtr = 0;
        return;
    }

    //si se recibe un FINALCHARACTER se procesa el comando, de lo contrario
    //se almacena el caracter si es un caracter imprimible
    if (byte_u8 == FINALCHARACTER1 || byte_u8 == FINALCHARACTER2)
    {
        UartBuffer[UartBufferPtr++] = '\0'; // null character manually added
        UartBufferPtr = 0;
        commandProcessing(UartBuffer);
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
    SK6812RGBW_init();
    
    

    while(1){
        commandUart_TaskHandler();
    }
    

    return 0;
}
