#include "Arduino.h"

#define HC595_PIN_NC -1

#define HC595_ERR_PIN -1
#define HC595_ERR_INIT -2

#define HC595_HELF_CLK_US 1
class HC595{
private:
  boolean DBG;
  boolean INITIALIZED;
  int pinDS;
  int pinOE;
  int pinMR;
  int pinSHCP;
  int pinSTCP;
public:
  HC595();
  int begin(int ds, int oe, int mr, int shcp, int stcp);
  void enableDbg(boolean en);
  int enableOutput(boolean en);
  int writeByte(unsigned char b);
};