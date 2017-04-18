
#include "msg.h"
#include "../control/extruder.h"

void Message::OK() {
  UART::Print("ok\n");
}

char* removeSpaces(char* a) {
  while(*a) {
    if(*a != ' ')
      break;
    a++;
  }

  return a;
}

void Message::CurrentPosition() {
  char buf[10];

  UART::Print("ok");
  UART::Print(" C: ");

  UART::Print("X:");
  UART::Print(removeSpaces(dtostrf(Motor::X.pos, 7, 2, buf)));
  UART::PutChar(' ');

  UART::Print("Y:");
  UART::Print(removeSpaces(dtostrf(Motor::Y.pos, 7, 2, buf)));
  UART::PutChar(' ');

  UART::Print("Z:");
  UART::Print(removeSpaces(dtostrf(Motor::Z.pos, 7, 2, buf)));
  UART::PutChar(' ');

  UART::Print("E:");
  UART::Print(removeSpaces(dtostrf(Motor::E.pos, 7, 2, buf)));
  UART::PutChar('\n');
}

void Message::Temperature() {
  char buf[24];

  UART::Print("ok");

  UART::Print(" T:");
  UART::Print(utoa(Extruder::GetTemperature(), buf, 10));

  // No hotbed
  UART::Print(" B:0");
  UART::Print(" // ");
  UART::Print(utoa(ATDC::val, buf, 10));
  UART::PutChar('\n');
}
