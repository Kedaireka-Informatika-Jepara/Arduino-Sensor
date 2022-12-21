void setup() {
  Serial.begin(9600); //Baud rate: 9600
}
void loop() {
  int sensorValue = analogRead(39);// read the input on analog pin 0:
  float turbidity = map(sensorValue, 0, 2800, 5, 1);
  String text = (String)turbidity;
  Serial.println(text); // print out the value you read:
  delay(500);
}