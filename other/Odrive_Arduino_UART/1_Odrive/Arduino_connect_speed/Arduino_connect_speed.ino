//#include <SoftwareSerial.h>
#include <ODriveArduino.h>

// Serial to the ODrive
HardwareSerial &odrive_serial = Serial1;
// SoftwareSerial odrive_serial(8, 9); //RX (ODrive TX), TX (ODrive RX)
// Note: you must also connect GND on ODrive to GND on Arduino!

// ODrive object
ODriveArduino odrive(odrive_serial);

void setup() {
  // ODrive uses 115200 baud
  odrive_serial.begin(115200);

  // Serial to PC
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor to open

  Serial.println("ODriveArduino");
  Serial.println("Hello\nSetting parameters...");

  // Set motor paramaters
  set_odrive_parameters(odrive_serial);

    // // In this example we set the same parameters to both motors.
    // // You can of course set them different if you want.
    // // See the documentation or play around in odrivetool to see the available parameters
    // for (int axis = 0; axis < 2; ++axis) {
    //   odrive_serial << "w axis" << axis << ".controller.config.vel_limit " << 22000.0f << '\n';
    //   odrive_serial << "w axis" << axis << ".motor.config.current_lim " << 11.0f << '\n';
    //   // This ends up writing something like "w axis0.motor.config.current_lim 10.0\n"
    // }
  
  Serial.println("Ready!");
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
  
}
