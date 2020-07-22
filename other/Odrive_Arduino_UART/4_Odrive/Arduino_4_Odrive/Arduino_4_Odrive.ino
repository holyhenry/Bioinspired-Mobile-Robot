#include <ODriveArduino.h>
#include <Eigen30.h>
using Eigen::MatrixXd;

HardwareSerial &leg_1_serial = Serial1;
HardwareSerial &leg_2_serial = Serial2;
HardwareSerial &leg_3_serial = Serial3;
HardwareSerial &leg_4_serial = Serial4;

ODriveArduino odrive_1(leg_1_serial);
ODriveArduino odrive_2(leg_2_serial);
ODriveArduino odrive_3(leg_3_serial);
ODriveArduino odrive_4(leg_4_serial);

void setup() {
  // ODrive uses 115200 baud
  leg_1_serial.begin(115200);
  leg_2_serial.begin(115200);
  leg_3_serial.begin(115200);
  leg_4_serial.begin(115200);
  
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor to open

  Serial.println("ODriveTeeeeensy");
  Serial.println("Hello");

  // Set motor paramaters
  set_odrive_parameters(leg_1_serial);
  set_odrive_parameters(leg_2_serial);
  set_odrive_parameters(leg_3_serial);
  set_odrive_parameters(leg_4_serial);
  
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
      
    // Run calibration sequence
    if (c == 'c') {

      Serial.println("Calibrating motors");
      calibrate_motors(odrive_1, odrive_2, odrive_3, odrive_4);

    }

    // Set loop control
    if (c == 'l' ) {

      Serial.println("Loop control");
      loop_control(odrive_1, odrive_2, odrive_3, odrive_4);

    }

    // Set idle mode
    if (c == 'i') {

      Serial.println("Idle mode");
      idle_mode(odrive_1, odrive_2, odrive_3, odrive_4);

    }

    // Read bus voltage from both ODrives
    if (c == 'b') {

      Serial.println("Reading bus voltage");
      Serial << "Vbus voltage: " << bus_voltage(odrive_1, leg_1_serial) << '\n';
      Serial << "Vbus voltage: " << bus_voltage(odrive_2, leg_2_serial) << '\n';
      Serial << "Vbus voltage: " << bus_voltage(odrive_3, leg_3_serial) << '\n';
      Serial << "Vbus voltage: " << bus_voltage(odrive_4, leg_4_serial) << '\n';    

    }

    // Clear errors
    if (c == 'e' ) {
      Serial.println("");
      Serial.println("odrive_1******************");
      clear_errors(odrive_1, leg_1_serial);
      Serial.println("");
      Serial.println("odrive_2******************");
      clear_errors(odrive_2, leg_2_serial);
      Serial.println("");
      Serial.println("odrive_3******************");
      clear_errors(odrive_3, leg_3_serial);
      Serial.println("");
      Serial.println("odrive_4******************");
      clear_errors(odrive_4, leg_4_serial);

    }

    // Print errors
    if (c == 'p') {

    print_errors(odrive_1, leg_1_serial);
    print_errors(odrive_2, leg_2_serial);
    print_errors(odrive_3, leg_3_serial);
    print_errors(odrive_4, leg_4_serial);
      
    }

    // Sinusoidal move
    if (c == 's') {

      Serial.println("Sinusoidal move");
      sinusoidal_move(odrive_1, odrive_2, odrive_3, odrive_4);

    }

    // Test Odrive communication speed
    if (c == 't') {
      
      Serial.println("Testing Odrive communication speed");
      test_odrive_communication_speed(odrive_1, leg_1_serial, odrive_2, leg_2_serial, 
                                      odrive_3, leg_3_serial, odrive_4, leg_4_serial);
      
    }
  }
  
}
