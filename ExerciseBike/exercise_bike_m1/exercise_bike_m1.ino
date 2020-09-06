int pin5 = 5;
int pin6 = 6;
int pin8 = 8;
int pin9 = 9;

int pin8State = HIGH;
int pin9State = HIGH;
int read8 = HIGH;
int read9 = HIGH;

void setup() {
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  read8 = digitalRead(pin8);
  read9 = digitalRead(pin9);
  
  if(read9 == LOW && pin9State != LOW) {
    pin9State = LOW;
    Serial.println("Turning Pin 9 on");
    digitalWrite(pin5, HIGH);
    digitalWrite(pin6, LOW);
  } else if(read9 == HIGH && pin9State == LOW) {
    pin9State = HIGH;
    Serial.println("Turning Pin 9 off");
    digitalWrite(pin5, LOW);
    digitalWrite(pin6, LOW); 
  }
  
  if(read8 == LOW && pin8State != LOW) {
    pin8State = LOW;
    Serial.println("Turning Pin 8 on");
    digitalWrite(pin5, LOW);
    digitalWrite(pin6, HIGH); 
  } else if(read8 == HIGH && pin8State == LOW) {
    pin8State = HIGH;
    Serial.println("Turning Pin 8 off");
    digitalWrite(pin5, LOW);
    digitalWrite(pin6, LOW); 
  }
}
