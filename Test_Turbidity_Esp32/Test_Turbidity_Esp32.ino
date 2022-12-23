void setup() {
  Serial.begin(115200); //Baud rate: 115200
}
void loop() {
  int sensorValue = analogRead(39);// read the input on analog pin 0:
  float turbidity = map(sensorValue, 0, 1400, 5, 1);
  String text = (String)turbidity;
  Serial.println(text); // print out the value you read:
  delay(500);
}
