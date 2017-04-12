
class GCodeCommand {
private:
  typedef void (*gcode_method_t)(char* c, int l, char* rp, char* op);
public:
  char* command;
  int length;
  char* required_parameters;
  char* optional_parameters;

  gcode_method_t method;

  void CollMethod() {
    (*method)(command, length, required_parameters, optional_parameters);
  }

  GCodeCommand(char* nc, int nl, char* nrp, char* nop, gcode_method_t nm) {
    command = nc;
    length = nl;
    required_parameters = nrp;
    optional_parameters = nop;
    method = nm;
  }
};

typedef struct gcode_struct gcode;

namespace GCode {
  GCodeCommand* List[256];
  void Lookup(char* a[]);
}
