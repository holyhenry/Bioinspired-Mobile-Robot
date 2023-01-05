#include <ODriveArduino.h>

#include <stlport.h>
#include <Eigen30.h>

using Eigen::Vector3d;
using Eigen::Matrix3d;
using Eigen::Matrix2d;

HardwareSerial &odrive_serial = Serial1; // Serial to the ODrive

ODriveArduino odrive(odrive_serial);     // ODrive object

void setup() {
  
  odrive_serial.begin(115200);   // ODrive uses 115200 baud

  Serial.begin(115200);   // Serial to PC
  while (!Serial) ;       // wait for Arduino Serial Monitor to open
  Serial.println("ODriveArduino");

  set_odrive_parameters(odrive_serial);
  Serial.println("Setting parameters...");
  
  Serial << "Ready for basic test!\n";
  Serial << "Send 'c' to calibrate all motors\n"  << "Send 'l' to close loop control\n" << "Send 'i' to idle mode\n"          << "Send 'b' to read bus voltage\n";
  Serial << "Send 'e' to clear errors\n"          << "Send 'p' to print errors\n"       << "Send 's' to do sinusoidal move\n" << "Send 't' to test Odrive communication speed\n";

  Serial.println("Forward Kinematics computing");
  Matrix2d FK(2,1);
  double thetaL = 0.25 * PI;
  double thetaR = 0.75 * PI;
  double l1 = 0.09;
  double l2 = 0.16;
  double w = 0.07;
  forward_kinematics(FK, thetaL, thetaR, l1, l2, w);      
  Serial.print("x = ");
  Serial.println(FK(0,0), 5);
  Serial.print("y = ");
  Serial.println(FK(1,0), 5);
  Serial.println("Forward Kinematics ready!");

}

void loop() {

  if (Serial.available()) {
    char c = Serial.read();
      
    // Run calibration sequence
    if (c == 'c') {
      Serial.println("Calibrating motors");
      calibrate_motors(odrive);
    }

    // Set closed loop control
    if (c == 'l' ) {
      Serial.println("Loop control");
      closed_loop_control(odrive);
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
