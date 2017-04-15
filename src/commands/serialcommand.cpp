
#include "serialcommand.h"
#include "gcode/gcode.h"

char* strcpy(char *strDest, const char *strSrc) {
  char *temp = strDest;
  while(*strDest++ = *strSrc++);
  return temp;
}

int SerialCommand::GetSerialInput() {
  if(Motor::AreCurrentlyUpdated())
    return 1;

  char* b = UART::ReadString();
  char c[256];

  strcpy(c, b);

  free(b);

  SerialCommand::ParseCommand(c);

  return 0;
}

int getIndex(const char* string) {
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

int getIndexes(const char* string) {
  uint8_t i = 0;

  while(*string) {
    if(*string > 64 && *string < 91)
      i++;

    *string++;
  }

  return i;
}

void SerialCommand::PrintSupportedCommands() {
  UART::Print("none!");
}

int SerialCommand::ParseCommand(char* c) {
  if(c && !c[0])
    return 1;

  char a[10][64];

  int indexes = getIndexes(c);

  int b = 0;

  for(int b = 0; b < indexes; b++) {
    int index = getIndex(c);

    uint8_t offset = 0;

    if(index == 0)
      index = UART::Strlen(c);

    for(int i = 0; i < index; i++) {
      if(*(c + i) != ' ')
        a[b][i] = *(c + i);
      else
        offset++;
    }

    a[b][index - offset] = '\0';

    c = c + index;
  }

  GCode::Lookup(a, indexes);
}
