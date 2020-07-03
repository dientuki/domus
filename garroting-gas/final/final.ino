#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#define dangerpin 2
#define okpin 3 
#define buzzer 4

int mqs[] = {150, 200, 150, 150};


RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 03;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t imperius = 00;  

void setup() {
  pinMode(dangerpin, OUTPUT);
  pinMode(okpin, OUTPUT);  
  pinMode(buzzer, OUTPUT);

  digitalWrite(dangerpin, LOW);
  digitalWrite(okpin, LOW);     

  delay(10000);
  digitalWrite(buzzer, LOW);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  delay(10000);
  Serial.begin(9600);
}

void loop() {
  bool danger = false;
  int values[] = {};
  int sensorValue = 0;  
  
  network.update();
  
  for (byte i = 0; i < 4; i = i + 1) {
    sensorValue = analogRead("A" + i);
    values[i] = sensorValue;

    if (sensorValue >= mqs[i]) {
      danger = true;
    }
    Serial.print("MQ ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorValue);
  }

  //Send data
  RF24NetworkHeader header(imperius);     // (Address where the data is going)
  bool ok = network.write(header, &values, sizeof(values)); // Send the data

  light(danger);

  delay(1000);
}

void light(bool state) {
  if (state == false) {
    digitalWrite(okpin, HIGH);
    digitalWrite(dangerpin, LOW);    
  } else {
    digitalWrite(okpin, LOW);
    digitalWrite(dangerpin, HIGH);   
    alarm();
  }
}

void alarm() {
  for (int j = 0; j < 80; j++) {  // make a sound
    digitalWrite(buzzer, HIGH); // send high signal to buzzer 
    delay(2); // delay 1ms
    digitalWrite(buzzer, LOW); // send low signal to buzzer
    delay(2);
  }   
}
