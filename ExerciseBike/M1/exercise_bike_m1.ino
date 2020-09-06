int pin5 = 5;
int pin6 = 6;
int pin8 = 8;
int pin9 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // this is positive
  if(digitalRead(pin9) == LOW) {
    Serial.println("Turning Pin 9 on");
    digitalWrite(pin5, HIGH);
    digitalWrite(pin6, LOW);
  } else if(digitalRead(pin8) == LOW) {
    Serial.println("Turning Pin 8 on");
    digitalWrite(pin5, LOW);
    digitalWrite(pin6, HIGH); 
  } else {
    Serial.println("Turning Pin 8 and 9 off");
    digitalWrite(pin5, LOW);
    digitalWrite(pin6, LOW); 
  }
}
