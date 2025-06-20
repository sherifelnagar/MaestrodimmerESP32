/*
* example is for "DL_16A" Dimmer Low With maximum Power "3000 Watt"
* the maximum Percentatge is 80 to maximum volt ac load (220 volt AC) & the minimum Percentatge is 0 to minimum volt ac load(0 volt AC)

* example with two push button up and down control Percentatge of dimmer. 

   ESP32 Connection to DL_16A and two push button  :
   ---------------------------
   DL_16A Pin | ESP32 Pin
   ---------------------------
   DIM        | GPIO 25
   ZC         | GPIO 26
   VCC        | 3.3V
   GND        | GND


   Push Button (PULLUP Configuration) | ESP32 Pin
   ------------------------------------------
   UP Button  (Pull-up)               | GPIO 15
   DOWN Button (Pull-up)              | GPIO 4

*/


#include <MaestroRBDdimmer.h>

#define DIM  25
#define ZC  26

#define Up_Button 15
#define Down_Button 4

int PerCentatge = 0;

dimmerLamp dimmer(DIM, ZC);

void setup() {
  Serial.begin(9600);
  
  pinMode(Down_Button, INPUT_PULLUP);
  pinMode(Up_Button, INPUT_PULLUP);
  
  dimmer.toggleSettings(0, 100);
  dimmer.begin(NORMAL_MODE, ON);
  
  Serial.println("Dimmer Program is starting...");
  Serial.println("Set value");
}

void loop() {
  /*dimmer button*/
  int sensorValUP = digitalRead(Up_Button);
  int sensorValDOWN = digitalRead(Down_Button);
  /*dimmer up*/
  if (sensorValUP == LOW) {
    PerCentatge = PerCentatge + 5 ;
    if (PerCentatge >= 80)
    {
      PerCentatge = 80;
    }
    dimmer.setPower(PerCentatge);
    Serial.println(PerCentatge);
    delay(100);
  }
  /*dimmer down*/
  if (sensorValDOWN == LOW) {
    PerCentatge = PerCentatge - 5;
    if (PerCentatge <= 0)
    {
      PerCentatge = 0;
    }
    dimmer.setPower(PerCentatge);
    Serial.println(PerCentatge);
    delay(100);
  }
}
