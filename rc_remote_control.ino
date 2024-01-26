/*   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG  

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "MyESP"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 87 bytes
  { 255,4,0,0,0,80,0,16,31,1,1,0,26,41,12,12,2,31,32,226,
  134,145,32,0,1,0,14,57,12,12,2,31,226,134,144,0,1,0,38,57,
  12,12,2,31,226,134,146,0,1,0,26,73,12,12,2,31,32,226,134,147,
  32,0,129,0,9,7,47,6,2,82,101,109,111,116,101,32,67,111,110,116,
  114,111,108,108,101,114,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t up; // =1 if button pressed, else =0 
  uint8_t left; // =1 if button pressed, else =0 
  uint8_t right; // =1 if button pressed, else =0 
  uint8_t down; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#define RIGHT_MOTORS_POWER 14 
#define RIGHT_MOTORS_GROUND 27 
#define LEFT_MOTORS_POWER 26 
#define LEFT_MOTORS_GROUND 25 


void setup() 
{
  Serial.begin(115200);
  RemoteXY_Init(); 

  // Setup pins
  pinMode(RIGHT_MOTORS_POWER, OUTPUT);
  pinMode(RIGHT_MOTORS_GROUND, OUTPUT);
  pinMode(LEFT_MOTORS_POWER, OUTPUT);
  pinMode(LEFT_MOTORS_GROUND, OUTPUT);

}

void loop() 
{ 
  RemoteXY_Handler ();
  
  // TODO you loop code
  if (RemoteXY.up == 1){
    drive_forward();
  } else if (RemoteXY.down == 1) {
    drive_backward();
  } else if (RemoteXY.left == 1) {
    turn_left();
  } else if (RemoteXY.right == 1) {
    turn_right();
  } else {
    stop();
  }

}


void drive_forward() {
    digitalWrite(RIGHT_MOTORS_POWER,HIGH);
    digitalWrite(RIGHT_MOTORS_GROUND,LOW);

    digitalWrite(LEFT_MOTORS_POWER,HIGH);
    digitalWrite(LEFT_MOTORS_GROUND,LOW);
}

void drive_backward() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,HIGH);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,HIGH);
}

void turn_right() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,HIGH);

    digitalWrite(LEFT_MOTORS_POWER,HIGH);
    digitalWrite(LEFT_MOTORS_GROUND,LOW);
}

void turn_left() {
    digitalWrite(RIGHT_MOTORS_POWER,HIGH);
    digitalWrite(RIGHT_MOTORS_GROUND,LOW);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,HIGH);
}

void stop(){
    digitalWrite(RIGHT_MOTORS_POWER, LOW);
    digitalWrite(RIGHT_MOTORS_GROUND, LOW);

    digitalWrite(LEFT_MOTORS_POWER, LOW);
    digitalWrite(LEFT_MOTORS_GROUND, LOW);
}


