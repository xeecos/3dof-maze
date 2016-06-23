#include "MeMegaPi.h"

MeMegaPiDCMotor motors[3] = {MeMegaPiDCMotor(PORT2A),MeMegaPiDCMotor(PORT1B),MeMegaPiDCMotor(PORT1A)};
MeRGBLed led;
int limit_pins[6] = {A10,A11,A12,A13,A14,A15};
int motion_pins[3] = {A7,A8,A9};
int read_motions[3] = {0,0,0};
float j, f, k;
void setup(){
  
  Serial.begin(115200);
  led.setpin(A6);
  int i;
  for(i=0;i<3;i++){
    pinMode(limit_pins[i*2],INPUT_PULLUP);
    pinMode(limit_pins[i*2+1],INPUT_PULLUP);
    pinMode(motion_pins[i],INPUT);
    motors[i].stop();
  }
}
void loop(){
  int i;
  float spd = 0;
  for(i=0;i<3;i++){
    read_motions[i] = (analogRead(motion_pins[i])-480)/6;
    read_motions[i] = abs(read_motions[i])<20?0:read_motions[i];
    /*Serial.print(read_motions[i]);
    Serial.print(" ");
    Serial.print(digitalRead(limit_pins[i*2]));
    Serial.print(" ");
    Serial.print(digitalRead(limit_pins[i*2+1]));
    Serial.print(" ");*/
    spd+=abs(read_motions[i]);
    if(digitalRead(limit_pins[i*2])==0){
      if(read_motions[i]<0){
        read_motions[i] = 0;
      }
    }
    if(digitalRead(limit_pins[i*2+1])==0){
      if(read_motions[i]>0){
        read_motions[i] = 0;
      }
    }
    motors[i].run(read_motions[i]);
  }
//  Serial.println();
//  delay(500);
    color_loop(spd/8);
}
void color_loop(float spd)
{
  for(uint8_t t = 1; t < 15; t++)
  {
    uint8_t red  = spd * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = spd * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = spd * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    led.setColorAt(t, red, green, blue);
  }
  led.show();
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

