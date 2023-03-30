#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "YOUR_SSID";   //SSID
const char *password = "YOUR_PASS";   //Password

const long utcOffsetInSeconds = 3600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId = "None";
byte nuidPICC[4];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.pl.pool.ntp.org", utcOffsetInSeconds);
 
void setup(void) 
{
 Serial.begin(115200);
 Serial.println("System initialized");
 nfc.begin();
 pinMode(D4, OUTPUT);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {   //wait for connection
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

}
 
void loop() 
{
 readNFC();

}
void open(){
  digitalWrite(D4, HIGH);
  delay(3000);
}
void burdzy(){
  delay(5000);
  digitalWrite(D4, HIGH);
  delay(3000);
}
void print_time(){
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.print(timeClient.getSeconds());

}
void limited_acces(){
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  if (hour < 8 || (hour == 14 && minute > 50) || (hour == 15 && minute < 15)){ //
    open();
  } else if ((hour == 8 && 50>= minute >= 45)) { //First brake 5min long
    open();
  } else if (hour == 9 && 45 >= minute >= 35 ) { // Second brake 10min long
    open();
  } else if (hour == 10 && 35 >= minute >= 30 ) { // Third brake 5min long
    open();
  } else if (hour == 11 && 35 >= minute >= 20 ) { // Fourth brake 15min long
    open();
  }else if (hour == 12 && 25 >= minute >= 20 ) { // Fifth brake 5min long
    open();
  }else if (hour == 13 && 15 >= minute >= 10 ) { // sixth brake 5min long
    open();
  }else if (hour == 14 && 5 >= minute ) { // seventh brake 5min long
    open();
  }

}
 
void readNFC() 
{
  
 if (nfc.tagPresent())
 {
   NfcTag tag = nfc.read();
   tag.print();
   tagId = tag.getUidString();
   if (tag.getUidString() == "A3 1E AD A5"){
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 E7 F0 1C"){//łentek
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "81 11 C9 1C"){//Madzia
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "81 0C F8 1C"){//chicker
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 D0 E5 1C"){//burdzy
   burdzy();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "81 11 CC 1C"){
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 9C 37 1C"){//Maciek
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 59 94 1C"){//Maksiu
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 2F DA 1C"){//BRYGU
   limited_acces();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 25 E9 1C"){//Kurzawa
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "81 0E 9E 1C"){//Czekaj
   limited_acces();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "C3 3E 0A 1C"){//Hjaduk brelok
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "C3 96 9D 1B"){//hajduk kurwa mac 24
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "71 91 C3 1C"){//Oliwia
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 }else if (tag.getUidString() == "43 76 4E A8"){//Krzychu kierownik
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 delay(1000);
 }else if (tag.getUidString() == "71 40 71 1C"){//Dominik Batko
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 delay(1000);
 }else if (tag.getUidString() == "23 B9 BC 1D"){//chicker brelok
   open();
   tag.getUidString() = "None";
   digitalWrite(D4,LOW);
 delay(1000);
 }
 }
}