int motor = 3;
int fan = 2;
int i;
int pir = 8;
int pirValue = 0;

boolean sensorStatus = false;

void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(pir, INPUT);
}

void loop() {  
  pirValue = digitalRead(pir);
  if (pirValue == HIGH){
    sensorStatus = true;
    digitalWrite(motor, HIGH);
    for (i = 0; i <= 200; i++){
      if (pirValue == LOW){
        digitalWrite(motor, LOW);
        sensorStatus = false;
        break;
      }
      delay(10);
    }
    digitalWrite(motor, LOW);
    if(sensorStatus==true){
      delay(2000);
    }
  }
  
  while(pirValue == HIGH && sensorStatus == true){
    pirValue = digitalRead(pir);
    digitalWrite(fan, HIGH);
  }
  digitalWrite(fan, LOW);
  sensorStatus = false;
}
