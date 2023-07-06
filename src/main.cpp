#include <Arduino.h>
#include "pt2248.h"
#include <stdio.h>

st_pt2248 pPT2248;

void setup() {
  Serial.begin(9600);
  pt2248Init(&pPT2248, 10, 2, 4, 6, 8);
  //Serial.begin(9600);
}

void loop() {
    getState(&pPT2248);
    if (pPT2248.DATA_STATE != 0)
        single_short(&pPT2248, pPT2248.DATA_STATE);
    //int state = digitalRead(pPT2248.DATA_INPUT_PIN[0]); // Đọc trạng thái của chân pin
    int state = digitalRead(pPT2248.DATA_OUT_PIN); // Đọc trạng thái của chân pin
    Serial.println(state);              //Xuất trạng thái
    //delay(250);
  
    pPT2248.DATA_STATE = 0;
}