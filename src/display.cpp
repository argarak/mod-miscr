
#include "display.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

u8g_t u8g;

void Display::Init() {
  u8g_InitSPI(&u8g,&u8g_dev_st7920_128x64_sw_spi, PN(0, 1), PN(7, 0), PN(7, 1), U8G_PIN_NONE, U8G_PIN_NONE);
  CLKPR = 0x80;
  CLKPR = 0x00;

  /* Timer clock = I/O clock / 1024 */
  TCCR0B = (1<<CS02)|(1<<CS00);
  /* Clear overflow flag */
  TIFR0  = 1<<TOV0;
  /* Enable Overflow Interrupt */
  TIMSK0 = 1<<TOIE0;
}

ISR(TIMER0_OVF_vect) {
  u8g_FirstPage(&u8g);

  do {
    u8g_SetFont(&u8g, u8g_font_6x10);
    u8g_DrawStr(&u8g, 0, 15, "Hello miscr!");
  } while(u8g_NextPage(&u8g));
  u8g_Delay(100);
}
