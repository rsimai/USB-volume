// rsimai 2023-11-24
// volume control via USB keyboard

#include <Arduino.h>
#include <RotaryEncoder.h>
#include "HID-Project.h"

#define PIN_IN1 8 // DT
#define PIN_IN2 7 // CLK
#define PIN_SW 9  // button, low active

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int dir;
int buttonState = 0;

void setup()
{
  pinMode(PIN_SW, INPUT);
  Consumer.begin();
  BootKeyboard.begin();
} 

void loop()
{
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  buttonState = digitalRead(PIN_SW);
  
  if ((pos - newPos >= 2) || (newPos - pos >=2)) { // does 2 ticks between positions 
    dir = (int)(encoder.getDirection());
    pos = newPos;
    if (dir == 1){                       // turned right
      Consumer.write(MEDIA_VOL_UP);
    }
    if (dir == -1){                      // turned left
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }
  if ( digitalRead(PIN_SW) == LOW){      // button pressed?
    Consumer.write(MEDIA_VOL_MUTE);
    while ( digitalRead(PIN_SW) == LOW){ // block
      delay(100);
    }
  }
} 
