
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

int getIndex(char* string, char a) {
  uint8_t i = 0;

  while(*string) {
    if(*string == a) {
      return i;
    }

    i++;
    *string++;
  }
}

void SerialCommand::PrintSupportedCommands() {
  UART::Print("none!");
}

bool SerialCommand::ParseCommand(char* c) {
  char a[10][64];

  for(int b = 0; b < 5; b++) {
    int index = getIndex(c, ' ');

    for(int i = 0; i < index; i++) {
      a[b][i] = *(c + i);
    }

    c = c + index + 1;

    a[b][index] = '\0';

    UART::Print(a[b]);
  }

  return false;
}
