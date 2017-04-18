#include "soc-hw.h"

uart_t              *uart0          = (uart_t *)            0x20000000;
timerH_t            *timer0         = (timerH_t *)          0x30000000;
gpio_t              *gpio0          = (gpio_t *)            0x40000000;
uart_t              *uart1          = (uart_t *)            0x50000000;

isr_ptr_t isr_table[32];

/***************************************************************************
 * IRQ handling
 */
void isr_null(void)
{
}

void irq_handler(uint32_t pending)
{     
    uint32_t i;

    for(i=0; i<32; i++) {
        if (pending & 0x00000001){
            (*isr_table[i])();
        }
        pending >>= 1;
    }
}

void isr_init(void)
{
    int i;
    for(i=0; i<32; i++)
        isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
    isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
    isr_table[irq] = &isr_null;
}

/***************************************************************************
 * TIMER Functions
 */
uint32_t tic_msec;

void mSleep(uint32_t msec)
{
    uint32_t tcr;

    // Use timer0.1
    timer0->compare1 = (FCPU/1000)*msec;
    timer0->counter1 = 0;
    timer0->tcr1 = TIMER_EN;

    do {
        //halt();
         tcr = timer0->tcr1;
     } while ( ! (tcr & TIMER_TRIG) );
}

void uSleep(uint32_t usec)
{
    uint32_t tcr;

    // Use timer0.1
    timer0->compare1 = (FCPU/1000000)*usec;
    timer0->counter1 = 0;
    timer0->tcr1 = TIMER_EN;

    do {
        //halt();
         tcr = timer0->tcr1;
     } while ( ! (tcr & TIMER_TRIG) );
}

void tic_isr(void)
{
    tic_msec++;
    timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init(void)
{
    tic_msec = 0;

    // Setup timer0.0
    timer0->compare0 = (FCPU/10000);
    timer0->counter0 = 0;
    timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

    isr_register(1, &tic_isr);
}


/***************************************************************************
 * UART Functions
 */
void uart_init(void)
{
    //uart0->ier = 0x00;  // Interrupt Enable Register
    //uart0->lcr = 0x03;  // Line Control Register:    8N1
    //uart0->mcr = 0x00;  // Modem Control Register

    // Setup Divisor register (Fclk / Baud)
    //uart0->div = (FCPU/(57600*16));
}
//UART0
char uart_getchar(void)
{   
    while (! (uart0->ucr & UART_DR)) ;
    return uart0->rxtx;
}

void uart_putchar(char c)
{
    while (uart0->ucr & UART_BUSY) ;
    uart0->rxtx = c;
}

void uart_putstr(char *str)
{
    char *c = str;
    while(*c) {
        uart_putchar(*c);
        c++;
    }
}
//UART1
char uart1_getchar(void)
{   
    while (! (uart1->ucr & UART_DR)) ;
    return uart1->rxtx;
}

void uart1_putchar(char c)
{
    while (uart1->ucr & UART_BUSY) ;
    uart1->rxtx = c;
}

void uart1_putstr(char *str)
{
    char *c = str;
    while(*c) {
        uart1_putchar(*c);
        c++;
    }
}

/***************************************************************************
 * Comunicaciones Functions
 */


/*************************************************************************/ /**
Función iniciar ESP8266
*****************************************************************************/
void WIFI_INIT(void){
    mSleep(2000);
    uart_putstr("AT\r\n");
    mSleep(2000);
    uart_putstr("AT+CWMODE=1\r\n");
    mSleep(2000);
    uart_putstr("AT+CWJAP=\"LenovoAndroid\",\"54321osk\"\r\n");
    mSleep(6000);
}
/*************************************************************************/ /**
Función Conectar al servidor
*****************************************************************************/
void WIFIConnectServer(void){
    uart_putstr("AT\r\n");
    mSleep(2000);
    uart_putstr("AT+CIPMUX=0\r\n");
    mSleep(2000);
    uart_putstr("AT+CIPMODE=1\r\n");
    mSleep(2000);
    uart_putstr("AT+CIPSTART=\"TCP\",\"200.112.210.132\",7777\r\n");
    mSleep(3000);
}
/*************************************************************************/ /**
Función establecer conexión con el servidor Sockets
*****************************************************************************/
void WIFIStartSend(void){
    uart_putstr("AT+CIPSEND\r\n");
    mSleep(2000);
}
/*************************************************************************/ /**
Función enviar potencia
*****************************************************************************/
void WIFISendPotencia(uint32_t Potencia){

}
/*************************************************************************/ /**
Función enviar pH
*****************************************************************************/
void WIFISendpH(uint32_t pH){

}
/*************************************************************************/ /**
Función enviar Temperatura
*****************************************************************************/
void WIFISendTemp(uint32_t Temp){

}
/*************************************************************************/ /**
Función enviar estado del filtro
*****************************************************************************/
void WIFISendFiltro(uint32_t Filtro){

}
/*************************************************************************/ /**
Función enviar imagen
*****************************************************************************/
void WIFISendImagen(uint32_t Imagen){

}
/*************************************************************************/ /**
Función recibir comando del filtro y enviarlo al módulo del filtro
*****************************************************************************/
void WIFIRecivFiltro(void){

}
/*************************************************************************/ /**
Función recibir comando de tomar imagen y enviarlo al módulo de cámara
*****************************************************************************/
void WIFIRecivTakeImagen(void){

}