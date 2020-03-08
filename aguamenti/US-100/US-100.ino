// sudo chmod a+rw /dev/ttyACM0d
// http://arduinoinfo.mywikis.net/wiki/UltraSonicDistance

#include <SoftwareSerial.h>

#define txPin    3              // Connect pin 2 of Nano to US100 trigger/Tx
#define rxPin    4              // Connect pin 3 of Nano to US100 Echo/Rx
#define getDist  0x55           // send this to get distance in mm
#define getCels  0x50           // send this to get temp
#define loopTime 2000           // delay time in ms between loop iterations
#define maxWait  1000           // max time to wait for US100 response 

SoftwareSerial us100(rxPin,txPin);  // Set Nano for UART signaling 
int     mmDist;                 // measured distance in mm
uint8_t highDist,lowDist;       // bytes read in from US100
int     cTemp;                  // temp in Celsius for reporting
float   fTemp;                  // temp in Farenheit for reporting

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // talk to the controlling device
  pinMode(rxPin, INPUT);        // Set pin directions for US100 communications
  pinMode(txPin, OUTPUT);
  us100.begin(9600);            // and start SoftSerial service
}

void loop() {
  Serial.println("Start sampling loop for US-100 testing");

  us100.flush();
  us100.write(getDist);         // ask US-100 to get distance; wait for response
  for ( int i=0; (i<maxWait) && !us100.available(); i++ ) delay(1);
  if (us100.available()) {
    highDist = us100.read();    // get high byte
    for ( int i=0; (i<maxWait) && !us100.available(); i++ ) delay(1);
    if (us100.available()) {
      lowDist = us100.read();   // get low byte
      mmDist = highDist*256 + lowDist;
    }
    else {
      Serial.println("Incomplete response to distance request");
      mmDist = 0;
    }
  }
  else {
    Serial.println("No response to distance request");
    mmDist = 0;
  };

  delay(1);                     // let US100 catch its breath, otherwise won't respond
  us100.flush();
  us100.write(getCels);
  for ( int j=0; (j<maxWait) && !us100.available(); j++ ) delay(1);
  if (us100.available()) {
    cTemp = us100.read() - 45;
    fTemp = cTemp * 1.8 + 32;
  }
  else {
    Serial.println("No response to temp request");
    cTemp = 0;
    fTemp = 0.0;
  };

  Serial.print("Distance = ");  
  Serial.print(mmDist/10);
  Serial.print(" cm    Temp = ");  
  Serial.print(cTemp);
  Serial.print(" C = ");  
  Serial.print(fTemp);  
  Serial.println(" F");

  delay(loopTime);
}
