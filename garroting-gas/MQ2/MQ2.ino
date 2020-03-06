// Sensor Pin
#define mq2 A0

int sensorValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(mq2);


  delay(500);
}
