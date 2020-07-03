#include <DS3232RTC.h>  //RTC Library https://github.com/JChristensen/DS3232RTC

void setup() {
  Serial.begin(9600);//Start Serial Comunication

  tmElements_t tm;
  tm.Hour = 00;               // set the RTC to an arbitrary time
  tm.Minute = 19;
  tm.Second = 00;
  tm.Day = 3;
  tm.Month = 1;
  tm.Year = 2020 - 1970;      // tmElements_t.Year is the offset from 1970
  RTC.write(tm);              // set the RTC from the tm structure

}

void loop() {
  time_t t; //create a temporary time variable so we can set the time and read the time from the RTC
  t=RTC.get();//Gets the current time of the RTC
  Serial.println("Date: "+String(day(t))+":"+String(month(t))+":"+String(year(t)));
  Serial.println("Time: "+String(hour(t))+":"+String(minute(t))+":"+String(second(t)));
  delay(5000);
}
