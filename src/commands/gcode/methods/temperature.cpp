
#include "method.h"
#include "../../../control/extruder.h"

int Command::GCodeM104(uint8_t code, const char(*parameters)[64],
              uint8_t l) {

  // No duplicate arguments
  if(!CheckMultipleArguments(parameters, l, "S"))
    return 2;

  for(int i = 0; i < l; i++) {
    switch(parameters[i][0]) {
    case 'S':
      Extruder::dtemp = GCode::ConvertToInt(parameters[i]);
      break;
    }
  }

  return 0;
}

int Command::GCodeM106(uint8_t code, const char(*parameters)[64],
                       uint8_t l) {

  // No duplicate arguments
  if(!CheckMultipleArguments(parameters, l, "S"))
    return 2;

  for(int i = 0; i < l; i++) {
    switch(parameters[i][0]) {
    case 'S':
      // No PWM yet!
      break;
    }
  }

  Extruder::FanOn();

  return 0;
}
