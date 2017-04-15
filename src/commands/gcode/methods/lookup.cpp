
#include "../gcode.h"
#include "../../../../mirpm.h"
#include "method.h"

int GCode::ExecuteGCommand(uint8_t code, const char(*parameters)[64],
                            uint8_t l) {
  switch(code) {
  case 0:
    Command::GCodeG0(code, parameters, l);
    break;
  case 1:
    Command::GCodeG1(code, parameters, l);
    break;
  default:
    UART::Print("resend\n");
  }

  return 0;
}

int GCode::ExecuteMCommand(uint8_t code, const char(*parameters)[64],
                            uint8_t l) {
  return 0;
}

uint8_t GCode::ConvertToInt(const char* command) {
  return (uint8_t)strtol(command + 1, (char **)NULL, 10);
}

double GCode::ConvertToDouble(const char* parameter) {
  return strtod(parameter + 1, (char **)NULL);
}

void GCode::Lookup(const char(*a)[64], uint8_t l) {
  char z = a[0][0];

  if(z == 'G')
    GCode::ExecuteGCommand(GCode::ConvertToInt(a[0]), a, l);
  else if(z == 'M')
    GCode::ExecuteMCommand(GCode::ConvertToInt(a[0]), a, l);
  else
    UART::Print("resend\n");
}
