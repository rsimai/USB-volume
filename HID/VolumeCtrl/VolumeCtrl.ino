//USB Rotary Volume Control
//using atmega32u4


#include "HID-Project.h"    //MIT
#include <SimpleEncoder.h>  //MIT

//Mega Minidings
//const int BTN = 9;   // D9 - SW
//const int encB = 10; //D10 - DT
//const int encA = 11; //D11 - CLK
//const int LED = LED_BUILTIN;

//Mega Normal
const int BTN = 9;   // D9 - SW
const int encB = 8;  //D10 - DT
const int encA = 7;  //D11 - CLK
//const int LED = 17;

SimpleEncoder encoder(BTN, encA, encB);

void setup() {
  //pinMode(LED, OUTPUT);
  Consumer.begin();
  BootKeyboard.begin();
}

void loop() {
  if (encoder.CLOCKWISE) {
     Consumer.write(MEDIA_VOL_UP);
  }
   if (encoder.COUNTERCLOCKWISE) {
     Consumer.write(MEDIA_VOL_DOWN);
  }
  if (encoder.BUTTON_PRESSED) {
     Consumer.write(MEDIA_VOL_MUTE);
     while (encoder.buttonPressed()) {
        //digitalWrite(LED, HIGH);
        delay(100);
     }
     //digitalWrite(LED, LOW);
  }
}
