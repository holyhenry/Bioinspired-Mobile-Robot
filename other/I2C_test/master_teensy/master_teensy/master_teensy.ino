#include <Wire.h>

void setup() {
  Wire.begin();          // join i2c bus (address optional for master)
  
  Serial.begin(230400);  // start serial monitor output
  while (!Serial) ;      // wait for Arduino Serial Monitor to open

  Serial.println("Master Ready!");
  Serial.println("Send the character 'c' to calibrate all motors ");
  Serial.println("Send the character 'l' to loop control");
  Serial.println("Send the character 'i' to idle mode");
  Serial.println("Send the character 'b' to read bus voltage");
  Serial.println("Send the character 'e' to clear errors");
  Serial.println("Send the character 'p' to print errors");
  Serial.println("Send the character 's' to do sinusoidal move");
  Serial.println("Send the character 't' to test Odrive communication speed");
}

void loop() {
  
  if (Serial.available()) {
    char c = Serial.read();
      Wire.beginTransmission(2); // transmit to device #2
      Wire.write(c);             // sends five bytes 
      Wire.endTransmission();    // stop transmitting
  }
}
