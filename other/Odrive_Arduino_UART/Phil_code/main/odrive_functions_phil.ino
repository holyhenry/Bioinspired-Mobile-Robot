
////////////////////////////////////////////////////////////////////////////////////////////////
// Set parameters
void set_odrive_parameters(HardwareSerial &odrive_serial) {
    for (int axis = 0; axis < 2; ++axis) {
      odrive_serial << "w axis" << axis << ".controller.config.vel_limit " << 500000.0f << '\n';
      odrive_serial << "w axis" << axis << ".motor.config.current_lim " << 20.0f << '\n';
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Calibrate both motors
void calibrate_motors(ODriveArduino odrive1, ODriveArduino odrive2, ODriveArduino odrive3, ODriveArduino odrive4)  {
    int requested_state;
    requested_state = ODriveArduino::AXIS_STATE_FULL_CALIBRATION_SEQUENCE;
    odrive1.run_state(0, requested_state, false);
    odrive1.run_state(1, requested_state, false);
    odrive2.run_state(0, requested_state, false);
    odrive2.run_state(1, requested_state, false);
    odrive3.run_state(0, requested_state, false);
    odrive3.run_state(1, requested_state, false);
    odrive4.run_state(0, requested_state, false);
    odrive4.run_state(1, requested_state, false);
    delay(100);

}
////////////////////////////////////////////////////////////////////////////////////////////////
// Close Loop Control
void close_loop_control(ODriveArduino odrive1, ODriveArduino odrive2, ODriveArduino odrive3, ODriveArduino odrive4)  {
    int requested_state;
    requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
    odrive1.run_state(0, requested_state, false);
    odrive1.run_state(1, requested_state, false);
    odrive2.run_state(0, requested_state, false);
    odrive2.run_state(1, requested_state, false);
    odrive3.run_state(0, requested_state, false);
    odrive3.run_state(1, requested_state, false);
    odrive4.run_state(0, requested_state, false);
    odrive4.run_state(1, requested_state, false);

}
////////////////////////////////////////////////////////////////////////////////////////////////
// IDLE
void idle_mode(ODriveArduino odrive1, ODriveArduino odrive2, ODriveArduino odrive3, ODriveArduino odrive4)  {
    int requested_state;
    requested_state = ODriveArduino::AXIS_STATE_IDLE;
    odrive1.run_state(0, requested_state, false);
    odrive1.run_state(1, requested_state, false);
    odrive2.run_state(0, requested_state, false);
    odrive2.run_state(1, requested_state, false);
    odrive3.run_state(0, requested_state, false);
    odrive3.run_state(1, requested_state, false);
    odrive4.run_state(0, requested_state, false);
    odrive4.run_state(1, requested_state, false);

}

////////////////////////////////////////////////////////////////////////////////////////////////
// This is the basic sinusoidal motion control
void sinusoidal_move(ODriveArduino odrive1, ODriveArduino odrive2, ODriveArduino odrive3,ODriveArduino odrive4)  {
  for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
    float pos_m0 = 20000.0f * cos(ph);
    float pos_m1 = 20000.0f * sin(ph);
    odrive1.SetPosition(0, pos_m0);
    odrive1.SetPosition(1, pos_m1);
    odrive2.SetPosition(0, pos_m0);
    odrive2.SetPosition(1, pos_m1);
    odrive3.SetPosition(0, pos_m0);
    odrive3.SetPosition(1, pos_m1);
    odrive4.SetPosition(0, pos_m0);
    odrive4.SetPosition(1, pos_m1);
    delay(5);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the current motor position for the odrive and axis passed to the function
float get_position(ODriveArduino odrive, HardwareSerial &odrive_serial, int axis)  {
    odrive_serial << "r axis" << axis << ".encoder.pos_estimate\n";
    return odrive.readFloat();
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the bus volge for four Odrives
float bus_voltage(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
    odrive_serial << "r vbus_voltage\n";
    return odrive.readFloat();
}




////////////////////////////////////////////////////////////////////////////////////////////////
// Sends a move command for each axis and reads the current position in a loop as fast as 
// possible. Returns the communication (closed loop) rate
float test_odrive_communication_speed(ODriveArduino odrive, HardwareSerial &odrive_serial) {
    
    // First set both motors to idle (requested state = 1)
    odrive.run_state(0, 1, false); // don't wait
    odrive.run_state(1, 1, false); // don't wait

    static const unsigned long duration = 3000;
    String pos;
    unsigned long start = millis();
    unsigned int count = 0;
    unsigned int t_now = 0;
    
    while(millis() - start < duration) {
      
      // Set motor positions
      odrive.SetPosition(0, 0);
      odrive.SetPosition(1, 0);
      
      pos = get_position(odrive, odrive_serial, 0);
      pos = get_position(odrive, odrive_serial, 1);
  
      count++;
    }
    t_now = millis() - start;

    Serial << "Command loops:  " << count << "\tElapsed time:  " << t_now << "\tClosed loop frequency:  " << count / (t_now / 1000) << '\n';
}





////////////////////////////////////////////////////////////////////////////////////////////////
// Printing with stream operator
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }


////////////////////////////////////////////////////////////////////////////////////////////////
// Clear all errors on the ODrive
float clear_errors(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
    Serial.println("Errors");
    print_errors(odrive, odrive_serial);
    for (int motor = 0; motor < 2; ++motor) {
        odrive_serial << "w axis" << motor << ".error 0\n";
        odrive_serial << "w axis" << motor << ".motor.error 0\n";
        odrive_serial << "w axis" << motor << ".controller.error 0\n";
        odrive_serial << "w axis" << motor << ".envoder.error 0\n";
    }
    // For debugging to make sure they are cleared
//    Serial.println("");
//    Serial.println("After clearing errors");
//    print_errors(odrive, odrive_serial);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Print all errors on the ODrive
float print_errors(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
    
    for (int motor = 0; motor < 2; ++motor) {
        odrive_serial << "r axis" << motor << ".error \n";
        Serial << "axis" << motor << ".error = " << odrive.readFloat() << "\n";
        
        odrive_serial << "r axis" << motor << ".motor.error \n";
        Serial << "axis" << motor << ".motor.error = " << odrive.readFloat() << "\n";
        
        odrive_serial << "r axis" << motor << ".controller.error \n";
        Serial << "axis" << motor << ".controller.error = " << odrive.readFloat() << "\n";
              
        odrive_serial << "r axis" << motor << ".encoder.error \n";
        Serial << "axis" << motor << ".encoder.error = " << odrive.readFloat() << "\n";
    }
}
