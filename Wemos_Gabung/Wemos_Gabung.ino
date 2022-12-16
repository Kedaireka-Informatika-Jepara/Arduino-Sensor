//Defines which libraries to use
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>            //for temp sensor ds18b20
#include <DallasTemperature.h>  //for temp sensor ds18b20
#include <DFRobot_PH.h>         //for pH sensor Gravity pH V2
#include <EEPROM.h>             //for pH sensor Gravity pH V2
#include <MQ135.h>              //for gas sensor MQ135

//Defines what pins are used
#define ONE_WIRE_BUS D5         //DS18B20 connect to pin D5
#define MUXA D1
#define MUXB D2
#define MUXC D3
#define MUXD D4
#define ANALOG_INPUT A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DFRobot_PH ph;

//Define the network connection
/* Set these to your desired credentials. */
const char *ssid = "Alifio Adel";
const char *password = "ShortSeal";

//Web/Server address to read/write from 
const char *host = "monitoring.cemebsa.com";
WiFiClient client;

// variabel
  float temp;
  float gas;
  float turbidity;
  float pHvalue, pHsensor;
  float rain;
  HTTPClient http;
  String postData;
  String postVariable;
  
void setup() {
  delay(1000); //wait 1s after power on

  //set connection as output from multiplexer
  pinMode(MUXA, OUTPUT);
  pinMode(MUXB, OUTPUT);
  pinMode(MUXC, OUTPUT);
  pinMode(MUXD, OUTPUT);
  // ph.begin();
  sensors.begin();
  Serial.begin(115200);
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

void changeMux(int d, int c, int b, int a) {
  digitalWrite(MUXA, a);
  digitalWrite(MUXB, b);
  digitalWrite(MUXC, c);
  digitalWrite(MUXD, d); 
}

void loop() {
  
  readTemperature();
  readTurbidity();
  // readpH();
  readGas();
  readRaindrop();
  sendtoDB();
  delay(2000);
}
void readTurbidity(){
  // Turbidity
  // MUX pin C10 => [1,0,1,0]
  changeMux(HIGH, LOW, HIGH, LOW);
  int sensorTurb = analogRead(ANALOG_INPUT);
  turbidity = sensorTurb * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print(" Turbidity: ");
  Serial.print(turbidity);  // print out the value you read:
}
void readTemperature(){
  //Temp Sensor
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(temp);
}
void readGas(){
  //Multiplexer
  //  Gas
  //  MUX pin on C0 => [0,0,0,0]
  changeMux(LOW, LOW, LOW, LOW);
  MQ135 gasSensor = MQ135(ANALOG_INPUT);
  gas = (gasSensor.getPPM())/10000.0; // Get the ppm of CO2 sensed (assuming only CO2 in the air)
  Serial.print(" Gas: ");
  Serial.print(gas);  // print out the value you read:
}
// void readpH(){
//   // pH
//   // MUX pin on C12 => [1,1,0,0]
//   changeMux(HIGH, HIGH, LOW, LOW);
//   float sensPH
//   sensPH = analogRead(ANALOG_INPUT)/1024.0*5000;
//   pHvalue = ph.readPH(voltage,temp);
//   pHsensor = (phValue,2)
//   Serial.print(" pH: ");
//   Serial.print(pHsensor);  // print out the value you read:
// }
void readRaindrop(){
// Raindrop
  // MUX pin on C15 => [1,1,1,1]
  changeMux(HIGH, HIGH, HIGH, HIGH);
  rain = analogRead(ANALOG_INPUT);
  Serial.print(" Raindrop: ");
  Serial.println(rain);  // print out the value you read:
}
void sendtoDB() {
  postVariable = "suhu=";
  //Post Data
  postData = postVariable + temp + "&ph=" + "7" + "&turbidity=" + turbidity + "&raindrop=" + rain + "&gas=" + gas;

  http.begin(client, "http://monitoring.cemebsa.com/test/koneksi.php");  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");       //Specify content-type header

  int httpCode = http.POST(postData);  //Send the request
  String payload = http.getString();   //Get the response payload

  Serial.println(postData);
  Serial.println(httpCode);  //Print HTTP return code
  Serial.println(payload);   //Print request response payload

  http.end();  //Close connection 
}
