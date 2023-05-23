// include Servo library
#include <Servo.h>

// Horizontal servo
Servo horizontal;
int servoh = 90;

int servohLimitHigh = 165;
int servohLimitLow = 15;


// Vertical servo
Servo vertical;
int servov = 90;

int servovLimitHigh = 165;
int servovLimitLow = 15;


// LDR pin connections
int ldrTR = 0; // LDR top right   bread 7 green
int ldrTL = 1; // LDR top left    bread 5 red
int ldrBR = 2; // LDR bottom right bread 6 blue 
int ldrBL = 3; // LDR bottom left  bread 4 blue


void setup() {
  Serial.begin(9600);
  // servo connections
  horizontal.attach(9);
  vertical.attach(10);
  // move servos
  horizontal.write(90);
  vertical.write(90);
  delay(3000);
}


void loop() {
  bool update_horizontal = false;
  bool update_vertical = false;

  int tr = analogRead(ldrTR); // top right
  int tl = analogRead(ldrTL); // top left
  int br = analogRead(ldrBR); // bottom right
  int bl = analogRead(ldrBL); // bottom left

  int dtime = 5; // change for debugging only
  int tol = 30;

  int avt = (tl + tr) / 2; // average value top
  int avd = (bl + br) / 2; // average value bottom
  int avl = (tl + bl) / 2; // average value left
  int avr = (tr + br) / 2; // average value right

  int dvert = avt - avd;  // check the difference of up and down
  int dhoriz = avl - avr; // check the difference of left and right


  // send data to the serial monitor if desired
  Serial.println(dhoriz);
  Serial.print(" ");
 

  // check if the difference is in the tolerance else change vertical angle
 
  if (-1 * tol > dvert || dvert > tol) {
    if (avt > avd) {
      servov = ++servov;
      if (servov > servovLimitHigh) {
        servov = servovLimitHigh;
      }
    }
    else if (avt < avd) {
      servov = --servov;
      if (servov < servovLimitLow) {
        servov = servovLimitLow;
      }
    }
    else if (avt = avd) {
      // nothing
    }
    update_vertical = true;
  }

  // check if the difference is in the tolerance else change horizontal angle
  if (-1 * tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
      servoh = ++servoh;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    }
    else if (avl < avr) {
      servoh = --servoh;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    }
    else if (avl = avr) {
      // nothing
    }
    update_horizontal = true;
  }
  

  if (update_vertical) {
    vertical.write(servov);
  }
  if (update_horizontal) {
    horizontal.write(servoh);
  }

  delay(dtime);
  
}
