/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
void setup() {
  pinMode(13, OUTPUT); // for LED
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("Ready!");
}
void loop() {
  delay(100);
}
// callback for received data
void receiveData(int byteCount){
  while(Wire.available()) {
  number = Wire.read();
  Serial.print("data received: ");
  Serial.println(number);
  if (number == 1){
  if (state == 0){
  digitalWrite(13, HIGH); // set the LED on
  state = 1;
}
else{
  digitalWrite(13, LOW); // set the LED off
  state = 0;
}
}
}
}
// callback for sending data
void sendData(){
Wire.write(number+1);
}
