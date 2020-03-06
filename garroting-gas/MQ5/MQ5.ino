// Sensor Pin
#define mq5 A2
// Thereshold to warning
#define threshold 200

int sensorValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(mq5);

  if (sensorValue > threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}