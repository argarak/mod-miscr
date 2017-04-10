
#include "../../mirpm.h"

namespace SerialCommand {
  int GetSerialInput();
  void PrintSupportedCommands();

  bool ParseCommand(char* b);
}
