
#include "extruder.h"

temp_t Extruder::temperature;
uint16_t Extruder::dtemp;
uint8_t Extruder::dcycle = 128;

short temptable[NUMTEMPS][2] = {
  {1, 841},
  {54, 255},
  {107, 209},
  {160, 184},
  {213, 166},
  {266, 153},
  {319, 142},
  {372, 132},
  {425, 124},
  {478, 116},
  {531, 108},
  {584, 101},
  {637, 93},
  {690, 86},
  {743, 78},
  {796, 70},
  {849, 61},
  {902, 50},
  {955, 34},
  {1008, 3}
};

void Extruder::Init() {
  //  io_set_high(DDR(EXTRUDER_PIN), PIN(EXTRUDER_PIN));
  io_set_high(DDR(EXTRUDER_FAN_PIN), PIN(EXTRUDER_FAN_PIN));

  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS22);

  OCR2A = 10;

  Extruder::dcycle = 128;

  io_set_high(PORT(EXTRUDER_FAN_PIN), PIN(EXTRUDER_FAN_PIN));
}

void Extruder::UpdateTemperature() {
  uint16_t currTemp = Extruder::GetTemperature();

  OCR2A = Extruder::dcycle;

  if(currTemp < Extruder::dtemp) {
    if(Extruder::dcycle != 255)
      ++Extruder::dcycle;
  } else if(currTemp > Extruder::dtemp) {
    if(Extruder::dcycle != 0)
      --Extruder::dcycle;
  }
}

ISR(ADC_vect) {
  ATDC::val = ADC;
  Extruder::UpdateTemperature();
}

uint16_t Extruder::GetTemperature() {
  uint16_t adc = ATDC::val;

  uint16_t d = abs(temptable[0][0] - adc);
  uint16_t index = 0;

  for(int i = 0; i < NUMTEMPS; ++i) {
    uint16_t cd = abs(temptable[i][0] - adc);

    if(cd < d) {
      index = i;
      d = cd;
    }
  }

  return temptable[index][1];
}
