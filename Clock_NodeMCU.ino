#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define Relay1 D1
 
// Setup Wifi
const char *ssid     = "insert_ssid_name";
const char *password = "insert_password";

const int onhour=12;
const int onmin=41;

const int offhour=12;
const int offmin=50;

const long utcOffsetInSeconds = 25200; // set utc
 
// Set date to day
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
 
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);
 
void setup(){
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
 
  WiFi.begin(ssid, password);
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
 
  timeClient.begin();
}
 
void loop() {
  timeClient.update();
 
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  if(timeClient.getHours()==onhour && timeClient.getMinutes()==onmin)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Light ON");
  }
  else if(timeClient.getHours()==offhour && timeClient.getMinutes()==offmin)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Light OFF");
  }
 
  delay(1000);
}
