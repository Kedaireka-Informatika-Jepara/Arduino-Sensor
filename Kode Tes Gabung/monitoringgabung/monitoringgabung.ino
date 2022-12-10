#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DFRobot_PH.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#include "DFRobot_PH.h"
#include <EEPROM.h>

#define PH_PIN A1
#define TURBIDITY_PIN A0
float voltage, phValue, temperature, turbidity;
float suhu;
DFRobot_PH ph;
/* Set these to your desired credentials. */
const char *ssid = "sya";
const char *password = "sugawara";

//Web/Server address to read/write from 
const char *host = "testmonitoring.cemebsa.com";
WiFiClient client;
void setup() {
  delay(1000);
  Serial.begin(115200);
  ph.begin();
  sensors.begin();
  WiFi.mode(WIFI_OFF);            //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);            //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  
  readTemperature();
  readTurbidity();
  readpH();
  
  SendtoDB();

  ph.calibration(voltage, temperature);  // calibration process by Serail CMD
  delay(10000);
}
float readpH(){
  voltage = analogRead(PH_PIN) / 1024.0 * 5000;  // read the voltage
  phValue = ph.readPH(voltage, temperature);     // convert voltage to pH with temperature compensation
  Serial.print(" pH: ");
  Serial.println(phValue, 2);
}
float readTurbidity() {
  int sensorValue = analogRead(TURBIDITY_PIN);                // read the input on analog pin 0:
  float turbidity = sensorValue * (5.0 / 1024.0);  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print(" Turbidity: ");
  Serial.print(turbidity);  // print out the value you read:
}
float readTemperature() {
  //add your code here to get the temperature from your temperature sensor
  sensors.requestTemperatures();  // 发送命令获取温度
  Serial.print("Temperature: ");
  suhu = sensors.getTempCByIndex(0);  // 获取温度
  Serial.print(suhu);
}
void SendtoDB() {
  //Post Data
  postData = "suhu=" + suhu + "&ph=" + phValue + "&turbidity=" + turbidity;

  http.begin(client, "http://testmonitoring.cemebsa.com/test/koneksi.php");  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");       //Specify content-type header

  int httpCode = http.POST(postData);  //Send the request
  String payload = http.getString();   //Get the response payload

  Serial.println(postData);
  Serial.println(httpCode);  //Print HTTP return code
  Serial.println(payload);   //Print request response payload

  http.end();  //Close connection

  
}
