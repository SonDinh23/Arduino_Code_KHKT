#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

SoftwareSerial DF(3, 2);
DFRobotDFPlayerMini myDFPlayer;

int button = 4;
int relay = 5;
int speakerTX = 2;
int speakerRX = 3;
int buttonStatus = 0;
unsigned long timeCountUse = 0; //Dem thoi gian nguoi dung su dung goi

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  DF.begin(9600);
  if (!myDFPlayer.begin(DF, true, false))
    while (true)
      delay(0);
  myDFPlayer.volume(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStatus = digitalRead(button);
  digitalWrite(relay, LOW);
  if (buttonStatus == 0) {
    digitalWrite(relay, HIGH);
    for (int i; i <= 60; i++) {
      if (buttonStatus == HIGH) {
        digitalWrite(relay, LOW);
        break;
      }
      else {
        digitalWrite(relay, HIGH);
        delay(200);
        continue;
      }
      digitalWrite(relay, LOW);
      buttonStatus = digitalRead(button);
    }
    
    for (int i; i <= 60; i++) {
      if (buttonStatus == HIGH) {
        speakerPause();
        break;
      }
      else {
        speakerStart();
        delay(60000);
        continue;
      }
      digitalWrite(relay, LOW);
      buttonStatus = digitalRead(button);
    }
    buttonStatus = digitalRead(button);
  }

  if (buttonStatus == 1){
    digitalWrite(relay, LOW);
    speakerPause();
  }
}

void speakerStart() {
  myDFPlayer.randomAll();
}

void speakerPause(){
  myDFPlayer.pause();
}
