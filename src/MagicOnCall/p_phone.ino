/*
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

FlashLED flashLed(5);

int mode = 0;
void Gamepad_check() {
    //Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("Up");
//   flashLed3.activate();
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("Down");
//    flashLed4.activate();
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    mode = 1;
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    mode = 0;
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    mode = 2;
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    mode = 3;
  }
  
  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
    flashLed.activate();
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
//    flashLed2.activate();
  }

    switch (mode) {
    case 0:     
      flashLed.strobe(); 
//      flashLed2.check(); 
//      flashLed3.strobe(); 
//      flashLed4.check(); 
      break;
    case 1:    // Ultra-sonic Distance
      flashLed.check(); 
//      flashLed2.strobe(); 
//      flashLed3.check(); 
//      flashLed4.strobe(); 
      break;
    case 2:     
      flashLed.check(); 
//      flashLed2.strobe(); 
//      flashLed4.check(); 
//      flashLed3.strobe(); 
      break;
    }

}

*/
