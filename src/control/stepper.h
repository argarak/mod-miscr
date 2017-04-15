
#ifndef _H_STEPPER
#define _H_STEPPER

#include "../../mirpm.h"
#include "../../../../src/constants/datatypes.h"

#define STEPPER_X_STEP   F,0
#define STEPPER_X_DIR    F,1
#define STEPPER_X_ENABLE D,7

#define STEPPER_Y_STEP   F,6
#define STEPPER_Y_DIR    F,7
#define STEPPER_Y_ENABLE F,2

#define STEPPER_Z_STEP   L,3
#define STEPPER_Z_DIR    L,1
#define STEPPER_Z_ENABLE K,0

#define STEPPER_E_STEP   A,4
#define STEPPER_E_DIR    A,6
#define STEPPER_E_ENABLE A,2

class Stepper {
private:
  gpio_t step;
  gpio_t dir;
  gpio_t enable;
public:
  uint16_t pos;
  uint16_t stepsPerMM;

  float micro_delay;
  double feedrate;

  bool update;
  uint32_t steps;

  void Init();

  int Step(double mm);

  int Update();

  void ChangeDir(bool val);

  Stepper(uint16_t nspmm, char type);
};

namespace Motor {
  extern Stepper X;
  extern Stepper Y;
  extern Stepper Z;
  extern Stepper E;

  bool AreCurrentlyUpdated();
}

#endif
