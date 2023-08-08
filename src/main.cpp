/*
#include <Arduino.h>
#include "pt2248.h"
#include <stdio.h>

st_pt2248 pPT2248;

void setup() {
  Serial.begin(9600);
  pt2248Init(&pPT2248, 11, 2, 4, 6, 8);
}

void loop() {
    getState(&pPT2248);
    if (pPT2248.DATA_STATE != 0) {
      single_short(&pPT2248, pPT2248.DATA_STATE);
    }
    int state = digitalRead(pPT2248.DATA_INPUT_PIN[0]); // Đọc trạng thái của chân pin
    Serial.println(state);
    //delay(250);
  
    pPT2248.DATA_STATE = 0;
}
*/

#include <Arduino.h>
//#include "pt2248.h"
#include <stdio.h>
#include <IRremote.h>


st_pt2248 pPT2248;

int singleButtonState7 = HIGH;   // Trạng thái trước của nút bấm single
int singleButtonState8 = HIGH;   // Trạng thái trước của nút bấm single
int singleButtonState9 = HIGH;   // Trạng thái trước của nút bấm single
int singleButtonState10 = HIGH;   // Trạng thái trước của nút bấm single




void setup() {
  Serial.begin(9600);
  pt2248Init(&pPT2248, 11, 2, 4, 6, 8);
}

void loop() {
  int currentSingle7 = pPT2248.DATA_INPUT_PIN[0];

  int currentSingle8 = pPT2248.DATA_INPUT_PIN[1];

  int currentSingle9 = pPT2248.DATA_INPUT_PIN[2];

  int currentSingle10 = pPT2248.DATA_INPUT_PIN[3];


  // Ham gui tin hieu single shot khi nhan nut o day voi command Word la 7: 
  if(currentSingle7 != singleButtonState7){
    if(currentSingle7 == LOW){
      Serial.print("dung");
      //digitalWrite(irLedPin, HIGH);
      //sendSingleShotSignal(dataBits7);
      //sendSingleShotSignal(dataBits7);
      irsend.sendSony(sonyCode, 12);
    }else{
      //digitalWrite(irLedPin, LOW);
      noTone(pPT2248.DATA_OUT_PIN); // Dừng lại tín hiệu PWM
    }
  }

  // Ham gui tin hieu single shot khi nhan nut o day voi command Word la 8: 
  if(currentSingle8 != singleButtonState8){
    if(currentSingle8 == LOW){
      //digitalWrite(irLedPin, HIGH);
      //{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}
      unsigned int rawData[] = {420, 1262, 420, 1262, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 420, 1262, 420, 1262};
      //unsigned int rawData[] = {1600, 1600, 560, 1600, 560, 560, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560};
      irsend.sendRaw(rawData, 12, 38);
      //sendSingleShotSignal(dataBits8);
      //sendSingleShotSignal(dataBits9);
    }else{
      noTone(pPT2248.DATA_OUT_PIN); // Dừng lại tín hiệu PWM   
    }
  }
  
  if(currentSingle9 != singleButtonState9){
    if(currentSingle9 == LOW){
      //digitalWrite(irLedPin, HIGH);
      //{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}
      unsigned int rawData[] = {420, 1262, 420, 1262, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 420, 1262, 420, 1262};
      //unsigned int rawData[] = {1600, 1600, 560, 1600, 560, 560, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560};
      irsend.sendRaw(rawData, 12, 38);
      //sendSingleShotSignal(dataBits8);
      //sendSingleShotSignal(dataBits9);
    }else{
      noTone(pPT2248.DATA_OUT_PIN); // Dừng lại tín hiệu PWM   
    }
  }

  if(currentSingle10 != singleButtonState10){
    if(currentSingle10 == LOW){
      //digitalWrite(irLedPin, HIGH);
      //{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}
      unsigned int rawData[] = {420, 1262, 420, 1262, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 1262, 420, 420, 1262, 420, 1262, 420, 1262, 420, 1262};
      //unsigned int rawData[] = {1600, 1600, 560, 1600, 560, 560, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560, 1600, 560};
      irsend.sendRaw(rawData, 12, 38);
      //sendSingleShotSignal(dataBits8);
      //sendSingleShotSignal(dataBits9);
    }else{
      noTone(pPT2248.DATA_OUT_PIN); // Dừng lại tín hiệu PWM   
    }
  }
  /*
  * Cap nhat trang thai truoc cua dau 6 va dau 7
  * Lay thong tin tu cac chan 6 va 7 cua vi dieu khien 
  */ 
  singleButtonState7 = currentSingle7;
  singleButtonState8 = currentSingle8;
  singleButtonState9 = currentSingle9;
  singleButtonState10 = currentSingle10;

  }