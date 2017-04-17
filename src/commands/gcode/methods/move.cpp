
#include "method.h"
#include "../../../control/stepper.h"
#include "../../../control/feedrate.h"
#include "../../msg.h"

bool Command::commandIssued = false;

int strcmp(const char* s1, const char* s2) {
  while(*s1 && (*s1 == *s2))
      s1++; s2++;
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int Command::IsComplete() {
  if(!commandIssued)
    return 2;

  if(!Motor::AreCurrentlyUpdated())
    return 0;

  return 1;
}

bool Command::CheckMultipleArguments(const char(*parameters)[64],
                                     uint8_t l, const char* arguments) {
  int arg[10] = {0};

  for(int i = 0; i < l; i++) {
    char t = parameters[i][0];

    for(int a = 0; a < UART::Strlen(arguments); a++)
      if(t == arguments[a]) {
        if(arg[a] == 1)
          return false;
        arg[a]++;
      }
  }

  return true;
}

int Command::GCodeG0(uint8_t code, const char(*parameters)[64],
                     uint8_t l) {
  //if(code != 0)
  //  return 1;

  // No duplicate arguments
  if(!CheckMultipleArguments(parameters, l, "XYZEF"))
    return 2;

  for(int i = 0; i < l; i++)
    if(parameters[i][0] == 'F')
      Feedrate::Set(GCode::ConvertToInt(parameters[i]));

  Feedrate::Calc(parameters, l);

  Command::commandIssued = true;

  for(int i = 0; i < l; i++) {
    switch(parameters[i][0]) {
    case 'X':
      Motor::X.Step(GCode::ConvertToDouble(parameters[i]));
      break;
    case 'Y':
      Motor::Y.Step(GCode::ConvertToDouble(parameters[i]));
      break;
    case 'Z':
      Motor::Z.Step(GCode::ConvertToDouble(parameters[i]));
      break;
    case 'E':
      Motor::E.Step(GCode::ConvertToDouble(parameters[i]));
      break;
    case 'S':
      break;
    }
  }

  return 0;
}

int Command::GCodeG1(uint8_t code, const char(*parameters)[64],
                     uint8_t l) {
  return 1;
}

int Command::GCodeG28(uint8_t code, const char(*parameters)[64],
                      uint8_t l) {
  // No duplicate arguments
  if(!CheckMultipleArguments(parameters, l, "XYZ"))
    return 2;

  bool prevValue = GCode::absolute;
  GCode::absolute = true;

  if(l != 1) {
    for(int i = 0; i < l; i++) {
      switch(parameters[i][0]) {
      case 'X':
        Motor::X.Step((double)0);
        break;
      case 'Y':
        Motor::Y.Step((double)0);
        break;
      case 'Z':
        Motor::Z.Step((double)0);
        break;
      }
    }
  } else {
    // Set all motors to 0
    Motor::X.Step((double)0);
    Motor::Y.Step((double)0);
    Motor::Z.Step((double)0);
  }

  GCode::absolute = prevValue;

  Message::OK();

  return 0;
}

int Command::GCodeG92(uint8_t code, const char(*parameters)[64],
                      uint8_t l) {
  // No duplicate arguments
  if(!CheckMultipleArguments(parameters, l, "XYZ"))
    return 2;

  if(l != 1) {
    for(int i = 0; i < l; i++) {
      switch(parameters[i][0]) {
      case 'X':
        Motor::X.pos = GCode::ConvertToDouble(parameters[i]);
        break;
      case 'Y':
        Motor::Y.pos = GCode::ConvertToDouble(parameters[i]);
        break;
      case 'Z':
        Motor::Z.pos = GCode::ConvertToDouble(parameters[i]);
        break;
      case 'E':
        Motor::E.pos = GCode::ConvertToDouble(parameters[i]);
        break;
      }
    }
  } else {
    // Set all positions to 0
    Motor::X.pos = (double)0;
    Motor::Y.pos = (double)0;
    Motor::Z.pos = (double)0;
    Motor::E.pos = (double)0;
  }

  Message::OK();

  return 0;
}
