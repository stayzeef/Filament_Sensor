#include "OctoPrintClient.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "SSID";
const char* password = "PASSWORD";
String ApiKey   = "APIKEY";
String server   = "SERVERIP";
int port        = 5000;
String user     = "USER";
String pass     = "PASSWORD";
boolean psu     = false;

#define sensorPin A0

OctoPrintClient octo(ApiKey, server, port, user, pass, psu);


void setup() 
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  Serial.println("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print(".");
 
  }

  Serial.println("connected!");
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) //only if we're connected to wifi
  { 
    if(printCheck()) //only if we're printing
    {
      Serial.println("printing...");
     
      delay(50);
      if(!filament())
      {
        octo.pausePrint();
      }
    }
    else
    {

    }
      
  }
 
  delay(30000);    //Send a request every 30 seconds
  
}

bool printCheck()
{
    octo.getPrinterJobResults(); //update the results
    bool printcheck = octo.isPrinting();
    Serial.print("isprinting: "); Serial.println(printcheck);
    return printcheck;  
}


bool filament()
{
  int value = analogRead(sensorPin);
  int mappedValue = map(value, 0, 255, 0, 100);
  Serial.println(mappedValue);
  if(mappedValue > 10) //change this based on light sensor readings
  {
    Serial.println("you're out of fillament");
    return false;
  }
  else
  {
    Serial.println("you good");
    return true;
  }
}
