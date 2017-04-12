
#include "serialcommand.h"
#include "../control/stepper.h"

int SerialCommand::GetSerialInput() {
  if(sX.update ||
     sY.update ||
     sZ.update ||
     sE.update)
    return 1;
  while(1) {
    char* b = UART::ReadString();

    UART::Print(b);

    if(b && b[0]) {
      SerialCommand::ParseCommand(b);
      break;
    }

    free(b);
  }

  return 0;
}

int getIndex(char* string) {
  uint8_t i = 0;

  while(*string) {
    if(*string > 64 && *string < 91 && i != 0) {
      return i;
    }

    i++;
    *string++;
  }

  return 0;
}

void SerialCommand::PrintSupportedCommands() {
  UART::Print("none!");
}

int SerialCommand::ParseCommand(char* c) {
  char a[10][64];

  if(c && !c[0]) {
    UART::Print("empty string");
    return 1;
  }

  UART::Print(" >> ");
  UART::Print(c);
  UART::Print("\n\n");

  for(int b = 0; b < 5; b++) {
    int index = getIndex(c);

    if(index == 0)
      index = UART::Strlen(c);

    unsigned int offset = 0;

    for(int i = 0; i < index; i++) {
      if(*(c + i) != ' ')
        a[b][i] = *(c + i);
      else
        offset++;
    }

    c = c + index;

    if(index != 0)
      a[b][index - offset] = '\0';

    char buf[20];

    // Debugging!
    UART::Print("index:: ");
    UART::Print(itoa(index, buf, 10));
    UART::Print("\n\n");

    UART::Print("c:: ");
    UART::Print(c);
    UART::Print("\n\n");

    UART::Print("offset:: ");
    UART::Print(itoa(offset, buf, 10));
    UART::Print("\n\n");

    UART::Print("a[b]:: ");
    UART::Print(a[b]);
    UART::Print("\n\n");
  }

  free(c);

  //GCode::Lookup(a);
}
