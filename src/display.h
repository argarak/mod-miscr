
#include "../miscr.h"
#include "../mirpm.h"
#include "../lib/u8glib-avr/u8g.h"

#define BUZZER_PIN          C,0
#define DISPLAY_RS_PIN      H,1
#define DISPLAY_ENABLE_PIN  H,0
#define DISPLAY_D0_PIN      A,1
#define DISPLAY_D1_PIN      A,3
#define DISPLAY_D2_PIN      A,5
#define DISPLAY_D3_PIN      A,7

extern u8g_t u8g;

namespace Display {
  //void Buzzer(uint8_t freq);
  void Init();
}
