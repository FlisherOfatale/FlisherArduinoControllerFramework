bool getAxisStatus(int key) {
  bool match = false;  
  for (int i = 0; i < IO_Axis_Count; i++) {
    if (IO_Axis[i].type == key) {
      match = true;
    }
  }
  return match;
};

struct AxisList {
  int type;
  bool enabled;
};

AxisList AXIS_LIST[] {
  { AXIS_X, getAxisStatus(AXIS_X) },
  { AXIS_Y, getAxisStatus(AXIS_Y) },
  { AXIS_Z, getAxisStatus(AXIS_Z) },
  { AXIS_RX, getAxisStatus(AXIS_RX) },
  { AXIS_RY, getAxisStatus(AXIS_RY) },
  { AXIS_RZ, getAxisStatus(AXIS_RZ) }, 
  { AXIS_RUDDER, getAxisStatus(AXIS_RUDDER) },
  { AXIS_THROTTLE, getAxisStatus(AXIS_THROTTLE) },
  { AXIS_ACCELERATOR, getAxisStatus(AXIS_ACCELERATOR) },
  { AXIS_BRAKE, getAxisStatus(AXIS_BRAKE) },
  { AXIS_STEERING, getAxisStatus(AXIS_STEERING) },
};


const uint8_t hatSwitchCount  = 0; //Not Implemented yet   //  Indicates how many hat switches will be available on the joystick. Range: 0 - 2
const bool includeXAxis       = AXIS_LIST[AXIS_X].enabled; 
const bool includeYAxis       = AXIS_LIST[AXIS_Y].enabled;
const bool includeZAxis       = AXIS_LIST[AXIS_Z].enabled;
const bool includeRxAxis      = AXIS_LIST[AXIS_RX].enabled;
const bool includeRyAxis      = AXIS_LIST[AXIS_RY].enabled;
const bool includeRzAxis      = AXIS_LIST[AXIS_RZ].enabled;
const bool includeRudder      = AXIS_LIST[AXIS_RUDDER].enabled;
const bool includeThrottle    = AXIS_LIST[AXIS_THROTTLE].enabled;
const bool includeAccelerator = AXIS_LIST[AXIS_ACCELERATOR].enabled;
const bool includeBrake       = AXIS_LIST[AXIS_BRAKE].enabled;
const bool includeSteering    = AXIS_LIST[AXIS_STEERING].enabled;
