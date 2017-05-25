#include "soc-hw.h"

uart_t              *uart0          = (uart_t *)            0x20000000;
timerH_t            *timer0         = (timerH_t *)          0x30000000;
gpio_t              *gpio0          = (gpio_t *)            0x40000000;
uart_t              *uart1          = (uart_t *)            0x50000000;
leds_t              *leds0          = (leds_t *)            0x60000000;
i2c_t               *i2c0           = (i2c_t *)             0x70000000;
SK6812RGBW_t        *SK6812RGBW0    = (SK6812RGBW_t *)      0x80000000;
fuente_t            *fuente0        = (fuente_t*)           0x90000000;

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

char uart_getchar(void)
{   
    while (! (uart0->ucr & Uart_RXData_Ready));
    return uart0->rx_data;
}

void uart_putchar(char c)
{
    while (uart0->ucr & Uart_TX_Busy);
        uart0->tx_data = c;
        uart0->tx_run = 1;
        uart0->tx_run = 0; 
    
}

void uart_putstr(char *str)
{
    char *c = str;
    while(*c) {
        uart_putchar(*c);
        while(txbusy()){
        uSleep(1);
        }
        c++;
    }
}

uint32_t txbusy(void){
    return uart0->tx_busy;
}
uint32_t rxavail(void){
    return uart0->rx_avail;
}

/***************************************************************************
 * C Functions
 */
/**
 * strstr - Find the first substring in a %NUL terminated string
 * @s1: The string to search for
 * @s2: The string to be searched
 */
 /**

 * memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
int memcmp(const void *cs, const void *ct, size_t count)
{
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;
    return res;
}
char *strstr(const char *s1, const char *s2)
{
    size_t l1, l2;

    l2 = strlen(s2);
    if (!l2)
        return (char *)s1;
    l1 = strlen(s1);
    while (l1 >= l2) {
        l1--;
        if (!memcmp(s1, s2, l2))
            return (char *)s1;
        s1++;
    }
    return NULL;
}

/**
 * strlen - Find the length of a string
 * @s: The string to be sized
 */
size_t strlen(const char *s)
{
    const char *sc;

    for (sc = s; *sc != '\0'; ++sc)
        /* nothing */;
    return sc - s;
}
/**
 * itoa
 */
char *itoa(int i, char b[]){
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
    //uart_putstr("AT+CWJAP=\"Moto G\",\"09aa276522ec\"\r\n");
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
    mSleep(1000);
    WIFISendPotencia(0x30);
    mSleep(100);
    WIFISendpH(0x31);
    mSleep(100);
    WIFISendTemp(0x32);
    mSleep(100);
    WIFISendFiltro(0x33);
    mSleep(100);
    WIFISendImagen(0x34);
    mSleep(100);
    WIFISendComida(0x35);
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
 
uint8_t i2c_read(uint8_t slave_addr, uint8_t per_addr)
{
        
    while(!(i2c0->scr & I2C_DR));       //Se verifica que el bus esté en espera
    i2c0->s_address = slave_addr;
    i2c0->s_reg     = per_addr;
    i2c0->start_rd  = 0x00;
    while(!(i2c0->scr & I2C_DR));
    return i2c0->i2c_rx_data;
    mSleep(2);
}

void i2c_write(uint8_t slave_addr, uint8_t per_addr, uint8_t data){
    
    while(!(i2c0->scr & I2C_DR));       //Se verifica que el bus esté en espera
    i2c0->s_address = slave_addr;
    i2c0->s_reg     = per_addr;
    i2c0->tx_data   = data;
    i2c0->start_wr  = 0x00;
    mSleep(1);
}

/***************************************************************************
 * Display Functions
 */

void send_command_display(uint8_t addr, uint8_t command){
    i2c_write(addr, DISPLAY_COMMAND, command);
};

void send_data_display(uint8_t addr, uint8_t data){
    i2c_write(addr, DISPLAY_INDEX, data);
};

void sec_on_display(void){
    uint32_t addr = 642;
        uint8_t data;
        uint8_t k; 
        for(k=0;k<28;k++){
            data = fuente_read_data(addr+k);
            send_command_display(DISPLAY_ADDR,data);
        };
};  



void clear_GDRAM(void){
        uint8_t i, j;
        set_position(0x00, 0x00);
    for(j=1;j<9;j++){
            for (i=1;i<129;i++) {
                    send_data_display(DISPLAY_ADDR, 0x00);
            }
        }
    
};

void set_position(uint8_t posx, uint8_t posy){
    send_command_display(DISPLAY_ADDR,0x21); //Configurar el direccionamiento por columna
    send_command_display(DISPLAY_ADDR,posx);
    send_command_display(DISPLAY_ADDR,0x7F);
    send_command_display(DISPLAY_ADDR,0x22); //Configurar el direccionamiento por página
    send_command_display(DISPLAY_ADDR,posy);
    send_command_display(DISPLAY_ADDR,0x07);
};

void print_char(uint8_t code){
        uint32_t addr = (code*6);
        uint8_t data;
        uint8_t k; 
        for(k=0;k<6;k++){
            data = fuente_read_data(addr+k);
            send_data_display(DISPLAY_ADDR,data);
        };
};

void print_cadena_ascii(char* cadena){               
    uint8_t i;
   
    for(i = 0; cadena[i] !='\0'; i++){      
            print_char(cadena[i]-32); 
    };
};

void print_entero_ascii(int numero){
    uint8_t c = numero;
    uint8_t contador = 1; 
    
     while(c/10>0)
    {
        c=c/10;
        contador++;
    };
    
    char buffer[contador];
    
    itoa(numero,buffer);
    
    print_cadena_ascii(buffer);
};

void print_wifi_hour(uint8_t hora, uint8_t minutos){
        set_position(80, 0);
        print_entero_ascii(hora);
        print_char(26);
        print_entero_ascii(minutos);
        print_char(00);
        print_char(94);
        print_char(95);
};

void init_display(void){
        uint8_t i;
        set_position(23,3);
        print_cadena_ascii("AUTOAQUARIUM");
        //peces
        set_position(19,5);
        for(i=0;i<3;i++){
                print_char(00);
                print_char(96);
                print_char(97);
                print_char(00);
                print_char(00);
        };
};

void principal_display(uint8_t hora, uint8_t minutos, uint8_t temperatura, uint8_t ph){
        print_wifi_hour(hora,minutos);
        set_position(4,1);
        print_char(98);
        print_char(99);
        set_position(4,2);
        print_char(100);
        print_char(101);
        print_cadena_ascii("Temperatura: ");
        print_entero_ascii(temperatura);
        print_char(102);
        print_char(35);
        set_position(4,3);
        print_char(103);
        print_char(104);
        set_position(4,4);
        print_char(105);
        print_char(106);
        print_cadena_ascii("Nivel de PH: ");
        print_entero_ascii(ph);        
};

/***************************************************************************
 * Fuente Functions
 */

uint8_t fuente_read_data(uint32_t addr){
    fuente0->addr_rd    = addr;
    fuente0->rd     = 1;
    fuente0->rd     = 0;
    return fuente0->d_out;
};

/***************************************************************************
 * SK6812RGBW Functions
 */
void SK6812RGBW_init(void)
{
    SK6812RGBW_nBits(35*32);//35 Leds
    SK6812RGBW_source(0);
    SK6812RGBW_rgbw(0x00000000);
    SK6812RGBW_rgbw(0x00000000);
}

uint32_t SK6812RGBW_busy(void)
{
    return SK6812RGBW0->busy;
}

void SK6812RGBW_rgbw(uint32_t rgbw)
{
    while (SK6812RGBW_busy());
    SK6812RGBW0->rgbw = rgbw;
}

void SK6812RGBW_nBits(uint32_t nBits)
{
    while (SK6812RGBW_busy());
    SK6812RGBW0->nBits = nBits;
}

void SK6812RGBW_source(uint32_t source)
{
    while (SK6812RGBW_busy());
    SK6812RGBW0->source = source;
}

void SK6812RGBW_ram(uint32_t color, uint32_t add)
{
  uint32_t   *wram   = (uint32_t *)    (0x60000000 + 0x1000 + add);
  *wram = color;
}

void SK6812RGBW_ram_w(void)
{
    while (SK6812RGBW_busy());
    SK6812RGBW0->rgbw = 0;
}

