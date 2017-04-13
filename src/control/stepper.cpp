
#include "stepper.h"
#include "feedrate.h"
#include "../../mirpm.h"

void Stepper::Init() {
  io_mode_output(&step.portd,   step.ddr);
  io_mode_output(&dir.portd,    dir.ddr);
  io_mode_output(&enable.portd, enable.ddr);

  io_set_low(&enable.port, enable.pin);
}

int Stepper::Step(float mm) {
  if(mm == 0)
    return 0;

  steps = mm * stepsPerMM;
  update = true;

  pos += mm;
}

int Stepper::Update() {
  if(!update)
    return 1;

  if(steps == 0)
    update = false; return 1;

  io_set_high(&step.port, step.pin);
  _delay_us(feedrate.micro_delay);
  io_set_low(&step.port, step.pin);
  _delay_us(feedrate.micro_delay);

  steps--;

  return 0;
}

Stepper::Stepper(uint16_t nspmm, char type) {
  stepsPerMM = nspmm;

  // Prepare for a rushed mess!
  switch(type) {
  case 'X':
    step.pin   = PIN(STEPPER_X_STEP);
    step.ddr   = BITD(STEPPER_X_STEP);
    step.port  = PORT(STEPPER_X_STEP);
    step.portd = DDR(STEPPER_X_STEP);

    dir.pin   = PIN(STEPPER_X_DIR);
    dir.ddr   = BITD(STEPPER_X_DIR);
    dir.port  = PORT(STEPPER_X_DIR);
    dir.portd = DDR(STEPPER_X_DIR);

    enable.pin   = PIN(STEPPER_X_ENABLE);
    enable.ddr   = BITD(STEPPER_X_ENABLE);
    enable.port  = PORT(STEPPER_X_ENABLE);
    enable.portd = DDR(STEPPER_X_ENABLE);

    break;
  case 'Y':
    step.pin   = PIN(STEPPER_Y_STEP);
    step.ddr   = BITD(STEPPER_Y_STEP);
    step.port  = PORT(STEPPER_Y_STEP);
    step.portd = DDR(STEPPER_Y_STEP);

    dir.pin   = PIN(STEPPER_Y_DIR);
    dir.ddr   = BITD(STEPPER_Y_DIR);
    dir.port  = PORT(STEPPER_Y_DIR);
    dir.portd = DDR(STEPPER_Y_DIR);

    enable.pin   = PIN(STEPPER_Y_ENABLE);
    enable.ddr   = BITD(STEPPER_Y_ENABLE);
    enable.port  = PORT(STEPPER_Y_ENABLE);
    enable.portd = DDR(STEPPER_Y_ENABLE);

    break;
  case 'Z':
    step.pin   = PIN(STEPPER_Z_STEP);
    step.ddr   = BITD(STEPPER_Z_STEP);
    step.port  = PORT(STEPPER_Z_STEP);
    step.portd = DDR(STEPPER_Z_STEP);

    dir.pin   = PIN(STEPPER_Z_DIR);
    dir.ddr   = BITD(STEPPER_Z_DIR);
    dir.port  = PORT(STEPPER_Z_DIR);
    dir.portd = DDR(STEPPER_Z_DIR);

    enable.pin   = PIN(STEPPER_Z_ENABLE);
    enable.ddr   = BITD(STEPPER_Z_ENABLE);
    enable.port  = PORT(STEPPER_Z_ENABLE);
    enable.portd = DDR(STEPPER_Z_ENABLE);

    break;
  case 'E':
    step.pin   = PIN(STEPPER_E_STEP);
    step.ddr   = BITD(STEPPER_E_STEP);
    step.port  = PORT(STEPPER_E_STEP);
    step.portd = DDR(STEPPER_E_STEP);

    dir.pin   = PIN(STEPPER_E_DIR);
    dir.ddr   = BITD(STEPPER_E_DIR);
    dir.port  = PORT(STEPPER_E_DIR);
    dir.portd = DDR(STEPPER_E_DIR);

    enable.pin   = PIN(STEPPER_E_ENABLE);
    enable.ddr   = BITD(STEPPER_E_ENABLE);
    enable.port  = PORT(STEPPER_E_ENABLE);
    enable.portd = DDR(STEPPER_E_ENABLE);

    break;
  default:
    // Unpredicable things *will* occur!
    break;
  }

  Stepper::Init();
}

Stepper Motor::X(80, 'X');
Stepper Motor::Y(80, 'Y');
Stepper Motor::Z(80, 'Z');
Stepper Motor::E(80, 'E');

bool Motor::AreCurrentlyUpdated() {
  return (Motor::X.update ||
          Motor::Y.update ||
          Motor::Z.update ||
          Motor::E.update);
}
