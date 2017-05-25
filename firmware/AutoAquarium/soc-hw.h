#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      50000000

#define UART_RXBUFSIZE 32

#define DISPLAY_ADDR  0X3C
#define DISPLAY_COMMAND 0X00
#define DISPLAY_INDEX 0X40
#define NULL ((void *)0)

/****************************************************************************
 * Constantes sensor de color
 */
#define DEBUG                   0

/* APDS-9960 I2C address */
#define APDS9960_I2C_ADDR       0x39

/* Gesture parameters */
#define GESTURE_THRESHOLD_OUT   10
#define GESTURE_SENSITIVITY_1   50
#define GESTURE_SENSITIVITY_2   20

/* si error de codigo */
#define ERROR                   0xFF

/* Direcciones aceptables IDs */
#define APDS9960_ID_1           0xAB
#define APDS9960_ID_2           0x9C 

/* Misc parameters */
#define FIFO_PAUSE_TIME         30      // Wait period (ms) between FIFO reads

/* APDS-9960 register addresses */
#define APDS9960_ENABLE         0x80
#define APDS9960_ATIME          0x81
#define APDS9960_WTIME          0x83
#define APDS9960_AILTL          0x84
#define APDS9960_AILTH          0x85
#define APDS9960_AIHTL          0x86
#define APDS9960_AIHTH          0x87
#define APDS9960_PILT           0x89
#define APDS9960_PIHT           0x8B
#define APDS9960_PERS           0x8C
#define APDS9960_CONFIG1        0x8D
#define APDS9960_PPULSE         0x8E
#define APDS9960_CONTROL        0x8F
#define APDS9960_CONFIG2        0x90
#define APDS9960_ID             0x92
#define APDS9960_STATUS         0x93
#define APDS9960_CDATAL         0x94
#define APDS9960_CDATAH         0x95
#define APDS9960_RDATAL         0x96
#define APDS9960_RDATAH         0x97
#define APDS9960_GDATAL         0x98
#define APDS9960_GDATAH         0x99
#define APDS9960_BDATAL         0x9A
#define APDS9960_BDATAH         0x9B
#define APDS9960_PDATA          0x9C
#define APDS9960_POFFSET_UR     0x9D
#define APDS9960_POFFSET_DL     0x9E
#define APDS9960_CONFIG3        0x9F
#define APDS9960_GPENTH         0xA0
#define APDS9960_GEXTH          0xA1
#define APDS9960_GCONF1         0xA2
#define APDS9960_GCONF2         0xA3
#define APDS9960_GOFFSET_U      0xA4
#define APDS9960_GOFFSET_D      0xA5
#define APDS9960_GOFFSET_L      0xA7
#define APDS9960_GOFFSET_R      0xA9
#define APDS9960_GPULSE         0xA6
#define APDS9960_GCONF3         0xAA
#define APDS9960_GCONF4         0xAB
#define APDS9960_GFLVL          0xAE
#define APDS9960_GSTATUS        0xAF
#define APDS9960_IFORCE         0xE4
#define APDS9960_PICLEAR        0xE5
#define APDS9960_CICLEAR        0xE6
#define APDS9960_AICLEAR        0xE7
#define APDS9960_GFIFO_U        0xFC
#define APDS9960_GFIFO_D        0xFD
#define APDS9960_GFIFO_L        0xFE
#define APDS9960_GFIFO_R        0xFF

/* Bit fields */
#define APDS9960_PON            0b00000001
#define APDS9960_AEN            0b00000010
#define APDS9960_PEN            0b00000100
#define APDS9960_WEN            0b00001000
#define APSD9960_AIEN           0b00010000
#define APDS9960_PIEN           0b00100000
#define APDS9960_GEN            0b01000000
#define APDS9960_GVALID         0b00000001

/* On/Off definitions */
#define OFF                     0
#define ON                      1

/* Acceptable parameters for setMode */
#define POWER                   0
#define AMBIENT_LIGHT           1
#define PROXIMITY               2
#define WAIT                    3
#define AMBIENT_LIGHT_INT       4
#define PROXIMITY_INT           5
#define GESTURE                 6
#define ALL                     7

/* LED Drive values */
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3

/* Proximity Gain (PGAIN) values */
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

/* ALS Gain (AGAIN) values */
#define AGAIN_1X                0
#define AGAIN_4X                1
#define AGAIN_16X               2
#define AGAIN_64X               3

/* Gesture Gain (GGAIN) values */
#define GGAIN_1X                0
#define GGAIN_2X                1
#define GGAIN_4X                2
#define GGAIN_8X                3

/* LED Boost values */
#define LED_BOOST_100           0
#define LED_BOOST_150           1
#define LED_BOOST_200           2
#define LED_BOOST_300           3    

/* Gesture wait time values */
#define GWTIME_0MS              0
#define GWTIME_2_8MS            1
#define GWTIME_5_6MS            2
#define GWTIME_8_4MS            3
#define GWTIME_14_0MS           4
#define GWTIME_22_4MS           5
#define GWTIME_30_8MS           6
#define GWTIME_39_2MS           7

/* Default values */
#define DEFAULT_ATIME           219     // 103ms
#define DEFAULT_WTIME           246     // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UR      0       // 0 offset
#define DEFAULT_POFFSET_DL      0       // 0 offset      
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_LDRIVE          LED_DRIVE_100MA
#define DEFAULT_PGAIN           PGAIN_4X
#define DEFAULT_AGAIN           AGAIN_4X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x11    // 2 consecutive prox or ALS for int.
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost  
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          40      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           30      // Threshold for exiting gesture mode    
#define DEFAULT_GCONF1          0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GGAIN           GGAIN_4X
#define DEFAULT_GLDRIVE         LED_DRIVE_100MA
#define DEFAULT_GWTIME          GWTIME_2_8MS
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          0       // All photodiodes active during gesture
#define DEFAULT_GIEN 0 


/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit
typedef int size_t; //IDK 



/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable(void);
void     irq_disable(void);
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak(void);

void     isr_init(void);
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);
void     isr_null(void);

/****************************************************************************
 * General Stuff
 */
void     halt(void);
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
    volatile uint32_t tcr0;
    volatile uint32_t compare0;
    volatile uint32_t counter0;
    volatile uint32_t tcr1;
    volatile uint32_t compare1;
    volatile uint32_t counter1;
} timerH_t;

void mSleep(uint32_t msec);
void uSleep(uint32_t usec);
void tic_init(void);
void tic_isr(void);
/***************************************************************************
 * Comunicaciones
 */
void WIFI_INIT(void);
void WIFIConnectServer(void);
void WIFIStartSend(void);
void WIFISendVar(void);
void WIFISendPotencia(uint32_t Potencia);
void WIFISendpH(uint32_t pH);
void WIFISendTemp(uint32_t Temp);
void WIFISendFiltro(uint32_t Filtro);
void WIFISendImagen(uint32_t imagen);
void WIFISendComida(uint32_t Comida);
void WIFIRecivFiltro(void);
void WIFIRecivTakeImagen(void);
/***************************************************************************
 * Iluminación
 */

typedef struct {
   volatile uint32_t init;        //0x00
   volatile uint32_t done;        //0x04
   volatile uint32_t start_add;   //0x08
   volatile uint32_t data;        //0x0C
   volatile uint32_t rw;      //0x10
} leds_t;

void set_start(uint32_t start0, uint32_t data0);
void leds_refresh(void);
uint32_t leds_finish(void);

/***************************************************************************
 * I2C0
 */

#define I2C_DR   0x03     //RX Data Ready
#define I2C_BUSY 0x04     //I2C Busy
#define I2C_ERR  0x02     //RX Error

typedef struct {
   volatile uint32_t scr;
   volatile uint32_t i2c_rx_data;
   volatile uint32_t s_address;
   volatile uint32_t s_reg;
   volatile uint32_t tx_data;
   volatile uint32_t start_wr;
   volatile uint32_t start_rd;
} i2c_t;

uint8_t i2c_read(uint32_t slave_addr, uint32_t per_addr);
void i2c_write(uint32_t slave_addr, uint32_t per_addr, uint32_t data);

/***************************************************************************
 * GPIO0
 */
typedef struct {
    volatile uint32_t ctrl;
    volatile uint32_t dummy1;
    volatile uint32_t dummy2;
    volatile uint32_t dummy3;
    volatile uint32_t in;
    volatile uint32_t out;
    volatile uint32_t oe;
} gpio_t;

/***************************************************************************
 * UART0
 */
#define Uart_RXData_Ready   0x01                    // RX Data Ready
#define Uart_RXData_Error   0x02                    // RX Error
#define Uart_TX_Busy        0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rx_data;
   volatile uint32_t rx_avail;
   volatile uint32_t tx_busy;
   volatile uint32_t tx_data;
   volatile uint32_t tx_run;
} uart_t;

void uart_init(void);
void uart_putchar(char c);
void uart_putstr(char *str);
void uart_putdata(uint8_t data);
char uart_getchar(void);
uint32_t txbusy(void);
uint32_t rxavail(void);

/***************************************************************************
 * SPI0
 */

typedef struct {
   volatile uint32_t rxtx;
   volatile uint32_t nop1;
   volatile uint32_t cs;
   volatile uint32_t nop2;
   volatile uint32_t divisor;
} spi_t;

void spi_init(void);
void spi_putchar(char c);
char spi_getchar(void);

/***************************************************************************
 * Funciones display
 */
 
void send_command_display(uint8_t addr, uint8_t command);
void send_data_display(uint8_t addr, uint8_t data);
void sec_on_display(void);
void clear_GDRAM(void);
void set_position(uint8_t posx, uint8_t posy);
void print_char(uint8_t code);
void print_cadena_ascii(char* cadena);
void print_entero_ascii(int numero);
void print_wifi_hour(uint8_t hora, uint8_t minutos);
void init_display(void);
void principal_display(uint8_t hora, uint8_t minutos, uint8_t temperatura, uint8_t ph);
void password(uint8_t);
void menu_display(void);

/***************************************************************************
 * Fuente0
 */
 
 typedef struct {
        volatile uint32_t rd;
        volatile uint32_t addr_rd;
        volatile uint32_t d_out;
 } fuente_t;
 
uint8_t fuente_read_data(uint32_t addr_rd);


/***************************************************************************
 * Funciones pH
 ***************************************************************************/
 
void initPH (void);
void habilitar_PH_sensor (void);
uint32_t leer_rojo (void);
uint32_t leer_verde (void);
uint32_t leer_azul (void);
void ver_entero_consola(uint32_t numero);

/***************************************************************************
 * PH Functions
 */
 
 void initPH (void) {

/*1*/int8_t id;
     
     id = i2c_read(0x39, 0x92);
    
    if(!(id == APDS9960_ID_1 || id == APDS9960_ID_2)) {
        //return false; 
    }

    
/*2*/   i2c_write(0x39,APDS9960_ENABLE, 0);

/*3*/    i2c_write(0x39,DEFAULT_ATIME, DEFAULT_ATIME);
         i2c_write(0x39,DEFAULT_WTIME, DEFAULT_WTIME);
         i2c_write(0x39,APDS9960_PPULSE, DEFAULT_PROX_PPULSE);
         i2c_write(0x39,APDS9960_POFFSET_UR, DEFAULT_POFFSET_UR);
         i2c_write(0x39,APDS9960_POFFSET_DL, DEFAULT_POFFSET_DL );
         i2c_write(0x39,APDS9960_CONFIG1, DEFAULT_CONFIG1);
         
         //escritura en solo dos posiciones:5,6

          //*ADPS_CONTROL=00xx1001
          int8_t ctrl; int8_t val;
          ctrl=i2c_read(0x39,APDS9960_CONTROL);
          ctrl&=0x30;//00110000;//00xx0000 salvo lo que tenia en xx
          val =0x9;//  00001001;
          ctrl|=val;
          i2c_write(0x39,APDS9960_CONTROL,ctrl);          

/*4*/     
          i2c_write(0x39, APDS9960_PILT,   DEFAULT_PILT );
          i2c_write(0x39, APDS9960_PIHT,   DEFAULT_PIHT);
          i2c_write(0x39, APDS9960_AILTL,  0xFF );
          i2c_write(0x39, APDS9960_AILTH , 0xFF);
          i2c_write(0x39, APDS9960_AIHTL,  0);
          i2c_write(0x39, APDS9960_AIHTH,  0);
          i2c_write(0x39, APDS9960_PERS,   DEFAULT_PERS );
          i2c_write(0x39, APDS9960_CONFIG2,DEFAULT_CONFIG2);
          i2c_write(0x39, APDS9960_CONFIG3,DEFAULT_CONFIG3);
          i2c_write(0x39, APDS9960_GPENTH, DEFAULT_GPENTH );
          i2c_write(0x39, APDS9960_GEXTH,  DEFAULT_GEXTH );
          i2c_write(0x39, APDS9960_GCONF1, DEFAULT_GCONF1);

/*5*/     //escritura en todo menos en bit:8
          
          //*APDS9960_GCONF2=X1000001 
          int8_t gconf2; int8_t val1;
          gconf2=i2c_read(0x39,APDS9960_GCONF2);
          gconf2&=0x80; //10000000;//x000000 salvo lo que tenia en x
          val1 = 0x41;  //01000001;
          gconf2|=val1;
          i2c_write(0x39,APDS9960_GCONF2,gconf2);
          
          i2c_write(0x39,APDS9960_GOFFSET_U , DEFAULT_GOFFSET); 
          i2c_write(0x39,APDS9960_GOFFSET_D , DEFAULT_GOFFSET); 
          i2c_write(0x39,APDS9960_GOFFSET_L , DEFAULT_GOFFSET); 
          i2c_write(0x39,APDS9960_GOFFSET_R , DEFAULT_GOFFSET); 
          i2c_write(0x39,APDS9960_GPULSE    , DEFAULT_GPULSE); 
          i2c_write(0x39,APDS9960_GCONF3    , DEFAULT_GCONF3); 

           //escritura  en bit:2
          
          //*APDS9960_GCONF4=xxxxxx0x
          int8_t gconf4; int8_t val2;
          gconf4=i2c_read(0x39,APDS9960_GCONF4);
          gconf4&=0xFD;//11111101;//x000000 salvo lo que tenia en x
          val2 =  0;
          gconf4|=val2;
          i2c_write(0x39,APDS9960_GCONF4,gconf4);
    
};

void habilitar_PH_sensor (void){
  
  uint8_t control = i2c_read(0x39, APDS9960_CONTROL);
  control &=  0xFC;
  uint8_t val_control = 0x01;
  control |= val_control;
  i2c_write(0x39, APDS9960_CONTROL, control);

  uint8_t enable = i2c_read(0x39, APDS9960_ENABLE);
  enable &=  0xEC;
  uint8_t val_enable = 0x03;
  enable |= val_enable;
  i2c_write(0x39, APDS9960_ENABLE, enable);
  
  mSleep(100);
};

uint32_t leer_rojo (void){

  uint32_t RL = i2c_read(0x39, APDS9960_RDATAL);
  uint32_t RH = i2c_read(0x39, APDS9960_RDATAH);
  uint32_t R = (RL) + (RH * 0xFF);

  return R;
};

uint32_t leer_verde (void){

  uint32_t GL = i2c_read(0x39, APDS9960_GDATAL);
  uint32_t GH = i2c_read(0x39, APDS9960_GDATAH);
  uint32_t G = (GL) + (GH * 0xFF);

  return G;
};

uint32_t leer_azul (void){

  uint32_t BL = i2c_read(0x39, APDS9960_BDATAL);
  uint32_t BH = i2c_read(0x39, APDS9960_BDATAH);
  uint32_t B = (BL) + (BH * 0xFF);

  return B;
};

void ver_entero_consola(uint32_t numero){
    uint8_t c = numero;
    uint8_t contador = 1; 
     while(c/10>0){
        c=c/10;
        contador++;
    };
    char buffer[contador];
    itoa(numero,buffer);
    uart_putstr(buffer);
};

/***************************************************************************


 * SK6812RGBW0
 */

typedef struct {
   volatile uint32_t nBits;
   volatile uint32_t rgbw;
   volatile uint32_t source;
   volatile uint32_t busy;
} SK6812RGBW_t;

void SK6812RGBW_init(void);
uint32_t SK6812RGBW_busy(void);
void SK6812RGBW_rgbw(uint32_t rgbw);
void SK6812RGBW_nBits(uint32_t nBits);
void SK6812RGBW_source(uint32_t source);
void SK6812RGBW_ram(uint32_t color, uint32_t add);
void SK6812RGBW_ram_w(void);

/***************************************************************************
 * Funciones
 */

size_t strlen(const char *s);
void *memcpy(void *to, const void *from, size_t n);
char *strstr(const char *s1, const char *s2);

/***************************************************************************
 * Pointer to actual components
 */
extern    timerH_t       *timer0;
extern    uart_t         *uart0; 
extern    gpio_t         *gpio0;
extern    uart_t         *uart1;
extern    leds_t         *leds0;
extern    uint32_t       *sram0;
extern    SK6812RGBW_t   *SK6812RGBW0;
extern    fuente_t       *fuente0; 

#endif // SPIKEHW_H
