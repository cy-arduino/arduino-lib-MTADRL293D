#include "Arduino.h"
#include "HC595.h"

#define MTADRL293D_DIR_POS 1
#define MTADRL293D_DIR_NEG 2

#define MTADRL293D_M_NUM 4
#define MTADRL293D_M1 0
#define MTADRL293D_M2 1
#define MTADRL293D_M3 2
#define MTADRL293D_M4 3

#define MTADRL293D_SPEED_MAX 255 //analogWrite
#define MTADRL293D_SPEED_MIN 0 //analogWrite
#define MTADRL293D_SPEED_MIN_DEF 30 

#define MTADRL293D_ERR_PARM -1
#define MTADRL293D_ERR_INIT -2

class MTADRL293D{
private:
  boolean DBG;
  boolean INITIALIZED;
  HC595 hc595;
  unsigned char hc595_data;
  int motor_en_pin[MTADRL293D_M_NUM];
  int motor_min_speed[MTADRL293D_M_NUM];
  int motor_dir[MTADRL293D_M_NUM];
public:
  MTADRL293D();
  void begin();
  void enableDbg(boolean en);
  int setMotorDir(int m, int dir);
  int setMotorSpeed(int m, int s);
  int setMinMotorSpeed(int m, int ms);
};