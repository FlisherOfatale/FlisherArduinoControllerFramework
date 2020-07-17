#pragma once

// Do not Edit after this line
#define IO_PhysicalButtons_Count  sizeof(IO_PhysicalButtons) / sizeof(IO_PhysicalButtons[0])  // 
#define IO_ShiftRegisterBits_Count  sizeof(IO_ShiftRegisterBits) / sizeof(IO_ShiftRegisterBits[0])  // 

// Activate Shift In Library
ShiftIn<ShiftRegisterChipCount> shift;

// Activate Joystick Library from https://github.com/MHeironimus/ArduinoJoystickLibrary

Joystick_ Joystick(
  hidReportId, 
  JOYSTICK_TYPE_JOYSTICK,    
  virtualButtonsCount, 
  hatSwitchCount,            
  includeXAxis,
  includeYAxis,
  includeZAxis,              
  includeRxAxis,
  includeRyAxis,
  includeRzAxis,
  includeRudder,
  includeThrottle,
  includeAccelerator,
  includeBrake,
  includeSteering
);
