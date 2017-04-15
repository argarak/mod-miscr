
#include <avr/io.h>
#include <stdlib.h>

namespace GCode {
  int ExecuteGCommand(uint8_t code, const char(*parameters)[64],
                              uint8_t l);

  int ExecuteMCommand(uint8_t code, const char(*parameters)[64],
                      uint8_t l);

  uint8_t ConvertToInt(const char* command);

  double ConvertToDouble(const char* parameter);

  void Lookup(const char(*a)[64], uint8_t l);
}
