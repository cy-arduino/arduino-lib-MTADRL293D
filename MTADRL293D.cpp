#include "Arduino.h"
#include "MTADRL293D.h"

MTADRL293D::MTADRL293D(){
  DBG = INITIALIZED = false;

  hc595_data = 0;

  //Motor enable pin
  motor_en_pin[MTADRL293D_M1] = 11;
  motor_en_pin[MTADRL293D_M2] = 3;
  motor_en_pin[MTADRL293D_M3] = 5;
  motor_en_pin[MTADRL293D_M4] = 6;

}

void MTADRL293D::begin(){
  if(DBG) Serial.println("[MTADRL293D] DBG begin()");

  //init HC595
  hc595.begin(8, 7, HC595_PIN_NC, 4, 12);
  hc595.enableOutput(true);
  hc595.writeByte((unsigned char)hc595_data);

  INITIALIZED = true;

  if(DBG) Serial.println("[MTADRL293D] DBG begin(): set motor direction " + String(MTADRL293D_DIR_POS));
  //after initialized
  //set motor direction
  setMotorDir(MTADRL293D_M1, MTADRL293D_DIR_POS);
  setMotorDir(MTADRL293D_M2, MTADRL293D_DIR_POS);
  setMotorDir(MTADRL293D_M3, MTADRL293D_DIR_POS);
  setMotorDir(MTADRL293D_M4, MTADRL293D_DIR_POS);

  //set min motor speed
  if(DBG) Serial.println("[MTADRL293D] DBG begin(): set motor min speed " + String(MTADRL293D_SPEED_MIN_DEF));
  setMinMotorSpeed(MTADRL293D_M1, MTADRL293D_SPEED_MIN_DEF);
  setMinMotorSpeed(MTADRL293D_M2, MTADRL293D_SPEED_MIN_DEF);
  setMinMotorSpeed(MTADRL293D_M3, MTADRL293D_SPEED_MIN_DEF);
  setMinMotorSpeed(MTADRL293D_M4, MTADRL293D_SPEED_MIN_DEF);

}

void MTADRL293D::enableDbg(boolean en){
  DBG = en;
}

int MTADRL293D::setMotorSpeed(int m, int s){
  if(!INITIALIZED){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorSpeed(): not initilized");
    return MTADRL293D_ERR_INIT;		
  }

  if(m < 0 || m >=MTADRL293D_M_NUM){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorSpeed(): invalid motor: " + String(m));
    return MTADRL293D_ERR_PARM;
  }

  if(s < MTADRL293D_SPEED_MIN || s > MTADRL293D_SPEED_MAX){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorSpeed(): invalid speed: " + String(s));
    return MTADRL293D_ERR_PARM;
  }

  if(DBG) Serial.println("[MTADRL293D] DBG setMotorSpeed(): m=" + String(m) + " speed=" + String(s));

  int real_s = 0;
  if(s > 0)		
    real_s = motor_min_speed[m] + (((double)s*(MTADRL293D_SPEED_MAX-motor_min_speed[m]))/MTADRL293D_SPEED_MAX);

  if(DBG) Serial.println("[MTADRL293D] DBG setMotorSpeed(): real speed=" + String(real_s));

  analogWrite(motor_en_pin[m], real_s);
}

int MTADRL293D::setMinMotorSpeed(int m, int ms){
  if(!INITIALIZED){
    if(DBG) Serial.println("[MTADRL293D] DBG setMinMotorSpeed(): not initilized");
    return MTADRL293D_ERR_INIT;		
  }

  if(m < 0 || m >=MTADRL293D_M_NUM){
    if(DBG) Serial.println("[MTADRL293D] DBG setMinMotorSpeed(): invalid motor: " + String(m));
    return MTADRL293D_ERR_PARM;
  }

  if(ms < MTADRL293D_SPEED_MIN || ms >MTADRL293D_SPEED_MAX){
    if(DBG) Serial.println("[MTADRL293D] DBG setMinMotorSpeed(): invalid min speed: " + String(ms));
    return MTADRL293D_ERR_PARM;
  }

  if(DBG) Serial.println("[MTADRL293D] DBG setMinMotorSpeed(): m=" + String(m) + " min speed=" + String(ms));

  motor_min_speed[m] = ms;
}

int MTADRL293D::setMotorDir(int m, int dir){
  if(!INITIALIZED){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): not initilized");
    return MTADRL293D_ERR_INIT;		
  }

  if(m < 0 || m >=MTADRL293D_M_NUM){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): invalid motor: " + String(m));
    return MTADRL293D_ERR_PARM;
  }

  if(dir != MTADRL293D_DIR_POS && dir != MTADRL293D_DIR_NEG){
    if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): invalid direction: " + String(dir));
    return MTADRL293D_ERR_PARM;	
  }

  if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): m=" + String(m) + " dir=" + String(dir));

  motor_dir[m] = dir;

  int a,b;

  if(dir == MTADRL293D_DIR_POS){
    a = 1; 
    b = 0;
  }
  else{
    a = 0;
    b = 1;
  }

  if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): hc595_data: before" + String(hc595_data, BIN));
  switch(m){
  case MTADRL293D_M1:
    bitWrite(hc595_data, 2, a);
    bitWrite(hc595_data, 3, b);
    break;
  case MTADRL293D_M2:
    bitWrite(hc595_data, 1, a);
    bitWrite(hc595_data, 4, b);
    break;
  case MTADRL293D_M3:
    bitWrite(hc595_data, 0, a);
    bitWrite(hc595_data, 6, b);
    break;
  case MTADRL293D_M4:
    bitWrite(hc595_data, 5, a);
    bitWrite(hc595_data, 7, b);
    break;
  }

  //apply to HC595
  if(DBG) Serial.println("[MTADRL293D] DBG setMotorDir(): hc595_data: after" + String(hc595_data, BIN));
  hc595.writeByte((unsigned char)hc595_data);
}