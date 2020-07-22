#include <ODriveArduino.h>
#include <Eigen30.h>
using Eigen::MatrixXd;

///// Connect to four Odrives
HardwareSerial &leg1_serial = Serial1;
HardwareSerial &leg2_serial = Serial2;
HardwareSerial &leg3_serial = Serial3;
HardwareSerial &leg4_serial = Serial4;

ODriveArduino odrive_1(leg1_serial);
ODriveArduino odrive_2(leg2_serial);
ODriveArduino odrive_3(leg3_serial);
ODriveArduino odrive_4(leg4_serial);

void setup() {
  // Odrive serial connection using 115200 baud
  leg1_serial.begin(115200);
  leg2_serial.begin(115200);
  leg3_serial.begin(115200);
  leg4_serial.begin(115200);

  // Serial to PC
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor to open

  Serial.println("ODriveTeensy");
  
  Serial.println("Setting parameters...");
  set_odrive_parameters(leg1_serial);
  set_odrive_parameters(leg2_serial);
  set_odrive_parameters(leg3_serial);
  set_odrive_parameters(leg4_serial);
  
  Serial.println("Ready!\n");
  Serial.println(" 'c' to calibrate all motors ");
  Serial.println("'k' to close loop control mode");
  Serial.println("'i' to idle mode");
  Serial.println(" 's' to exectue test move");
  Serial.println("'b' to read bus voltage");
  Serial.println("'p' to read motor positions in a 10s loop");
  Serial.println("'e' to read motor errors and clear them");
  Serial.println("'t' to test the odrive communication speed");

}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    // Read bus voltage from both ODrives
    if (c == 'b'){    
      Serial << "Serial1 voltage: " << bus_voltage(odrive_1,leg1_serial) << '\n' ;
      Serial << "Serial1 voltage: " << bus_voltage(odrive_2,leg2_serial) << '\n' ;
      Serial << "Serial1 voltage: " << bus_voltage(odrive_3,leg3_serial) << '\n' ;
      Serial << "Serial1 voltage: " << bus_voltage(odrive_4,leg4_serial) << '\n' ;
      
       
    }

    // Run calibration sequence
    if (c == 'c'){
      Serial.println("Calibrating motors");
      calibrate_motors(odrive_1, odrive_2, odrive_3, odrive_4);
      delay(500); 
      
    }
    
    // Close loop control mode
    if (c == 'k'){
      Serial.println("Close loop control mode");
      close_loop_control(odrive_1, odrive_2, odrive_3, odrive_4);
      delay(500); 
      
    }
    
    // IDLE mode
    if (c == 'i'){
      Serial.println("Idle mode");
      idle_mode(odrive_1, odrive_2, odrive_3, odrive_4);
      delay(500); 
      
    }
   
    // Sinusoidal test move
    if (c == 's') {
      Serial.println("Executing test move");
      sinusoidal_move(odrive_1,odrive_2,odrive_3,odrive_4);
    }

    
    // Read and clear errors
    if (c == 'e') {
      Serial.println("odriv1_error ******************************");
      clear_errors(odrive_1, leg1_serial);
      Serial.println("odriv2_error ******************************");
      clear_errors(odrive_2, leg2_serial);
      Serial.println("odriv3_error ******************************");
      clear_errors(odrive_3, leg3_serial);
      Serial.println("odriv4_error ******************************");
      clear_errors(odrive_4, leg4_serial);
    }

    // Speed testing
    if (c == 't'){
      test_odrive_communication_speed(odrive_1,leg1_serial);
      test_odrive_communication_speed(odrive_2,leg2_serial);
      test_odrive_communication_speed(odrive_3,leg3_serial);
      test_odrive_communication_speed(odrive_4,leg4_serial);

    }

   
  }
}





    
  
