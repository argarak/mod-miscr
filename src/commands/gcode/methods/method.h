
// includes and stuff
#include "../gcode.h"

namespace Command {

  bool CheckMultipleArguments(const char(*parameters)[64], uint8_t l,
                              const char* arguments);

  int GCodeG0(uint8_t code, const char(*parameters)[64], uint8_t l);
  int GCodeG1(uint8_t code, const char(*parameters)[64], uint8_t l);
}
