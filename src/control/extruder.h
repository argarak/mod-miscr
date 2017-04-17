
#ifndef _H_EXTRUDER
#define _H_EXTRUDER

#include "../../mirpm.h"
#include <avr/interrupt.h>

#define EXTRUDER_PIN B,4
#define EXTRUDER_FAN_PIN H,6

#define NUMTEMPS 20
extern short temptable[NUMTEMPS][2];

extern struct temp_t_struct {
  uint16_t raw;
  uint16_t celcius;
} temp_t_struct;

typedef struct temp_t_struct temp_t;

namespace Extruder {
  void Init();

  extern temp_t temperature;
  extern uint16_t dtemp;

  extern uint8_t dcycle;

  uint16_t GetTemperature();
  void UpdateTemperature();
}

#endif
