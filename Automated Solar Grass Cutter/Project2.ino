/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
#include <string.h>
// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Alpha"
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =  // 64 bytes
  { 255, 26, 0, 0, 0, 57, 0, 16, 31, 0, 5, 0, 65, 12, 43, 43, 2, 26, 31, 3,
    3, 250, 16, 12, 32, 2, 26, 2, 0, 23, 9, 27, 13, 2, 26, 31, 31, 79, 78, 0,
    79, 70, 70, 0, 7, 36, 23, 32, 27, 6, 2, 26, 2, 11, 7, 36, 23, 42, 27, 6,
    2, 26, 2, 11 };

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  int8_t joystick_1_x;   // from -100 to 100
  int8_t joystick_1_y;   // from -100 to 100
  uint8_t mode;          // =0 if select position A, =1 if position B, =2 if position C, ...
  uint8_t Cutting;       // =1 if switch ON and =0 if OFF
  char X_direction[11];  // string UTF8 end zero
  char Y_direction[11];  // string UTF8 end zero

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define up_r_p 12
#define up_r_n 11

#define up_l_p 9
#define up_l_n 10

#define down_r_p A0
#define down_r_n A1

#define down_l_p A3
#define down_l_n A2

#define echo_f 8
#define trig_f 7

#define echo_r 6
#define trig_r 5

#define echo_l 4
#define trig_l 3

#define cutting 2

int x_direction = 0;
int y_direction = 0;

void setup() {
  RemoteXY_Init();

  pinMode(up_r_p, OUTPUT);
  pinMode(up_r_n, OUTPUT);

  pinMode(up_l_p, OUTPUT);
  pinMode(up_l_n, OUTPUT);

  pinMode(down_r_p, OUTPUT);
  pinMode(down_r_n, OUTPUT);

  pinMode(down_l_p, OUTPUT);
  pinMode(down_l_n, OUTPUT);

  pinMode(trig_f, OUTPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(trig_l, OUTPUT);

  pinMode(echo_f, INPUT);
  pinMode(echo_r, INPUT);
  pinMode(echo_l, INPUT);

  pinMode(cutting, OUTPUT);
  digitalWrite(cutting, 1);
}


int checker = 0;

void loop() {
  RemoteXY_Handler();

  x_direction = atoi(RemoteXY.X_direction);
  y_direction = atoi(RemoteXY.Y_direction);
  if (RemoteXY.mode == 0) {  // manual mode
    if (RemoteXY.Cutting == 1) {
      digitalWrite(cutting, 0);
    } else {
      digitalWrite(cutting, 1);
    }
    if (RemoteXY.joystick_1_x >= 80 && RemoteXY.joystick_1_x <= 100) {
      go_right();
    } else if (RemoteXY.joystick_1_x >= -100 && RemoteXY.joystick_1_x <= -80) {
      go_left();
    } else if (RemoteXY.joystick_1_y >= 80 && RemoteXY.joystick_1_y <= 100) {
      go_forward();
    } else if (RemoteXY.joystick_1_y >= -100 && RemoteXY.joystick_1_y <= -80) {
      go_backward();
    } else {
      stop();
    }
  } else if (RemoteXY.mode == 1) {  // automatic mode
    get_ultrasonic_value();
  } else if (RemoteXY.mode == 2) {  // area mode

    digitalWrite(cutting, 0);
    RemoteXY.Cutting = 1;

    if (RemoteXY.mode == 2) {
      area_cut(x_direction, y_direction);
      RemoteXY.mode = 0;
    } else {
    }
  } else {
  }
}

void go_forward(void) {
  digitalWrite(up_r_p, HIGH);
  analogWrite(up_l_p, 210);
  digitalWrite(down_r_p, HIGH);
  digitalWrite(down_l_p, HIGH);

  digitalWrite(up_r_n, LOW);
  digitalWrite(up_l_n, LOW);
  digitalWrite(down_r_n, LOW);
  digitalWrite(down_l_n, LOW);
}

void go_right(void) {
  digitalWrite(up_r_p, LOW);
  digitalWrite(up_l_p, HIGH);
  digitalWrite(down_r_p, LOW);
  digitalWrite(down_l_p, HIGH);

  digitalWrite(up_r_n, HIGH);
  digitalWrite(up_l_n, LOW);
  digitalWrite(down_r_n, HIGH);
  digitalWrite(down_l_n, LOW);
}

void go_left(void) {
  digitalWrite(up_r_p, HIGH);
  digitalWrite(up_l_p, LOW);
  digitalWrite(down_r_p, HIGH);
  digitalWrite(down_l_p, LOW);

  digitalWrite(up_r_n, LOW);
  digitalWrite(up_l_n, HIGH);
  digitalWrite(down_r_n, LOW);
  digitalWrite(down_l_n, HIGH);
}

void go_backward(void) {
  digitalWrite(up_r_p, LOW);
  digitalWrite(up_l_p, LOW);
  digitalWrite(down_r_p, LOW);
  digitalWrite(down_l_p, LOW);

  digitalWrite(up_r_n, HIGH);
  digitalWrite(up_l_n, HIGH);
  digitalWrite(down_r_n, HIGH);
  digitalWrite(down_l_n, HIGH);
}

void stop(void) {
  digitalWrite(up_r_p, LOW);
  digitalWrite(up_l_p, LOW);
  digitalWrite(down_r_p, LOW);
  digitalWrite(down_l_p, LOW);

  digitalWrite(up_r_n, LOW);
  digitalWrite(up_l_n, LOW);
  digitalWrite(down_r_n, LOW);
  digitalWrite(down_l_n, LOW);
}

void area_cut(int x, int y) {
  digitalWrite(cutting, LOW);
  float dist = y / 32;
  int tryes = x / 30;
  if (y % 30) {
    tryes += 1;
  } else {
  }
  int dir_counter = 0;

  for (int i = 0; i < tryes; i++) {
    if (i == 0) {
      go_forward();
      delay((dist * 1000));
      stop();
      if (dir_counter % 2 == 0) {
        go_right();
        check_cut();
        delay(2180);
        go_forward();
        check_cut();
        delay(650);
        go_right();
        check_cut();
        delay(2180);
        dir_counter++;
      } else if (dir_counter % 2 == 1) {
        go_left();
        check_cut();
        delay(2350);
        go_forward();
        check_cut();
        delay(650);
        go_left();
        check_cut();
        delay(2350);
        dir_counter++;
      } else {
      }
    } else {
      go_forward();
      delay(((dist * 1000) - 500));
      stop();
      if (dir_counter % 2 == 0) {
        go_right();
        check_cut();
        delay(2180);
        go_forward();
        check_cut();
        delay(650);
        go_right();
        check_cut();
        delay(2180);
        dir_counter++;
      } else if (dir_counter % 2 == 1) {
        go_left();
        check_cut();
        delay(2350);
        go_forward();
        check_cut();
        delay(650);
        go_left();
        check_cut();
        delay(2350);
        dir_counter++;
      } else {
      }
    }
  }
  digitalWrite(cutting, HIGH);
}
void check_cut(void) {
  if (RemoteXY.Cutting == 1) {
    digitalWrite(cutting, 0);
  } else {
    digitalWrite(cutting, 1);
  }
}

void get_ultrasonic_value(void) {
  go_forward();
  digitalWrite(trig_f, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_f, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_f, LOW);
  int Dist_f = (pulseIn(echo_f, HIGH)) / 57;
  delay(10);
  check_cut();
  if (Dist_f <= 25) {
    if ((checker % 2) == 0) {
      go_right();
      check_cut();
      delay(2180);
      go_forward();
      check_cut();
      delay(650);
      go_right();
      check_cut();
      delay(2180);
      checker++;
    } else if ((checker % 2) == 1) {
      go_left();
      check_cut();
      delay(2350);
      go_forward();
      check_cut();
      delay(650);
      go_left();
      check_cut();
      delay(2350);
      checker++;
    }
}
}