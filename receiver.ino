#include <SoftwareSerial.h>
#include <SimpleCLI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const byte rxPin = D1;
const byte txPin = D2;
SoftwareSerial Serial2(rxPin, txPin);

SimpleCLI cli;

unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
    
  Serial.println("\nStarted");

  Command connectCmd = cli.addCmd("connect", [](cmd* ptr){
    Command cmd(ptr);
    String ssid = cmd.getArgument("ssid").getValue();
    String password = cmd.getArgument("password").getValue();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial2.println("OK");
    
    Serial.println("Connecting to");
    Serial.println("SSID: " + ssid);
    Serial.println("Password: " + password);

    for(int i=0; i<1000 && WiFi.status() != WL_CONNECTED; i++) {
                delay(10);
            }

            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("Connected!");
                Serial2.println("Connected!");
            } else {
                Serial.println("Error");
                Serial2.println("Error");
                WiFi.disconnect();
            }
  });
  connectCmd.addPosArg("s/sid");
  connectCmd.addPosArg("p/assword");
}

void loop() {
  if (Serial2.available()) {
    String input = Serial2.readString();
    cli.parse(input);
  }
  if (millis() - lastTime > 3000 && WiFi.status() == WL_CONNECTED) {
    lastTime = millis();
    HTTPClient http;
    http.begin("http://192.162.4.1/test.html");
    http.end();
  }  
}
