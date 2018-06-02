/*
  Bicycle Cinema Arduino Code
  Reads the voltage of the ultracaps via A0 connected to Voltage divider
  Turns on projector via Relay when voltage > 12V
  Turns off Projector when voltage  < 7V


*/

#define NUM_READINGS 10

int relay = 2;

int sensorValue;
int prevValue = 0;

int readings[NUM_READINGS];
int index = 0;
long average = 0;
long total = 0;

bool relay_on = false;



// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);


  // initialize the digital pin as an output.
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);
  relay_on = false;

  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }

}

void readVoltage() {
  //sensorValue = analogRead(A0);

  total = total - readings[index];
  // read from the sensor:
  readings[index] = analogRead(A0);
  // add the reading to the total:
  total = total + readings[index];
  // advance to the next position in the array:
  index++;

  // if we're at the end of the array...
  if (index >= NUM_READINGS) {
    // ...wrap around to the beginning:
    index = 0;
  }

  average = total / NUM_READINGS;

  if (abs(prevValue - average) > 2) {
    Serial.println(average);
    prevValue = average;
  }

  sensorValue = average;
}


// the loop routine runs over and over again forever:
void loop() {

  readVoltage();

  if (sensorValue > 565) {  // > 13V
    if (!relay_on) {
      //Serial.println("Relay on");
      relay_on = true;
      //turn on relay
      digitalWrite(relay, LOW); //585 597 603 619

    }
  }

  if (sensorValue < 482) { // < 11V
    if (relay_on) {
      //turn off relay
      digitalWrite(relay, HIGH); //585 597 603 619

      //Serial.println("Relay off");
      relay_on = false;

    }

  }

}
