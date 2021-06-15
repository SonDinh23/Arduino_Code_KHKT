#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mydfplayer(3, 2); // RX, TX
DFRobotDFPlayerMini dfplayer;

byte rfPin = 4;
float distance = 0;
byte Rtrig = 10;
byte Recho = 9;
byte Mtrig = 8;
byte Mecho = 7;
byte Ltrig = 6;
byte Lecho = 5;
float mid = 0;
float left = 0;
float right = 0;
int count = 0;
byte button = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(Ltrig, OUTPUT);
  pinMode(Lecho, INPUT);
  pinMode(Mtrig, OUTPUT);
  pinMode(Mecho, INPUT);
  pinMode(Rtrig, OUTPUT);
  pinMode(Recho, INPUT);

  pinMode(button, INPUT_PULLUP);

  Serial.begin(9600);

  mydfplayer.begin(9600);
  mydfplayer.listen();
  if (!dfplayer.begin(mydfplayer, true, false)) {
    while (true) {
      delay(0);
    }
  }
  dfplayer.volume(40);
  nhac_mo_dau();
}

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonicSS(Ltrig, Lecho);
  left = distance;
  ultrasonicSS(Mtrig, Mecho);
  mid = distance;
  ultrasonicSS(Rtrig, Recho);
  right = distance;

  Serial.println(left);
  Serial.println(mid);
  Serial.println(right);
  Serial.println();

  int v = digitalRead(button);
  Serial.print("Button status: ");
  Serial.println(v);

  if (v == 0) {
    if (distance >= 100 && distance <= 130) {
      dfplayer.play(28);
      delay(3000);
    }
    if (mid >= 5 && mid <= 40) {
      dfplayer.play(28);
      delay(3000);
    }
  }

  byte result = digitalRead(rfPin);
  while (result == 1) {
    dfplayer.play(26);
    delay(3000);
    Serial.println("RFSignalFound");
    result = digitalRead(rfPin);
  }

  if (v == 1) {
    if (mid <= 30 && count == 0) {
      Serial.println("Object detected!");
      dfplayer.play(26);
      count++;
    }
    else if (mid > 30 && count > 0) {
      count = 0;
    }
  }
}

void nhac_mo_dau() {
  dfplayer.play(27);
  delay(3000);
}

void ultrasonicSS(byte trig, byte echo) {
  unsigned long duration; // biến đo thời gia

  digitalWrite(trig, 0);  // tắt chân tri
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân tri
  delayMicroseconds(5);   // xung có độ dài 5 microSecond
  digitalWrite(trig, 0);  // tắt chân tri

  duration = pulseIn(echo, HIGH);
  distance = duration / 2 / 29.412;

  delay(200);
}
