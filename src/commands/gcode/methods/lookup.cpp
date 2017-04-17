
#include "../gcode.h"
#include "../../../../mirpm.h"
#include "method.h"
#include "../../msg.h"

bool GCode::absolute = false;

int GCode::ExecuteGCommand(uint8_t code, const char(*parameters)[64],
                            uint8_t l) {
  switch(code) {
  case 0:
    Command::GCodeG0(code, parameters, l);
    break;
  case 1:
    Command::GCodeG0(code, parameters, l);
    break;
  case 28:
    Command::GCodeG28(code, parameters, l);
    break;
  case 91:
    // Relative positioning
    GCode::absolute = false;
    Message::OK();
    break;
  case 90:
    // Absolute positioning
    GCode::absolute = true;
    Message::OK();
    break;
  case 92:
    Command::GCodeG92(code, parameters, l);
    break;
  }

  return 0;
}

int GCode::ExecuteMCommand(uint8_t code, const char(*parameters)[64],
                            uint8_t l) {
  switch(code) {
  case 110:
    Message::OK();
    break;
  case 114:
    Message::CurrentPosition();
    break;
  }
  return 0;
}

uint8_t GCode::ConvertToInt(const char* command) {
  return (uint8_t)strtol(command + 1, (char **)NULL, 10);
}

double GCode::ConvertToDouble(const char* parameter) {
  return strtod(parameter + 1, (char **)NULL);
}

void GCode::Lookup(const char(*a)[64], uint8_t l) {
  uint8_t commandIndex = 0;
  char z = a[commandIndex][0];

  if(z == 'N') {
    commandIndex++;
    z = a[commandIndex][0];
  }

  if(z == 'G')
    GCode::ExecuteGCommand(GCode::ConvertToInt(a[commandIndex]), a, l);
  else if(z == 'M')
    GCode::ExecuteMCommand(GCode::ConvertToInt(a[commandIndex]), a, l);
  else
    UART::Print("resend\n");
}
