#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


WiFiClient wifiClient;

int servoPin = 0; 

int motor_angle = 0;
 
const char* ssid = "Your Wifi Name";
const char* password = "Your wifi password";
 
void setup () {

  pinMode(servoPin,OUTPUT);
 
  Serial.begin(115200);
  
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { 

    // if wifi connected turn on led
    digitalWrite(D1,HIGH);
 
    HTTPClient http; 
 
    http.begin(wifiClient, "http://127.0.0.1:5000/api"); 
    int httpCode = http.GET();                                  
 
    if (httpCode > 0) { 
 
      String payload = http.getString(); 
      //Serial.println(payload); 
      motor_angle = payload.toInt();
      //Serial.print('Motor:');
      Serial.println(motor_angle); 

        int ontime = map(motor_angle,0,180,600,2600);
        int offtime = 20000-ontime;
        Serial.println(motor_angle);
        digitalWrite(servoPin,HIGH);
        delayMicroseconds(ontime);
        digitalWrite(servoPin,LOW);
        delayMicroseconds(offtime);           
 
    }
 
    http.end();
 
  }
 
  delay(300);
}
