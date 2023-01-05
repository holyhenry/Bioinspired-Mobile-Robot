
//////////////////////////////////////////////////////////////////////////////////Set parameters
void set_odrive_parameters(HardwareSerial &odrive_serial) {
    for (int axis = 0; axis < 2; ++axis) {

      odrive_serial << "w axis" << axis << ".controller.config.vel_limit " << 1000000.0f << '\n';
      odrive_serial << "w axis" << axis << ".motor.config.current_lim " << 11.0f << '\n';

    }
}

///////////////////////////////////////////////////////////////////////////Calibrate four motors
void calibrate_motors(ODriveArduino odrive)  {
    int requested_state;

    requested_state = ODriveArduino::AXIS_STATE_FULL_CALIBRATION_SEQUENCE;
    odrive.run_state(0, requested_state, false);
    odrive.run_state(1, requested_state, false);

}

////////////////////////////////////////////////////////////////////////////////////Loop control
void closed_loop_control(ODriveArduino odrive) {
    int requested_state;

    requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
    odrive.run_state(0, requested_state, false);
    odrive.run_state(1, requested_state, false);

}

///////////////////////////////////////////////////////////////////////////////////////Idle mode
void idle_mode(ODriveArduino odrive) {
    int requested_state;

    requested_state = ODriveArduino::AXIS_STATE_IDLE;
    odrive.run_state(0, requested_state, false);
    odrive.run_state(1, requested_state, false);

}

////////////////////////////////////////////////////////////////////////////////Read bus voltage
float bus_voltage(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
      
      odrive_serial << "r vbus_voltage\n";
      return odrive.readFloat(); 

}

/////////////////////////////////////////////////////This is the basic sinusoidal motion control
void sinusoidal_move(ODriveArduino odrive)  {
  for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
    float pos_m0 = 10000.0f * cos(ph);
    float pos_m1 = 10000.0f * sin(ph);
    odrive.SetPosition(0, pos_m0);
    odrive.SetPosition(1, pos_m1);

  }
}

////////////////Returns the current motor position for the odrive and axis passed to the function
float get_position(ODriveArduino odrive, HardwareSerial &odrive_serial, int axis)  {
    odrive_serial << "r axis" << axis << ".encoder.pos_estimate\n";
    return odrive.readFloat();
}

////////// Sends a move command for each axis and reads the current position in a loop as fast as 
////////////////////////////////////////// possible. Returns the communication (closed loop) rate
float test_odrive_communication_speed(ODriveArduino odrive, HardwareSerial &odrive_serial) {
    
    // First set both motors to idle
    int requested_state;
    requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
    odrive.run_state(0, requested_state, false); // don't wait
    odrive.run_state(1, requested_state, false); // don't wait

    static const unsigned long duration = 3000;
    String pos;
    unsigned long start = millis();
    unsigned int count = 0;
    unsigned int t_now = 0;
    
    while(millis() - start < duration) {
      
      // Set motor positions
      odrive.SetPosition(0, 5000);
      odrive.SetPosition(1, 5000);

      pos = get_position(odrive, odrive_serial, 0);
      pos = get_position(odrive, odrive_serial, 1);

      count++;
    }
    t_now = millis() - start;

    Serial << "Command loops:  " << count << "\tElapsed time:  " << t_now 
           << "\tClosed loop frequency:  " << count / (t_now / 1000) << '\n';

}


////////////////////////////////////////////////////////////////////////Printing with stream operator
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }


///////////////////////////////////////////////////////////////////////Clear all errors on the ODrive
float clear_errors(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
    Serial.println("Errors");
    print_errors(odrive, odrive_serial);
    for (int motor = 0; motor < 2; ++motor) {
        odrive_serial << "w axis" << motor << ".error 0\n";
        odrive_serial << "w axis" << motor << ".motor.error 0\n";
        odrive_serial << "w axis" << motor << ".controller.error 0\n";
        odrive_serial << "w axis" << motor << ".encoder.error 0\n";
    }
    // For debugging to make sure they are cleared
//    Serial.println("");
//    Serial.println("After clearing errors");
//    print_errors(odrive, odrive_serial);
}

///////////////////////////////////////////////////////////////////////Print all errors on the ODrive
float print_errors(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
    
    for (int motor = 0; motor < 2; ++motor) {
        Serial << "Axis " << motor << "********************" << "\n";
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

//////////////////////////////////////////////////////////////////////////////////Virtual compliance
float virtual_compliance(ODriveArduino odrive, HardwareSerial &odrive_serial)  {
//      int requested_state;
//      requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
//      odrive.run_state(0, requested_state, false);
//      odrive.run_state(1, requested_state, false);

      for (int axis = 0; axis < 2; ++axis) {

      odrive_serial << "w axis" << axis << ".controller.config.vel_limit " << 1000000.0f << '\n';
      odrive_serial << "w axis" << axis << ".motor.config.current_lim " << 11.0f << '\n';

    }

}
