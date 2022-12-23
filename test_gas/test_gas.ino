#include "MQ135.h"
int analogPin = A0;
int val = 0;
float gasValue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin);
  MQ135 gasSensor = MQ135(analogPin);
  float gas = gasSensor.getPPM();
  gasValue = gas / 10000.0;
  Serial.println("Amonia = ");
  Serial.println(gasValue);
  delay(500);
}
