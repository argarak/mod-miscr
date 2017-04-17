
#include "stepper.h"
#include "feedrate.h"
#include "../../mirpm.h"
#include "../commands/msg.h"
#include "../commands/gcode/gcode.h"

#include <math.h>

void Stepper::Init() {
  io_set_high(*step.portd,   step.pin);
  io_set_high(*dir.portd,    dir.pin);
  io_set_high(*enable.portd, enable.pin);

  micro_delay = 15;
}

void Stepper::ChangeDir(bool val) {
  if(val)
    io_set_high(*dir.port, dir.pin);
  else
    io_set_low(*dir.port, dir.pin);
}

int Stepper::Step(const double mm) {
  if(!GCode::absolute) {
    if(mm == 0)
      return 1;

    if(mm < 0) {
      ChangeDir(true);
      steps = ceil(-mm * stepsPerMM);
    } else {
      ChangeDir(false);
      steps = ceil(mm * stepsPerMM);
    }

    update = true;

    pos += mm;
  } else {
    if(mm == pos)
      return 1;

    double diff = mm - pos;

    if(diff < 0) {
      ChangeDir(true);
      steps = ceil(-diff * stepsPerMM);
    } else {
      ChangeDir(false);
      steps = ceil(diff * stepsPerMM);
    }

    update = true;

    pos = mm;
  }

  return 0;
}

int Stepper::Update() {
  --steps;

  if(!update)
    return 1;

  if(steps == 0) {
    update = false;
  }

  io_set_high(*step.port, step.pin);

  for(int i = 0; i < micro_delay; i++)
    _delay_us(1);

  io_set_low(*step.port, step.pin);

  for(int i = 0; i < micro_delay; i++)
    _delay_us(1);

  return 0;
}

Stepper::Stepper(uint16_t nspmm, char type) {
  stepsPerMM = nspmm;

  pos = 0;

  // Prepare for a rushed mess!
  switch(type) {
  case 'X':
    step.pin   = BIT(STEPPER_X_STEP);
    step.ddr   = BITD(STEPPER_X_STEP);
    step.port  = &PORT(STEPPER_X_STEP);
    step.portd = &DDR(STEPPER_X_STEP);

    dir.pin   = BIT(STEPPER_X_DIR);
    dir.ddr   = BITD(STEPPER_X_DIR);
    dir.port  = &PORT(STEPPER_X_DIR);
    dir.portd = &DDR(STEPPER_X_DIR);

    enable.pin   = BIT(STEPPER_X_ENABLE);
    enable.ddr   = BITD(STEPPER_X_ENABLE);
    enable.port  = &PORT(STEPPER_X_ENABLE);
    enable.portd = &DDR(STEPPER_X_ENABLE);

    break;
  case 'Y':
    step.pin   = BIT(STEPPER_Y_STEP);
    step.ddr   = BITD(STEPPER_Y_STEP);
    step.port  = &PORT(STEPPER_Y_STEP);
    step.portd = &DDR(STEPPER_Y_STEP);

    dir.pin   = BIT(STEPPER_Y_DIR);
    dir.ddr   = BITD(STEPPER_Y_DIR);
    dir.port  = &PORT(STEPPER_Y_DIR);
    dir.portd = &DDR(STEPPER_Y_DIR);

    enable.pin   = BIT(STEPPER_Y_ENABLE);
    enable.ddr   = BITD(STEPPER_Y_ENABLE);
    enable.port  = &PORT(STEPPER_Y_ENABLE);
    enable.portd = &DDR(STEPPER_Y_ENABLE);

    break;
  case 'Z':
    step.pin   = BIT(STEPPER_Z_STEP);
    step.ddr   = BITD(STEPPER_Z_STEP);
    step.port  = &PORT(STEPPER_Z_STEP);
    step.portd = &DDR(STEPPER_Z_STEP);

    dir.pin   = BIT(STEPPER_Z_DIR);
    dir.ddr   = BITD(STEPPER_Z_DIR);
    dir.port  = &PORT(STEPPER_Z_DIR);
    dir.portd = &DDR(STEPPER_Z_DIR);

    enable.pin   = BIT(STEPPER_Z_ENABLE);
    enable.ddr   = BITD(STEPPER_Z_ENABLE);
    enable.port  = &PORT(STEPPER_Z_ENABLE);
    enable.portd = &DDR(STEPPER_Z_ENABLE);

    break;
  case 'E':
    step.pin   = BIT(STEPPER_E_STEP);
    step.ddr   = BITD(STEPPER_E_STEP);
    step.port  = &PORT(STEPPER_E_STEP);
    step.portd = &DDR(STEPPER_E_STEP);

    dir.pin   = BIT(STEPPER_E_DIR);
    dir.ddr   = BITD(STEPPER_E_DIR);
    dir.port  = &PORT(STEPPER_E_DIR);
    dir.portd = &DDR(STEPPER_E_DIR);

    enable.pin   = BIT(STEPPER_E_ENABLE);
    enable.ddr   = BITD(STEPPER_E_ENABLE);
    enable.port  = &PORT(STEPPER_E_ENABLE);
    enable.portd = &DDR(STEPPER_E_ENABLE);

    break;
  default:
    // Unpredicable things *will* occur!
    break;
  }

  Stepper::Init();
}

Stepper Motor::X(80, 'X');
Stepper Motor::Y(80, 'Y');
Stepper Motor::Z(400, 'Z');
Stepper Motor::E(80, 'E');

bool Motor::AreCurrentlyUpdated() {
  return (Motor::X.update ||
          Motor::Y.update ||
          Motor::Z.update ||
          Motor::E.update);
}
