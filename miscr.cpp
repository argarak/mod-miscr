/****************************************************************************/
/*                                                                          */
/*          ▀                                                               */
/* ▄▄▄▄▄  ▄▄▄     ▄▄▄    ▄▄▄    ▄ ▄▄                                        */
/* █ █ █    █    █   ▀  █▀  ▀   █▀  ▀                                       */
/* █ █ █    █     ▀▀▀▄  █       █                                           */
/* █ █ █  ▄▄█▄▄  ▀▄▄▄▀  ▀█▄▄▀   █    version 0.2-dev                        */
/*                                                                          */
/*                                                                          */
/* Microcontroller Interfaced Stepper Control for Ramps                     */
/* (now mirpm-complacent!)                                                  */
/*                                                                          */
/* Copyright 2017 Jakub Kukiełka                                            */
/*                                                                          */
/* Licensed under the Apache License, Version 2.0 (the "License");          */
/* you may not use this file except in compliance with the License.         */
/* You may obtain a copy of the License at                                  */
/*                                                                          */
/*    http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                          */
/* Unless required by applicable law or agreed to in writing, software      */
/* distributed under the License is distributed on an "AS IS" BASIS,        */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and      */
/* limitations under the License.                                           */
/****************************************************************************/

#include "miscr.h"
#include "src/control/extruder.h"
#include "src/commands/msg.h"
#include "src/commands/gcode/methods/method.h"
#include "src/display.h"

void MISCR::setup() {
  UART::Init(); // Run just in case
  _delay_ms(30);

  UART::Print("miscr v0.2-dev ready\n");

  ATDC::Init(13);
  Extruder::Init();

  Motor::X.Init();
  Motor::Y.Init();
  Motor::Z.Init();
  Motor::E.Init();

  Display::Init();

  Message::OK();
}

void MISCR::loop() {
  Motor::X.Update();
  Motor::Y.Update();
  Motor::Z.Update();
  Motor::E.Update();

  Extruder::UpdateTemperature();

  if(Command::IsComplete() == 0) {
    Command::commandIssued = false;
    Message::OK();
  }

  SerialCommand::GetSerialInput();
}
