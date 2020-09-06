/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

int pinOut = 10;
int pin5 = 5;
int pin6 = 6;
int pin8 = 8;
int pin9 = 9;

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;

int pin8State = HIGH;
int pin9State = HIGH;
int read8 = HIGH;
int read9 = HIGH;

void setup() {
  pinMode(pinOut, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  
  // initialize serial communication with computer:
  Serial.begin(9600);
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

int getReading() {
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  // send it to the computer as ASCII digits
  return average;
}

int getFinalReading() {
  int reading = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    reading = getReading();
    delay(100);
  }
  return reading;
}

void alterMotorDirection() {
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

// the loop routine runs over and over again forever:
void loop() {
  int reading = getFinalReading();
  Serial.println(reading);

  alterMotorDirection();

}
