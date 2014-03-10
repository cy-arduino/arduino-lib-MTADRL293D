#include "Arduino.h"
#include "HC595.h"

HC595::HC595(){
  DBG = false;
  INITIALIZED = false;
  pinDS = pinOE = pinMR = pinSHCP = pinSTCP = HC595_PIN_NC;
}

void HC595::enableDbg(boolean en){
  DBG = en;
}

int HC595::enableOutput(boolean en){
  if(!INITIALIZED){
    if(DBG) Serial.println("[HC595] ERR setOutput(): not initialized!");
    return HC595_ERR_INIT;
  }
  if(pinOE <= 0){
    if(DBG) Serial.println("[HC595] ERR setOutput(): pinOE " + String(pinOE) + " is invalid!");
    return HC595_ERR_PIN;
  }

  if(DBG) Serial.println("[HC595] DBG setOutput(): " + String((en)? "on":"off(Z)"));

  if(en)
    digitalWrite(pinOE, LOW);
  else
    digitalWrite(pinOE, HIGH);
}

//take 3*8+ HELF_CLK_US
int HC595::writeByte(unsigned char b){
  if(!INITIALIZED){
    if(DBG) Serial.println("[HC595] ERR writeByte(): not initialized!");
    return HC595_ERR_INIT;
  }

  if(DBG) Serial.println("[HC595] DBG writeByte(): byte:" + String((unsigned char)b, BIN));

  for(int i=7; i>=0; i--){
    int value = (b>>i) & 0x01;
    if(DBG) Serial.println("[HC595] DBG writeByte(): write Q" + String(i) + "=" + String(value));

    digitalWrite(pinDS, ((value)?HIGH:LOW));
    delayMicroseconds(HC595_HELF_CLK_US);
    digitalWrite(pinSHCP, HIGH);
    delayMicroseconds(HC595_HELF_CLK_US);
    digitalWrite(pinSHCP, LOW);
    delayMicroseconds(HC595_HELF_CLK_US);
  }

  digitalWrite(pinSTCP, HIGH);
  delayMicroseconds(HC595_HELF_CLK_US);
  digitalWrite(pinSTCP, LOW);
  delayMicroseconds(HC595_HELF_CLK_US);
}

int HC595::begin(int ds, int oe, int mr, int shcp, int stcp){

  if(DBG) Serial.println("[HC595] DBG begin(): ds=" + String(ds) + " oe=" + String(oe) + " mr=" + String(mr) + " shcp=" + String(shcp) + " stcp=" + String(stcp));

  if(ds < 0 || shcp < 0 || stcp < 0){
    //OE/MR NC is acceptable
    if(DBG) Serial.write("[HC595] ERR begin(): invalid pin");
    return HC595_ERR_PIN;
  }

  INITIALIZED = true;

  pinDS = ds;
  pinOE = oe;
  pinMR = mr;
  pinSHCP = shcp;
  pinSTCP = stcp;

  //setup gpio pin
  if(DBG) Serial.println("[HC595] DBG begin(): initial GPIO pins");
  pinMode(pinDS, OUTPUT);
  digitalWrite(pinDS, LOW);

  if(pinMR>=0){
    pinMode(pinMR, OUTPUT);

    //clear shift register
    digitalWrite(pinMR, HIGH);
    delay(10);
    digitalWrite(pinMR, LOW);
  }

  if(pinOE>=0){
    pinMode(pinOE, OUTPUT);

    //default output is disable
    enableOutput(false);
  }

  pinMode(pinSHCP, OUTPUT);
  digitalWrite(pinSHCP, LOW);

  pinMode(pinSTCP, OUTPUT);
  digitalWrite(pinSTCP, LOW);
}



