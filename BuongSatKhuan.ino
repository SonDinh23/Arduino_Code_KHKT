int motor = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: HIGH = tắt; LOW = bật
  digitalWrite(motor, HIGH);
  Serial.println("Ổn định vị trí");
  delay(5000);
  
  digitalWrite(motor, LOW);
  Serial.println("Lồng quay");
  Serial.println("Bật máy bơm");
  delay(10000);
  
  digitalWrite(motor, HIGH);
  Serial.println("Tắt máy bơm");
  Serial.println("Tắt motor");
  delay(120000);
  Serial.println();
}
