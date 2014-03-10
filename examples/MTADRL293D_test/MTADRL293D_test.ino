#include "MTADRL293D.h"

MTADRL293D l293d;

void setup(){

  Serial.begin(115200);
  while (!Serial){
    ;
  }
  
  delay(5000);
  
  Serial.println("=== loop() ===");

  l293d.enableDbg(true);
  l293d.begin();

  l293d.setMotorDir(MTADRL293D_M1, MTADRL293D_DIR_POS);
  l293d.setMotorDir(MTADRL293D_M2, MTADRL293D_DIR_POS);
  l293d.setMotorDir(MTADRL293D_M3, MTADRL293D_DIR_POS);
  l293d.setMotorDir(MTADRL293D_M4, MTADRL293D_DIR_POS);

  l293d.setMinMotorSpeed(MTADRL293D_M1, 100);
  l293d.setMinMotorSpeed(MTADRL293D_M2, 100);
  l293d.setMinMotorSpeed(MTADRL293D_M3, 100);
  l293d.setMinMotorSpeed(MTADRL293D_M4, 100);

  l293d.setMotorSpeed(MTADRL293D_M1, 0);
  l293d.setMotorSpeed(MTADRL293D_M2, 0);
  l293d.setMotorSpeed(MTADRL293D_M3, 0);
  l293d.setMotorSpeed(MTADRL293D_M4, 0);
}


void loop(){
  Serial.println("=== loop() ===");

  Serial.println("=== m1 pos 100");
  l293d.setMotorDir(MTADRL293D_M1, MTADRL293D_DIR_POS);
  l293d.setMotorSpeed(MTADRL293D_M1, 100);
  delay(3000);

  Serial.println("=== m1 0");
  l293d.setMotorSpeed(MTADRL293D_M1, 0);
  delay(1000);

  Serial.println("=== m1 neg 100");
  l293d.setMotorDir(MTADRL293D_M1, MTADRL293D_DIR_NEG);
  l293d.setMotorSpeed(MTADRL293D_M1, 100);
  delay(3000);

  Serial.println("=== m1 0");
  l293d.setMotorSpeed(MTADRL293D_M1, 0);
  delay(1000);

  Serial.println("=== m3 pos 100");
  l293d.setMotorDir(MTADRL293D_M3, MTADRL293D_DIR_POS);
  l293d.setMotorSpeed(MTADRL293D_M3, 100);
  delay(3000);

  Serial.println("=== m3 0");
  l293d.setMotorSpeed(MTADRL293D_M3, 0);
  delay(1000);

  Serial.println("=== m3 neg 100");
  l293d.setMotorDir(MTADRL293D_M3, MTADRL293D_DIR_NEG);
  l293d.setMotorSpeed(MTADRL293D_M3, 100);
  delay(3000);

  Serial.println("=== m3 0");
  l293d.setMotorSpeed(MTADRL293D_M3, 0);
  delay(1000);

}



