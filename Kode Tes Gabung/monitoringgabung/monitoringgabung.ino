#include <Ethernet.h>

#include <DFRobot_PH.h>

/*
 * file DFRobot_PH.ino
 * @ https://github.com/DFRobot/DFRobot_PH
 *
 * This is the sample code for Gravity: Analog pH Sensor / Meter Kit V2, SKU:SEN0161-V2
 * In order to guarantee precision, a temperature sensor such as DS18B20 is needed, to execute automatic temperature compensation.
 * You can send commands in the serial monitor to execute the calibration.
 * Serial Commands:
 *   enterph -> enter the calibration mode
 *   calph   -> calibrate with the standard buffer solution, two buffer solutions(4.0 and 7.0) will be automaticlly recognized
 *   exitph  -> save the calibrated parameters and exit from calibration mode
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-04
 */
#include <OneWire.h>
#include <DallasTemperature.h>

// 数据输出脚接开发板数字引脚2
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#include "DFRobot_PH.h"
#include <EEPROM.h>

#define PH_PIN A1
float voltage,phValue,temperature;
float suhu;
DFRobot_PH ph;

void setup()
{
    Serial.begin(115200);  
    ph.begin();
    sensors.begin();
}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
        voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
        phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
        readTemperature();  
        readTurbidity();
        // Serial.print("temperature:");
        // Serial.print(temperature,1);
        Serial.print(" pH: ");
        Serial.println(phValue,2);
        // SendtoDB();
    }
    ph.calibration(voltage,temperature);           // calibration process by Serail CMD
}
float readTurbidity(){
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print(" Turbidity: ");
  Serial.print(voltage); // print out the value you read:
}
float readTemperature()
{
  //add your code here to get the temperature from your temperature sensor
  sensors.requestTemperatures(); // 发送命令获取温度
  Serial.print("Temperature: ");
  suhu = sensors.getTempCByIndex(0); // 获取温度
  Serial.print(suhu); 
}
// void SendtoDB(){
//    if (client.connect(server, 80)) {
//     Serial.println("");
//     Serial.println("connected");
//     // Make a HTTP request:
//     Serial.print("GET /monitoring/masukdb/koneksi.php?temperature=");
//     Serial.print(suhu);
//     Serial.print("&ph=");
//     Serial.println(phValue);
//     Serial.println("");
    
//     client.print("GET /arduino_mysql/koneksi.php?temperature=");     //YOUR URL
//     client.print(suhu);
//     client.print("&ph=");
//     client.print(phValue);
//     client.print(" ");      //SPACE BEFORE HTTP/1.1
//     client.print("HTTP/1.1");
//     client.println();
//     client.println("Host: 192.168.10.5");
//     client.println("Connection: close");
//     client.println();
//   } else {
//     // if you didn't get a connection to the server:
//     Serial.println("connection failed");
//   }
//  }