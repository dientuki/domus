int mqs[] = {150, 150, 150};
int values[] = {};
int sensorValue = 0;

void setup() {
  delay(20000);
}

void loop() {
  bool danger = false;
  
  for (byte i = 0; i < 2; i = i + 1) {
    sensorValue = analogRead("A" + i);
    values[i] = sensorValue;

    if (sensorValue >= mqs[i]) {
      danger = true;
    }
  }

  //Send data

  if (danger == true) {

  } else {
  
  }

  delay(1000);
}