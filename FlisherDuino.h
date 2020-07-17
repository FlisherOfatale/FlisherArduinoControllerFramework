#pragma once

void init_pins()
{
  // Initialize Button Pins
  for (int i = 0; i < IO_PhysicalButtons_Count; i++) {
    pinMode(IO_PhysicalButtons[i].pin, INPUT_PULLUP);
  }
}

void init_axis() {
  for (int i = 0; i < IO_Axis_Count; i++) {
    if (IO_Axis[i].type == AXIS_X) {
      Joystick.setXAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_Y) {
      Joystick.setYAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_Z) {
      Joystick.setZAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_RX) {
      Joystick.setRxAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_RY) {
      Joystick.setRyAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_RZ) {
      Joystick.setRzAxisRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_RUDDER) {
      Joystick.setRudderRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_THROTTLE) {
      Joystick.setThrottleRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_ACCELERATOR) {
      Joystick.setAcceleratorRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_BRAKE) {
      Joystick.setBrakeRange(IO_Axis[i].min, IO_Axis[i].max);
    }
    if (IO_Axis[i].type == AXIS_STEERING) {
      Joystick.setSteeringRange(IO_Axis[i].min, IO_Axis[i].max);
    }

    // Calculate DeadZone Values
    if (IO_Axis[i].max > IO_Axis[i].min) {
      IO_Axis[i].deadzone_value = (IO_Axis[i].max - IO_Axis[i].min)/2;
    }
    else {
      IO_Axis[i].deadzone_value = (IO_Axis[i].min - IO_Axis[i].max)/2;
    }
    
    IO_Axis[i].deadzone_min = IO_Axis[i].deadzone_value - IO_Axis[i].deadzone_limit;
    IO_Axis[i].deadzone_max = IO_Axis[i].deadzone_value + IO_Axis[i].deadzone_limit;
  }
}

void init_drivers() {
  Keyboard.begin();
  Joystick.begin();

  if (ShiftRegisterChipCount > 0) {
    // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
    // shift.begin(8, 9, 11, 12); // Leonardo
    shift.begin(2, 9, 14, 15); // Pro Micro
    //shift.begin(2, false, 14, 15); // Pro Micro   //Leonardo
  }
}

void init_actions() {
  for (int i = 0; i < IO_PhysicalButtons_Count; i++) {
    IO_PhysicalButtons[i].lastState =  -1;
  }

  for (int i = 0; i < IO_PhysicalButtons_Count; i++) {
    IO_ShiftRegisterBits[i].lastState =  -1;
  }
}

void debug(String text)
{
  #if DEBUG_MODE 
    Serial.println(text);
  #endif
}

char getKey(String normal, char special) {
  char key = normal.charAt(0);
  if (special != 0) key = special;  
  return key;
}

int Generate_Action(struct Button CurrentButton, int currentButtonState ) {
  // Action if it's a button
  int returnActionState;
  int calculatedState = currentButtonState;
  if (CurrentButton.unpressedState == true) {
    calculatedState = !currentButtonState;
  }

  if (CurrentButton.type == "button") {
      int button = String(CurrentButton.action.normal).toInt() -1;
      Joystick.setButton(button, calculatedState);
      returnActionState = calculatedState;
  }
  
  if (CurrentButton.type == "buttonToggle") {
      int button = String(CurrentButton.action.normal).toInt() -1;    
      if (calculatedState == 1) {
        calculatedState = !CurrentButton.lastActionState;       
        Joystick.setButton(button, calculatedState);
        returnActionState = calculatedState;
      }
      else {
        returnActionState = CurrentButton.lastActionState;
      }
  }

  if (CurrentButton.type == "keyPulse") {
      if (calculatedState) {
        Keyboard.print(getKey(CurrentButton.action.normal,CurrentButton.action.special));
        returnActionState = calculatedState;
      }
  }

  if (CurrentButton.type == "keyHold") {
    if (calculatedState) {
      Keyboard.press(getKey(CurrentButton.action.normal,CurrentButton.action.special));
      returnActionState = calculatedState;
    }
    else {
      Keyboard.release(getKey(CurrentButton.action.normal,CurrentButton.action.special));
      returnActionState = calculatedState;
    }
  }

  if (CurrentButton.type == "keyToggle") {
    if (calculatedState) {
      calculatedState = !CurrentButton.lastActionState;       
      if (calculatedState) {
        Keyboard.press(getKey(CurrentButton.action.normal,CurrentButton.action.special));
      }
      else {
        Keyboard.release(getKey(CurrentButton.action.normal,CurrentButton.action.special));
      }
      returnActionState = calculatedState;      
    }
    else {
      returnActionState = CurrentButton.lastActionState;
    }
  }
  
  // TODO : Merge POC code for key pulse, key press, 
  // TODO : Merge POC code for button toggle
  return returnActionState;
}
void check_buttons() {
  debug("==============================");
  debug("Loop : Start");
  int currentButtonState;
  
  // Code for Physical
  for (int i = 0; i < IO_PhysicalButtons_Count; i++) {
    // Generic Code to get current State
    currentButtonState = !digitalRead(IO_PhysicalButtons[i].pin);
  
    // Validate if the state of the button changed
    if (currentButtonState != IO_PhysicalButtons[i].lastState) {      
      IO_PhysicalButtons[i].lastActionState = Generate_Action( IO_PhysicalButtons[i], currentButtonState );  
      IO_PhysicalButtons[i].lastState = currentButtonState;
        Serial.print("lastActionState: ");
        Serial.print(IO_PhysicalButtons[i].lastActionState);
        Serial.println();
    }
  }
  
  // Code for Shift Register
  debug("Shift Register: BLOCK START");
  if (ShiftRegisterChipCount > 0) {
    debug("Shift Register: Active");
    if(shift.update()) { // read in all values. returns true if any button has changed
      debug("Shift Register: Bits Updated");
      for (int i = 0; i < IO_ShiftRegisterBits_Count; i++) {
        currentButtonState = shift.state(IO_ShiftRegisterBits[i].pin - 1);
        // Validate if the state of the button changed
        if (currentButtonState != IO_ShiftRegisterBits[i].lastState) {
          IO_ShiftRegisterBits[i].lastActionState = Generate_Action( IO_ShiftRegisterBits[i], currentButtonState );  
          IO_ShiftRegisterBits[i].lastState = currentButtonState;
        }
      }
    }
    debug("Shift Register: BLOCK END");
  }

}

void check_axis() {
  for (int i = 0; i < IO_Axis_Count; i++) {
    int value = analogRead(IO_Axis[i].pin);    
    if (value >= IO_Axis[i].deadzone_min && value <= IO_Axis[i].deadzone_max) {
      value = IO_Axis[i].deadzone_value;
    }      
    if (IO_Axis[i].type == AXIS_X) {
      Joystick.setXAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_Y) {
      Joystick.setYAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_Z) {
      Joystick.setZAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_RX) {
      Joystick.setRxAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_RY) {
      Joystick.setRyAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_RZ) {
      Joystick.setRzAxis(value);    
    }
    if (IO_Axis[i].type == AXIS_RUDDER) {
      Joystick.setRudder(value);    
    }
    if (IO_Axis[i].type == AXIS_THROTTLE) {
      Joystick.setThrottle(value);    
    }  
    if (IO_Axis[i].type == AXIS_ACCELERATOR) {
      Joystick.setAccelerator(value);    
    }
    if (IO_Axis[i].type == AXIS_BRAKE) {
      Joystick.setBrake(value);    
    }
    if (IO_Axis[i].type == AXIS_STEERING) {
      Joystick.setSteering(value);    
    }
  }
}
