#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(9, 2);

#define pin1 3
#define pin2 4
#define pin3 5
#define pin4 6
#define pin5 7
#define pin6 8

#define pin8 10
#define pin9 11
#define pin10 12
#define pin11 13

char data;
int value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() > 0){
    data = bluetooth.read();
    Serial.println(data);
    if (data == 'n'){
      for (int i = 3; i <= 13; i++){
        if (i != 9){
          digitalWrite(i, LOW);
        }
      }
    }
    else if (data == 'y'){
      for (int i = 3; i <= 13; i++){
        if (i != 9){
          digitalWrite(i, HIGH);
        }
      }
    }
    else{
      num(data);
      Serial.println(value);
      on(value);
    }
  }
}

void num(char data){
  if (data == '1')
      value = 3;
  if (data == '2')
      value = 4;
  if (data == '3')
      value = 5;
  if (data == '4')
      value = 6;
  if (data == '5')
      value = 7;
  if (data == '6')
      value = 8;
  
  if (data == '7')
      value = 10;
  if (data == '8')
      value = 11;
  if (data == 'a')
      value = 12;
  if (data == 'b')
      value = 13;
}

void on(int value){
  for (int i = 3; i <= 13; i++){
    if ((i == value) && (i != 9)){
      digitalWrite(value, HIGH);
      Serial.print("Bat den: ");
      Serial.println(i);
    }
    else if ((i != value) && (i != 9)){
      digitalWrite(i, LOW);
      Serial.print("Tat den: ");
      Serial.println(i);
    }
  }
}
