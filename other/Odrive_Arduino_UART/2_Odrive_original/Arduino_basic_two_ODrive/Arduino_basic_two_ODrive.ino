#include <ODriveArduino.h>

#include <stlport.h>
#include <Eigen30.h>

using Eigen::MatrixXd;

/////////////////////////// Leg kinematics definitions
//MatrixXd jacobian(2, 2);
static float K_T = 0.0285;                 // Nm / A
static int peak_amp = 30;                // A
static float peak_torque = K_T * peak_amp; // Nm

static float l1 = 0.09;                    // m 
static float l2 = 0.16;                    // m
static float w = 0.07;                     // m

/////////////////////////// Connect to two Odrives
// Odrive object attached to Serial2
HardwareSerial &odrive_1_serial = Serial1;
HardwareSerial &odrive_2_serial = Serial2;

ODriveArduino odrive_1(odrive_1_serial);
ODriveArduino odrive_2(odrive_2_serial);


void setup() {
  // ODrive uses 115200 baud
  odrive_2_serial.begin(115200);

  // Serial to PC
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor to open

  Serial.println("ODriveArduino");
  Serial.println("Setting parameters...");

  // Set motor paramaters
  set_odrive_parameters(odrive_1_serial);
  set_odrive_parameters(odrive_2_serial);
    
  Serial.println("Ready!");
  Serial.println("Testing the leg Jacobian");
  test_jacobian(l1, l2, w);
  
  Serial.println("Testing closed loop communication speed for 3s");
  test_odrive_communication_speed(odrive_1, odrive_1_serial);
  Serial.println("");
  Serial.println("");
  
  Serial.println("Send the character 'c' to calibrate all motors ");
  Serial.println("Send the character 's' to exectue test move");
  Serial.println("Send the character 'b' to read bus voltage");
  Serial.println("Send the character 'p' to read motor positions in a 10s loop");
  Serial.println("Send the character 'e' to read motor errors and clear them");
}

void loop() {

  if (Serial.available()) {
    char c = Serial.read();

    // Run calibration sequence
    if (c == 'c') {
      Serial.println("Calibrating motors");
      calibrate_motors(odrive_1, odrive_2);
    }

    // Sinusoidal test move
    if (c == 's') {
      Serial.println("Executing test move");
      sinusoidal_move(odrive_1);
    }

    // Read and clear errors
    if (c == 'e') {
      clear_errors(odrive_1, odrive_1_serial);
    }

    // Read bus voltage from both ODrives
    if (c == 'b') {
      odrive_1_serial << "r vbus_voltage\n";
      Serial << "Vbus voltage: " << odrive_1.readFloat() << '\n';
    }

    // print motor positions in a 10s loop
    if (c == 'p') {
      static const unsigned long duration = 1000;
      String pos;
      unsigned long start = millis();
      unsigned int count = 0;
      unsigned int t_now = 0;
      
      while(millis() - start < duration) {
        Serial << count << '\t' << t_now << '\t';
        for (int motor = 0; motor < 2; ++motor) {
            pos = get_position(odrive_1, odrive_1_serial, motor);
            Serial << pos << '\t';
        }
        count++;
        t_now = millis() - start;
        Serial << '\n';
      }
    }
    
  }
}
