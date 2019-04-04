int led = 13;
int sensor = 10;
int state = LOW;
int val = 0;

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(6, 7, 8);

#define buz 2
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(buz, OUTPUT);
  pinMode(sensor, INPUT);    // initialize sensor as an input
  
  Serial.begin(9600);
  
//  myRTC.setDS1302Time(00, 30, 22, 2, 04, 12, 2018); //Set Tanggal

  lcd.begin(16, 2);
  
}
void loop() 
{  
    myRTC.updateTime();
    
  lcd.setCursor (0, 1);
  lcd.print("DATE: ");                                                                  
  lcd.print(myRTC.dayofmonth);                                                                         
  lcd.print("/");                                                                                      
  lcd.print(myRTC.month);                                                                              
  lcd.print("/");                                                                                     
  lcd.print(myRTC.year);                                                                              
  
  
  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  lcd.print(myRTC.hours);                                                                              
  lcd.print(":");                                                                                     
  lcd.print(myRTC.minutes);                                                                            
  lcd.print(":");                                                                                      
  lcd.println(myRTC.seconds);
  
  
  
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    if( myRTC.hours == 23 & myRTC.minutes >= 25 & myRTC.seconds >= 30){
      digitalWrite(led, HIGH);   // turn LED ON
      digitalWrite(buz,LOW);
    }
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      digitalWrite(buz, HIGH);
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
      }
    }
  
  
}


