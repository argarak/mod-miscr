
#ifndef _H_SERIALCOMMAND
#define _H_SERIALCOMMAND

#include "../../mirpm.h"
#include "../control/stepper.h"

namespace SerialCommand {
  int GetSerialInput();
  void PrintSupportedCommands();

  int ParseCommand(char* c);
}

#endif
