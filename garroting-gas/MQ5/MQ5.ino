int sensorValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue, DEC);

  if (sensorValue > 500) {
    //Serial.println("peligro");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(500);
}
