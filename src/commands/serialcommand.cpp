
#include "serialcommand.h"

int SerialCommand::GetSerialInput() {
  while(1) {
    char* b = UART::ReadString();

    if(b[0] != '\0') {
      SerialCommand::ParseCommand(b);
      break;
    }

    free(b);
  }

  return 0;
}

void SerialCommand::PrintSupportedCommands() {
  UART::Print("none!");
}

int getIndex(char a) {
  return 0;
}

bool substring(char* string, uint8_t start, uint8_t end) {
  //char* buffer = (char*) malloc(strlen(string));
  //strncpy(to, from+2, 5);

  return true;
}

bool SerialCommand::ParseCommand(char* b) {
  UART::Print(b);
  return false;
}
