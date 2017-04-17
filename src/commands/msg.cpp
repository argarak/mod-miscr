
#include "msg.h"

void Message::OK() {
  UART::Print("ok\n");
}

void Message::CurrentPosition() {
  char buf[10];

  UART::Print("ok");
  UART::Print(" C: ");

  UART::Print("X:");
  UART::Print(dtostrf(Motor::X.pos, 7, 2, buf));
  UART::PutChar(' ');

  UART::Print("Y:");
  UART::Print(dtostrf(Motor::Y.pos, 7, 2, buf));
  UART::PutChar(' ');

  UART::Print("Z:");
  UART::Print(dtostrf(Motor::Z.pos, 7, 2, buf));
  UART::PutChar(' ');

  UART::Print("E:");
  UART::Print(dtostrf(Motor::E.pos, 7, 2, buf));
  UART::PutChar('\n');
}
