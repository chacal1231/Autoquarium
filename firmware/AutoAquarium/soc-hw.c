#include "soc-hw.h"

uart_t              *uart0          = (uart_t *)            0x20000000;
timerH_t            *timer0         = (timerH_t *)          0x30000000;
gpio_t              *gpio0          = (gpio_t *)            0x40000000;
uart_t              *uart1          = (uart_t *)            0x50000000;
leds_t              *leds0          = (leds_t *)            0x60000000;
i2c_t               *i2c0           = (i2c_t *)             0x70000000;

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
    //uart_putstr("AT+CWJAP=\"LenovoAndroid\",\"54321osk\"\r\n");
    uart_putstr("AT+CWJAP=\"-David McMahon\",\"masteryi\"\r\n");
    mSleep(16000);
    uart_putstr("AT+CWJAP?\r\n");
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
    uart_putstr("AT+CIPSTART=\"TCP\",\"200.112.210.132\",7778\r\n");
    mSleep(6000);
    uart_putstr("AT+CIPSTATUS\r\n");
}
/*************************************************************************/ /**
Función establecer conexión con el servidor Sockets
*****************************************************************************/
void WIFIStartSend(void){
    uart_putstr("AT+CIPSEND\r\n");
    mSleep(2000);
    WIFISendPotencia(0x30);
    mSleep(1000);
    WIFISendpH(0x31);
    mSleep(1000);
    WIFISendTemp(0x32);
    mSleep(1000);
    WIFISendFiltro(0x33);
    mSleep(1000);
    WIFISendImagen(0x34);
    mSleep(1000);
    WIFISendComida(0x35);
    mSleep(600000);
    uart_putstr("+++");
    mSleep(1000);
    uart_putstr("\r\n");
    uart_putstr("AT+CIPSTATUS\r\n");    
}

/*************************************************************************/ /**
Función enviar potencia
*****************************************************************************/
void WIFISendPotencia(uint32_t Potencia){
    uart_putstr("Potencia=");
    uart_putchar(Potencia);
    uart_putstr("\r\n");
}
/*************************************************************************/ /**
Función enviar pH
*****************************************************************************/
void WIFISendpH(uint32_t pH){
    uart_putstr("pH=");
    uart_putchar(pH);
    uart_putstr("\r\n");
}
/*************************************************************************/ /**
Función enviar Temperatura
*****************************************************************************/
void WIFISendTemp(uint32_t Temp){
    uart_putstr("Temp=");
    uart_putchar(Temp);
    uart_putstr("\r\n");
}
/*************************************************************************/ /**
Función enviar estado del filtro
*****************************************************************************/
void WIFISendFiltro(uint32_t Filtro){
    uart_putstr("Filtro=");
    uart_putchar(Filtro);
    uart_putstr("\r\n");
}
/*************************************************************************/ /**
Función enviar imagen
*****************************************************************************/
void WIFISendImagen(uint32_t Imagen){
    uart_putstr("Imagen=");
    uart_putchar(Imagen);
    uart_putstr("\r\n");
}
/*************************************************************************/ /**
Función enviar Comida
*****************************************************************************/
void WIFISendComida(uint32_t Comida){
    uart_putstr("Comida=");
    uart_putchar(Comida);
    uart_putstr("\r\n");
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
/*************************************************************************/ /**
Función recibir comando de tomar imagen y enviarlo al módulo de cámara
*****************************************************************************/
void WIFIRecivAlimen(void){

}

/***************************************************************************
 *Iluminación
 */

void set_start(uint32_t start0, uint32_t data0)
{   
     leds0->init = 0;
     leds0->rw = 0;
     leds0->start_add = start0;
     leds0->data = data0;
}
void leds_refresh(void){
  leds0->rw=1;
  leds0->init = 1;
  leds0->init = 0;  
}
uint32_t leds_finish(void){
    return leds0->done;
}

/***************************************************************************
 * I2C Functions
 */
 
void i2c_write_data(uint8_t addr_wr, uint8_t data){
    while(i2c0->i2c_state == 1){
        uSleep(50);
    };
    i2c0->rw        = 0;
    uSleep(10);
    i2c0->addr      = addr_wr;
    uSleep(10);
    i2c0->data_wr   = data;
    uSleep(10);
    i2c0->ena       = 1;
    uSleep(10);
    while(i2c0->i2c_state == 0){
        uSleep(50);
    };
    i2c0->ena       = 0;
};

uint8_t i2c_read_data(uint8_t addr_rd){
    while(i2c0->i2c_state == 1){
        uSleep(50);
    };
    i2c0->rw        = 1;
    uSleep(10);
    i2c0->addr      = addr_rd;
    uSleep(10);
    i2c0->ena       = 1;
    uSleep(10);
    while(i2c0->i2c_state == 0){
        uSleep(50);
    };
    i2c0->ena       = 0;
    while(i2c0->i2c_state == 1){
        uSleep(50);
    };
    return i2c0->data_rd;
};