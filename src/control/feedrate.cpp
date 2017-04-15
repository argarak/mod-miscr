
#include "feedrate.h"
#include "stepper.h"
#include "../commands/gcode/gcode.h"
#include <math.h>

int Feedrate::Calc(const char(*parameters)[64], int l) {

  double distance;

  for(int i = 0; i < l; i++) {
    switch(parameters[i][0]) {
    case 'X':
      distance = GCode::ConvertToDouble(parameters[i]);

      Motor::X.micro_delay = ((distance / (Motor::X.feedrate / 60)) /
                              (distance * Motor::X.stepsPerMM) * 1E6);
      break;
    case 'Y':
      distance = GCode::ConvertToDouble(parameters[i]);

      Motor::Y.micro_delay = ((distance / (Motor::Y.feedrate / 60)) /
                              (distance * Motor::Y.stepsPerMM) * 1E6);
      break;
    case 'Z':
      distance = GCode::ConvertToDouble(parameters[i]);

      Motor::Z.micro_delay = ((distance / (Motor::Y.feedrate / 60)) /
                              (distance * Motor::Z.stepsPerMM) * 1E6);
      break;
    case 'E':
      distance = GCode::ConvertToDouble(parameters[i]);

      Motor::E.micro_delay = ((distance / (Motor::Z.feedrate / 60)) /
                              (distance * Motor::E.stepsPerMM) * 1E6);
      break;
    default:
      return 1;
    }
  }
}

void Feedrate::Set(int feedrate) {
  Motor::X.feedrate = feedrate;
  Motor::Y.feedrate = feedrate;
  Motor::Z.feedrate = feedrate;
  Motor::E.feedrate = feedrate;
}
