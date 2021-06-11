#include "Struct.h"

//#define enableKeyboard true
//#define enableJoystick true

#define virtualButtonsCount 13 // Number of Virtual Buttons seen by the computer (0-32)
#define ShiftRegisterChipCount 0  //  Number of daisy chained 74HC165 Shift Register Chips

const uint8_t hidReportId = 0x03;   //  Indicates the joystick's HID report ID. This value must be unique if you are creating multiple instances of Joystick. Do not use 0x01 or 0x02 as they are used by the built-in Arduino Keyboard and Mouse libraries.
const uint8_t buttonCount = 13;                           //  Number of Button seen by the computer (0-32)

bool AltMode = 0;

Button IO_PhysicalButtons[] = {
  // Mandatory fields:  pin, "actionType",  "action",
  // Optional fields:   unpressedState: false / true (default: false)
  // Optional fields:   duration: in milliseconds
  // Optional fields:   unpressedState false / true (default: false)

  { 0,    "button",       {"1"}   },
  { 1,    "button",       {"2"}   },
  { 2,    "button",       {"3"}   },
  { 3,    "button",       {"4"}   },
  { 4,    "button",       {"5"}   },
  { 5,    "button",       {"6"}   },
  { 6,    "button",       {"7"}   },
  { 7,    "button",       {"8"}   },
  { 8,    "button",       {"9"}   },
  { 9,    "button",       {"10"}  },
  { 14,   "button",       {"11"}  },
  { 16,   "button",       {"12"}  },
  { 15,   "alt",       {""}  },
};

Button IO_PhysicalButtonsAlt[] = {
  // Mandatory fields:  pin, "actionType",  "action",
  // Optional fields:   unpressedState: false / true (default: false)
  // Optional fields:   duration: in milliseconds
  // Optional fields:   unpressedState false / true (default: false)

  { 0,    "button",       {"1"}  },
  { 1,    "button",       {"2"}  },
  { 2,    "button",       {"3"}  },
  { 3,    "button",       {"4"}  },
  { 4,    "button",       {"5"}  },
  { 5,    "keyPulse",     {"m"}  },
  { 6,    "keyPulse",     {"" , KEY_TAB}  },
  { 7,    "keyPulse",     {"c"}  },
  { 8,    "button",       {"9"}  },
  { 9,    "keyHold",      {"x"}  },
  { 14,   "button",       {"11"} },
  { 16,   "button",       {"12"} },
  { 15,   "alt",       {""}  },
};

Button IO_ShiftRegisterBits[] {
  /*

    { 1,    "button",   "21"  },
    { 8,    "button",   "28"  },
    { 2,    "button",   "22"  },
    { 3,    "button",   "23"  },
    { 4,    "button",   "24"  },
    { 5,    "button",   "25
    { 6,    "button",   "26"  },"  },
    { 7,    "button",   "27"  },
    { 8,    "button",   "28" a }
  */
};

Axis IO_Axis[] = {
//  Pin,  Axis,           Min,  Max,  Sensitivity,  Deadzone,
  { A3,   AXIS_X,         1023, 0,    0,            30},
  { A2,   AXIS_Y,         0,    1023, 0,            30},
  { A10,  AXIS_Z,         1023, 0,    4},
  { A1,   AXIS_RX,        1023, 0,    0,            30},
  { A0,   AXIS_RY,        0,    1023, 0,            30},
  { A10,  AXIS_RZ,        0,    0,    0},
};



#define IO_PhysicalButtons_Count  sizeof(IO_PhysicalButtons) / sizeof(IO_PhysicalButtons[0])  // 
#define IO_ShiftRegisterBits_Count  sizeof(IO_ShiftRegisterBits) / sizeof(IO_ShiftRegisterBits[0])  // 
#define IO_Axis_Count  sizeof(IO_Axis) / sizeof(IO_Axis[0])  // 

#define DEBUG_MODE false
#define LOOP_DELAY 10
#define LOOP_DELAY_DEBUG 100

#include "ConfigurationHelper.h"
