/**
 * Author:Ab Kurk
 * version: 1.0
 * date: 4/02/2018
 * Description: 
 * This sketch is part of the guide to putting your Arduino to sleep
 * tutorial. We use the:
 * DS3231 RTC
 * Arduino Pro Mini
 * In this example we use the RTC to wake up the Arduino.
 * After the data has been logged the Arduino goes back to sleep and gets woken up 5 minutes later to 
 * start all over again
 * Link To Tutorial http://www.thearduinomakerman.info/blog/2018/1/24/guide-to-arduino-sleep-mode
 * Link To Project   http://www.thearduinomakerman.info/blog/2018/2/5/wakeup-rtc-datalogger
 */

#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 2 //Pin we are going to use to wake up the Arduino
#include <DS3232RTC.h>  //RTC Library https://github.com/JChristensen/DS3232RTC
//RTC Module global variables
const int time_interval=1;// Sets the wakeup intervall in minutes

#include <SoftwareSerial.h>
#define txPin    3              // Connect pin 3 of Nano to US100 trigger/Tx
#define rxPin    4              // Connect pin 4 of Nano to US100 Echo/Rx
SoftwareSerial us100(rxPin,txPin);  // Set Nano for UART signaling 

void setup() {
  Serial.begin(9600);//Start Serial Comunication
  pinMode(LED_BUILTIN,OUTPUT);//We use the led on pin 13 to indecate when Arduino is A sleep
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  digitalWrite(LED_BUILTIN,HIGH);//turning LED on
  
  // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
  RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
  RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
  RTC.alarm(ALARM_1);
  RTC.alarm(ALARM_2);
  RTC.alarmInterrupt(ALARM_1, false);
  RTC.alarmInterrupt(ALARM_2, false);
  RTC.squareWave(SQWAVE_NONE);  

  time_t t; //create a temporary time variable so we can set the time and read the time from the RTC
  t=RTC.get();//Gets the current time of the RTC
  RTC.setAlarm(ALM1_MATCH_MINUTES , 0, minute(t)+time_interval, 0, 0);// Setting alarm 1 to go off 1 minutes from now
  // clear the alarm flag
  RTC.alarm(ALARM_1);
  // configure the INT/SQW pin for "interrupt" operation (disable square wave output)
  RTC.squareWave(SQWAVE_NONE);
  // enable interrupt output for Alarm 1
  RTC.alarmInterrupt(ALARM_1, true);

  pinMode(rxPin, INPUT);        // Set pin directions for US100 communications
  pinMode(txPin, OUTPUT);
  us100.begin(9600);            // and start SoftSerial service  
}

void loop() {
 Measure();
 Going_To_Sleep();
}

void Going_To_Sleep(){
  Serial.println("Prepare the bed");//prints time stamp on serial monitor
  sleep_enable();//Enabling sleep mode
  attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
  digitalWrite(LED_BUILTIN,LOW);//turning LED off
  time_t t;// creates temp time variable
  t=RTC.get(); //gets current time from rtc
  Serial.println("Sleep Time!!!");//prints time stamp on serial monitor
  delay(1000); //wait a second to allow the led to be turned off before going to sleep
  sleep_cpu();//activating sleep mode
  Serial.println("just woke up!");//next line of code executed after the interrupt 
  digitalWrite(LED_BUILTIN,HIGH);//turning LED on

  t=RTC.get();
  Serial.println("WakeUp Time!!");
  //Set New Alarm
  RTC.setAlarm(ALM1_MATCH_MINUTES , 0, minute(t)+time_interval, 0, 0);
  // clear the alarm flag
  RTC.alarm(ALARM_1);
}

void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
  sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}

void Measure() {
  #define getDist  0x55           // send this to get distance in mm
  #define getCels  0x50           // send this to get temp
  #define maxWait  1000           // max time to wait for US100 response   
  uint8_t highDist,lowDist;       // bytes read in from US100
  int     mmDist;                 // measured distance in mm  
  int     cTemp;                  // temp in Celsius for reporting
  Serial.println(">>>> Start sampling loop for US-100 testing <<<<");

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
  }
  else {
    Serial.println("No response to temp request");
    cTemp = 0;
  };

  Serial.println("Distance = " + String(mmDist/10) + " cm");  
  Serial.println("Temp = " + String(cTemp) + "C");  

  Serial.println(">>>>>>>>> Finish Measure <<<<<<<<<<");
}
