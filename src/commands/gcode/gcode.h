
class GCodeCommand {
private:
  typedef int (*gcode_method_t)(char* c, int l, char* rp, char* op);
public:
  const char* command;
  int length;
  const char* required_parameters;
  const char* optional_parameters;

  gcode_method_t method;

  GCodeCommand(const char* nc, int nl, const char* nrp,
               const char* nop, gcode_method_t nm) {
    command = nc;
    length = nl;
    required_parameters = nrp;
    optional_parameters = nop;
    method = nm;
  }
};

typedef struct gcode_struct gcode;

namespace GCode {
  void Lookup(char(*a)[64]);
}
