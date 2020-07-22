#include <ODriveArduino.h>
#include <Wire.h>

char c ; // signal character

HardwareSerial &odrive_serial = Serial2; // Serial to the ODrive
ODriveArduino odrive(odrive_serial);     // ODrive object

void setup() {
//-------------------Odrive <------> Teensy-----------------------------
  odrive_serial.begin(230400);  // ODrive uses 115200 baud

  Serial.begin(230400);  // start serial monitor output
  while (!Serial) ;      // wait for Arduino Serial Monitor to open

  Serial.println("ODriveTeeeeensy");
  Serial.println("Hello\nSetting parameters...");

  set_odrive_parameters(odrive_serial);  // Set motor paramaters

//-------------------Teensy <------> Master-----------------------------
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
}

char receiveEvent(int howMany){

  // function that executes whenever data is received from master
  while(1 < Wire.available()){
    char s = Wire.read();    // receive byte as a character
    Serial.print("Received signal: ");
    Serial.println(s);  
    return s; 
  } 
}

void loop() {
  
    c = receiveEvent(1);
    
    // Run calibration sequence
    if (c == 'c') {
      Serial.println("Calibrating motors");
      calibrate_motors(odrive);
    }

    // Set loop control
    if (c == 'l' ) {
      Serial.println("Loop control");
      loop_control(odrive);
    }

    // Set idle mode
    if (c == 'i') {
      Serial.println("Idle mode");
      idle_mode(odrive);
    }

    // Read bus voltage from both ODrives
    if (c == 'b') {
      Serial.println("Reading bus voltage");
      Serial << "Vbus voltage: " << bus_voltage(odrive, odrive_serial) << '\n';  
    }

    // Clear errors
    if (c == 'e' ) {
      Serial.println("");
      Serial.println("odrive_1******************");
      clear_errors(odrive, odrive_serial);
    }

    // Print errors
    if (c == 'p') {
    print_errors(odrive, odrive_serial);
    }

    // Sinusoidal move
    if (c == 's') {
      Serial.println("Sinusoidal move");
      sinusoidal_move(odrive);
    }

    // Test Odrive communication speed
    if (c == 't') {
      Serial.println("Testing Odrive communication speed");
      test_odrive_communication_speed(odrive, odrive_serial);
    }
  
}
