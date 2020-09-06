int pin5 = 5;
int pin6 = 6;
int pin8 = 8;
int pin9 = 9;
int state = 0;

int pinOut = 10;

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

void setup() {
  // put your setup code here, to run once:
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin8, INPUT);
  pinMode(pin9, INPUT);

  Serial.begin(9600);

  pinMode(pinOut, OUTPUT);
  
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
 //Serial.println(average);
  delay(1);
  return average;
}
void loop() {
  

  // this is positive
  if(digitalRead(pin8) == HIGH)
  {
    if (state != pin8) {
      state = pin8;
      Serial.println("Turning Pin 8 on");
      digitalWrite(pin5, HIGH);
      digitalWrite(pin6, LOW);
    }
  }

  // this is negative
  if(digitalRead(pin9) == HIGH)
  {
    if (state != pin9) {
      state = pin9;
      Serial.println("Turning Pin 9 on");
      digitalWrite(pin5, LOW);
      digitalWrite(pin6, HIGH); 
    }
  }

  int reading = getReading();
  Serial.println(reading);
  delay(100);
    
  // so if we have a reading of less than 100, we want to stop the motor as we are
  // at the highest tension and dont want to damage the motor or cable
  //if (reading < 100) {
    
//  }
}
