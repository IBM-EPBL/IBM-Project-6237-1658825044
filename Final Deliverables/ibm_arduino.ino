#include <string>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "ArduinoJson.h"
#include <HTTPClient.h>
LiquidCrystal_I2C lcd(0x27,20,4);
const char* ssid     = "Vr";
const char* password = "venkat123";
String payload;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(50);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.begin();
  lcd.backlight();
}
void link(void) {
   HTTPClient http;
   String url="https://node-red-fjaeq-2022-11-12.eu-gb.mybluemix.net/data";
//Serial.print(url);
  Serial.print("Making a request");
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
    if (httpCode > 0) { //Check for the ing code
        payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
    else {
      Serial.println("Error on HTTP request");
    }
  http.end();
}
void loop() {
  // put your main code here, to run repeatedly:
  link();

  //JSON
  Serial.println("Parsing start: ");
 
  //char JSONMessage[] = payload; //Original message
 
  StaticJsonBuffer<1000> JSONBuffer;                         //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(payload); //Parse message
 
  if (!parsed.success()) {   //Check for errors in parsing
 
    Serial.println("Parsing failed");
    delay(5000);
    ;
  }
 
  const char * sensorType = parsed["location"]; //Get sensor type value
  const char * sensorType1 = parsed["weather_report"];
  const char * sensorType2 = parsed["wea_alt"];
  const char * sensorType3 = parsed["schl_tmg"];
  const char * sensorType4 = parsed["spd_alt"];
  int value = parsed["humidity"];                    //Get value of sensor measurement
  double value1 = parsed["temperature"];
  int value2 = parsed["pressure"];
  Serial.print("Location: ");
  Serial.println(sensorType);
  Serial.print("Temperature: ");
  Serial.println(value1);
  Serial.print("Pressure: ");
  Serial.println(value2);
  Serial.print("Humidity: ");
  Serial.println(value);
  Serial.print("Weather Report: ");
  Serial.println(sensorType1);
  Serial.print("Message: ");
  Serial.println(sensorType2);
  Serial.print("Timing: ");
  Serial.println(sensorType3);
  Serial.print("Speed Limit: ");
  Serial.println(sensorType4);
  Serial.println();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome IBM IOT");
  lcd.setCursor(0, 1);
  lcd.print("Loc: ");
  lcd.print(sensorType);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(value1);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(value);
  lcd.print("%");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wea: ");
  lcd.print(sensorType1);
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(sensorType3);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(sensorType2);
  lcd.setCursor(0, 1);
  lcd.print(sensorType4);
}
