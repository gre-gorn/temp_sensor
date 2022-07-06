/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourSSID";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://domain.com/sensor/index.php";

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0; 

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;

// Set timer to 2 seconds (2000)
unsigned long timerDelay = 2000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 2 seconds
  if ((millis() - lastTime) > timerDelay) {
    int a = analogRead(pinTempSensor);
  
    float R = 4095.0 / a - 1.0;
    R = R0 * R;
 
    float temperature = 1.0/(log(R/R0)/B + 1/298.15) - 273.15; // convert to temperature via datasheet
    
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
     
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      String temperatureString =  String(temperature);
      String rawValueString =  String(a);
      String jsonString = "{\"sensor\":\"Attic\",\"value\":\"" + temperatureString + "\",\"raw\":\"" + rawValueString + "\"}";

      Serial.println("json:");
      Serial.println(jsonString);
      
      int httpResponseCode = http.POST(jsonString);
    
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    
    lastTime = millis();
  }
}
