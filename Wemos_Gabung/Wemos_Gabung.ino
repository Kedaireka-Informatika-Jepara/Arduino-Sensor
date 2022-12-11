//Defines which libraries to use
#include <OneWire.h>            //for temp sensor ds18b20
#include <DallasTemperature.h>  //for temp sensor ds18b20
#include "DFRobot_PH.h"         //for pH sensor Gravity pH V2
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

//Define the network connection


void setup() {
  delay(1000); //wait 1s after power on

  //set connection as output from multiplexer
  pinMode(MUXA, OUTPUT);
  pinMode(MUXB, OUTPUT);
  pinMode(MUXC, OUTPUT);
  pinMode(MUXD, OUTPUT);

  sensors.begin();
  Serial.begin(115200);
  
}

void changeMux(int d, int c, int b, int a) {
  digitalWrite(MUXA, a);
  digitalWrite(MUXB, b);
  digitalWrite(MUXC, c);
  digitalWrite(MUXD, d); 
}

void loop() {

  float Temp;
  float Gas;
  float Turbidity;
  float pHvalue, pHsensor;
  float Rain;
  
  
  //Temp Sensor
  sensors.requestTemperatures();
  Temp = sensors.getTempCByIndex(0);

  //Multiplexer
  //  Gas
  //  MUX pin on C0 => [0,0,0,0]
  changeMux(LOW, LOW, LOW, LOW);
  MQ135 gasSensor = MQ135(ANALOG_INPUT);
  Gas = (gasSensor.getPPM())/10000.0; // Get the ppm of CO2 sensed (assuming only CO2 in the air)

  // Turbidity
  // MUX pin C10 => [1,0,1,0]
  changeMux(HIGH, LOW, HIGH, LOW);
  int sensorTurb = analogRead(ANALOG_INPUT);
  Turbidity = sensorTurb * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
  // pH
  // MUX pin on C12 => [1,1,0,0]
  changeMux(HIGH, HIGH, LOW, LOW);
  float sensPH, temperature = 25;
  sensPH = analogRead(ANALOG_INPUT)/1024.0*5000;
  pHvalue = ph.readPH(voltage,temperature);
  pHsensor = (phValue,2)

  // Raindrop
  // MUX pin on C15 => [1,1,1,1]
  changeMux(HIGH, HIGH, HIGH, HIGH);
  Rain = analogRead(ANALOG_INPUT);
  
  
  

}
