
#include <avr/io.h>

#include "mirpm.h"
#include "src/commands/serialcommand.h"
#include "src/control/stepper.h"

#define SINGULAR_MODULE true

namespace MISCR {
  void setup(void);
  void loop(void);
}
