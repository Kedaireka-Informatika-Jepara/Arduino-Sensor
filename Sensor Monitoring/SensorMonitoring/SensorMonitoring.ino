#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "MQ135.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define relay D6
#define ONE_WIRE_BUS 14

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
int muxA= 5;
int muxB= 4;
int muxC= 0;
int muxD= 2;
int suhup= 16;
int analogPin = A0;
int val = 0;

/* Set these to your desired credentials. */
const char *ssid = "sya";
const char *password = "sugawara";

//Web/Server address to read/write from 
const char *host = "monitoring.cemebsa.com";
WiFiClient client;

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);

  pinMode(relay, OUTPUT);

  pinMode(muxA, OUTPUT);pinMode(muxB, OUTPUT);
  pinMode(muxC, OUTPUT);pinMode(muxD, OUTPUT);

  sensors.begin();
  Serial.begin(9600);
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

//=======================================================================
//                    Main Program Loop
//=======================================================================

void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
  String postData, curahHujan;
  String postVariable = "temp=";
  float celcius, amonia, suhu, gasValue;
  int relay;

  digitalWrite(relay, HIGH);
  delay(3000);
  digitalWrite(relay, LOW);
  delay(3000);

  if (OUTPUT == HIGH){

    // Gas
    //connect to pin input 0 => [A B C D] : [0 0 0 0]
    digitalWrite(muxA, LOW); digitalWrite(muxB, LOW);
    digitalWrite(muxC, LOW); digitalWrite(muxD, LOW);  
    val = analogRead(analogPin);
    MQ135 gasSensor = MQ135(analogPin);
    float gas = gasSensor.getPPM();
    gasValue = gas / 10000.0;

    // Curah Hujan
    //connect to pin input 15 => [A B C D] : [1 1 1 1]
    digitalWrite(muxA, HIGH); digitalWrite(muxB, HIGH);
    digitalWrite(muxC, HIGH); digitalWrite(muxD, HIGH);
    val = analogRead(analogPin);

    // Suhu
    sensors.requestTemperatures();
    Celsius = sensors.getTempCByIndex(0);
    
    // Relay
    relay = 1;
  
  }

  //Post Data
  postData = postVariable + Celsius + "&amonia=" + gasValue + "&curah_hujan=" + val + "&relay=" + relay;
  
  http.begin(client, "http://monitoring.cemebsa.com/test/koneksi.php"); //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(postData);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
  delay(5000);  //Post Data at every 5 seconds
}
