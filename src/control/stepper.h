
#include "../../mirpm.h"

#define STEPPER_X_STEP   C,1
#define STEPPER_X_DIR    C,2
#define STEPPER_X_ENABLE L,3

#define STEPPER_Y_STEP   C,7
#define STEPPER_Y_DIR    F,7
#define STEPPER_Y_ENABLE C,3

#define STEPPER_Z_STEP   D,3
#define STEPPER_Z_DIR    D,5
#define STEPPER_Z_ENABLE K,0

#define STEPPER_E_STEP   B,7
#define STEPPER_E_DIR    G,3
#define STEPPER_E_ENABLE B,5

class Stepper {
private:
  gpio_t step;
  gpio_t dir;
  gpio_t enable;
public:
  uint16_t pos;
  uint16_t stepsPerMM;

  bool update;
  uint32_t steps;

  void Init();

  int Step(float mm);

  int Update();

  Stepper(uint16_t nspmm, char type);
};
