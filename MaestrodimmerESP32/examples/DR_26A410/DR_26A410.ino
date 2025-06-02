/*
* example is for "DR_26A410" Dimmer Relay With maximum Power " 5000 Watt ",  With four Relay With maximum Current (10 amper)
* the maximum Percentatge is 80 to maximum volt ac load (220 volt AC) & the minimum Percentatge is 0 to minimum volt ac load(0 volt AC)

* example with two push button up and down control Percentatge of dimmer and four push button to change the relays states

   ESP32 Connection to DR_26A410 and two push button up & down Dimmer and four push button control four ralay states  :
   ---------------------------
   DR_26A410 Pin | ESP32 Pin
   ---------------------------
   SC            | GPIO 25
   G             | GND
   ZC            | GPIO 26
   

   G             | GND
   VCC           | 3.3v
   CH1           | GPIO 13
   CH2           | GPIO 12
   CH3           | GPIO 14
   CH4           | GPIO 27

   Push Button (PULLUP Configuration) | ESP32 Pin
   ------------------------------------------
   UP Button  (Pull-up)               | GPIO 15
   DOWN Button (Pull-up)              | GPIO 4
   Relay one Button  (Pull-up)        | GPIO 16
   Relay two Button  (Pull-up)        | GPIO 17
   Relay three Button  (Pull-up       | GPIO 5
   Relay four Button  (Pull-up)       | GPIO 18
*/
#include <MaestroRBDdimmer.h>

#define SC  25
#define ZC  26

#define Up_Button 15
#define Down_Button 4

#define Relay_1_Button 16
#define Relay_2_Button 17
#define Relay_3_Button 5
#define Relay_4_Button 18

#define Relay_1_Output 13
#define Relay_2_Output 12
#define Relay_3_Output 14
#define Relay_4_Output 27

int PerCentatge = 0;
int Relay_One = false;
int Relay_Two = false;
int Relay_Three = false;
int Relay_Four = false;

dimmerLamp dimmer(SC, ZC);

void setup() {
  Serial.begin(9600);
  
  pinMode(Down_Button, INPUT_PULLUP);
  pinMode(Up_Button, INPUT_PULLUP);

  pinMode(Relay_1_Button, INPUT_PULLUP);
  pinMode(Relay_2_Button, INPUT_PULLUP);
  pinMode(Relay_3_Button, INPUT_PULLUP);
  pinMode(Relay_4_Button, INPUT_PULLUP);

  pinMode(Relay_1_Output, OUTPUT);
  pinMode(Relay_2_Output, OUTPUT);
  pinMode(Relay_3_Output, OUTPUT);
  pinMode(Relay_4_Output, OUTPUT);
  digitalWrite(Relay_1_Output,LOW);
  digitalWrite(Relay_2_Output,LOW);
  digitalWrite(Relay_3_Output,LOW);
  digitalWrite(Relay_4_Output,LOW);
  
  dimmer.toggleSettings(0, 100);
  dimmer.begin(NORMAL_MODE, ON);
  
  Serial.println("Dimmer Program is starting...");
  Serial.println("Set value");
}

void loop() {
  /*dimmer button*/
  int sensorValUP = digitalRead(Up_Button);
  int sensorValDOWN = digitalRead(Down_Button);
  /*relay button*/
  int Relay_One_value = digitalRead(Relay_1_Button);
  int Relay_Two_value = digitalRead(Relay_2_Button);
  int Relay_Three_value = digitalRead(Relay_3_Button);
  int Relay_Four_value = digitalRead(Relay_4_Button);
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
  /*relay one*/
  if (Relay_One_value == LOW) {
    Relay_One = !Relay_One;
    digitalWrite(Relay_1_Output,Relay_One);
    delay(100);
  }
  /*relay two*/
  if (Relay_Two_value == LOW) {
     Relay_Two = !Relay_Two;
    digitalWrite(Relay_2_Output,Relay_Two);
    delay(100);
  }
  /*relay three*/
  if (Relay_Three_value == LOW) {
     Relay_Three = !Relay_Three;
    digitalWrite(Relay_3_Output,Relay_Three);
    delay(100);
  }
  /*relay four*/
  if (Relay_Four_value == LOW) {
     Relay_Four = !Relay_Four;
    digitalWrite(Relay_4_Output,Relay_Four);
    delay(100);
  }
}
