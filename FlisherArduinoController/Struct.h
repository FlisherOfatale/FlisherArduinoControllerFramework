#pragma once

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_RX 3
#define AXIS_RY 4
#define AXIS_RZ 5
#define AXIS_RUDDER 6
#define AXIS_THROTTLE 7
#define AXIS_ACCELERATOR 8
#define AXIS_BRAKE 9
#define AXIS_STEERING 10

struct Action {
  String normal;
  char special;
};

struct Button {
  int pin;
  String type;          // button, buttonToggle, keyHold, keyPulse | Implemented but not recommended: keyToggle
  Action action;        
  int unpressedState;   // Default to 0 (for Push Close), Set to 1 for Push Open
  int duration;         // time in miliseconds
  int lastState;        // Last State of pin/bits
  int lastActionState;  // Last State of action, usefull for Toggle Mode.
};



struct Axis {
  int pin;
  int type;
  int min;
  int max;
  int sensitivity; 
  int deadzone_limit;
  int deadzone_value;
  int deadzone_min;
  int deadzone_max;
  int lastValue;
  int sensitivity_max_value;
};
