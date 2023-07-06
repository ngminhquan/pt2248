#include <stdint.h>
#include <Arduino.h>
#include <stdio.h>

typedef struct {
    uint16_t POWER_ON_PIN;
    uint16_t LED_PIN;
    uint16_t DATA_OUT_PIN;
    uint16_t DATA_INPUT_PIN[4];
    uint16_t ADDRESS_COMMUNICATION;
    uint16_t DATA_STATE ;
} st_pt2248;

#define PT2248_OSC_CLOCK_PERIOD       (422) 
#define PT2248_CLK_PERIOD_3           (PT2248_OSC_CLOCK_PERIOD*3)
#define PT2248_CLK_PERIOD_60          (PT2248_OSC_CLOCK_PERIOD*60)
#define PT2248_CLK_PERIOD_80          (PT2248_OSC_CLOCK_PERIOD*60)



/*
 * PT2248/2249 has 2 types of bit
 */
#define PT2248_BIT_0                  (0)
#define PT2248_BIT_1                  (1)

void pt2248Init(st_pt2248 *PT2248, uint16_t data_out_pin, uint16_t data_input_pin0, uint16_t data_input_pin1, uint16_t data_input_pin2, uint16_t data_input_pin3)
{
  PT2248->DATA_OUT_PIN = data_out_pin;
  PT2248->DATA_INPUT_PIN[0] = data_input_pin0;
  PT2248->DATA_INPUT_PIN[1] = data_input_pin1;
  PT2248->DATA_INPUT_PIN[2] = data_input_pin2;
  PT2248->DATA_INPUT_PIN[3] = data_input_pin3;

  
  pinMode(PT2248->DATA_OUT_PIN    , OUTPUT );
  pinMode(PT2248->DATA_INPUT_PIN[0], INPUT  );
  pinMode(PT2248->DATA_INPUT_PIN[1], INPUT  );
  pinMode(PT2248->DATA_INPUT_PIN[2], INPUT  );
  pinMode(PT2248->DATA_INPUT_PIN[3], INPUT  );

}

void sendBit(st_pt2248 *PT2248, uint16_t PT2248_BIT){
    switch (PT2248_BIT) {
        case PT2248_BIT_0: // Bit 0: 1 LOW -> 3 HIGH
            digitalWrite(PT2248->DATA_OUT_PIN, 0);
            delayMicroseconds(PT2248_OSC_CLOCK_PERIOD);
            digitalWrite(PT2248->DATA_OUT_PIN, 1);
            delayMicroseconds(PT2248_CLK_PERIOD_3);
            break;
        case PT2248_BIT_1: // Bit 1: 3 LOW -> 1 HIGH
            digitalWrite(PT2248->DATA_OUT_PIN, 0);
            delayMicroseconds(PT2248_CLK_PERIOD_3);
            digitalWrite(PT2248->DATA_OUT_PIN, 1);
            delayMicroseconds(PT2248_OSC_CLOCK_PERIOD);
            break;
        default:
            //digitalWrite(PT2248->DATA_OUT_PIN, 0);
        break;
    }
}

void single_short(st_pt2248 *PT2248, uint16_t dataCode){
    // 2 Command words
    delayMicroseconds(PT2248_CLK_PERIOD_60);

    //Command code
    for(uint8_t i=0; i<12; i++){
            uint8_t bitValue = (dataCode >> i) & 0x001;
            sendBit(PT2248, bitValue);
        }
    delayMicroseconds(PT2248_CLK_PERIOD_80);
}

void getState(st_pt2248 *PT2248){
    PT2248->DATA_STATE = 0x000;
    
     if( digitalRead(PT2248->DATA_INPUT_PIN[0]) != 0 )
       PT2248->DATA_STATE = 0b100010100000  ;    //key 7
     if( digitalRead(PT2248->DATA_INPUT_PIN[1]) != 0 )
       PT2248->DATA_STATE = 0b100010010000  ;    //key 8
     if( digitalRead(PT2248->DATA_INPUT_PIN[2]) != 0 )
       PT2248->DATA_STATE = 0b100010001000  ;    //key 9
     if( digitalRead(PT2248->DATA_INPUT_PIN[3]) != 0 )
       PT2248->DATA_STATE = 0b100010000100  ;    //key 10
}