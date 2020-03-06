// Sensor Pin
#define mq7 A3
// Thereshold to warning
#define threshold 200

int sensorValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(mq7);

  if (sensorValue > threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}