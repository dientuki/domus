#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#define dangerpin  10
#define okpin  9

int mqs[] = {150, 150, 150};
int values[] = {};
int sensorValue = 0;

RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 03;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t imperius = 00;  

void setup() {
  pinMode(dangerpin, OUTPUT);
  pinMode(okpin, OUTPUT);  
  digitalWrite(dangerpin, LOW);
  digitalWrite(okpin, LOW);     
    
  delay(10000);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  delay(10000);
}

void loop() {
  bool danger = false;
  network.update();
  
  for (byte i = 0; i < 2; i = i + 1) {
    sensorValue = analogRead("A" + i);
    values[i] = sensorValue;

    if (sensorValue >= mqs[i]) {
      danger = true;
    }
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
  }
}
