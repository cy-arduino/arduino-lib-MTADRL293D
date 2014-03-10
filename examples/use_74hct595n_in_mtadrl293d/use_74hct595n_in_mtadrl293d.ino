#include "HC595.h"

HC595 hc595;
void setup(){
  Serial.begin(115200);

  //  while (!Serial){
  //    ;
  //  }

  delay(1000);
  Serial.println("=== setup() ===");

  hc595.enableDbg(true);
  hc595.begin(8, 7, HC595_PIN_NC, 4, 12); //74HCT595N in MTADRL293D
  hc595.enableOutput(true);

  hc595.writeByte((unsigned char)0b00001000);

  pinMode(11, OUTPUT);
  analogWrite(11, 0);

  delay(1000);
}

void loop(){
  Serial.println("=== loop() ===");

  hc595.writeByte((unsigned char)0b00001000);
  Serial.println("##p 0");
  analogWrite(11, 0);
  delay(1000);

  Serial.println("##p 1");
  analogWrite(11, 200);
  delay(2000);

  hc595.writeByte((unsigned char)0b00000100);
  Serial.println("##n 0");
  analogWrite(11, 0);
  delay(1000);

  Serial.println("##  1");
  analogWrite(11, 200);
  delay(2000);
}





