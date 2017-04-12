
class Feedrate {
public:
  float micro_delay;

  void SetDelay(float md) {
    micro_delay = md;
  }
};

Feedrate feedrate;
