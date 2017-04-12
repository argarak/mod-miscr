
#include "../../mirpm.h"

namespace SerialCommand {
  int GetSerialInput();
  void PrintSupportedCommands();

  int ParseCommand(char* c);
}
