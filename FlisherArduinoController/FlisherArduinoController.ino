// Version 1.2, based on Flisher Mining Controller MK3, version improved for Adamist

#include <ShiftIn.h>  // https://github.com/InfectedBytes/ArduinoShiftIn
#include <Joystick.h> // Joystick Library from https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Keyboard.h> // The main library for sending keystrokes.

#include "Struct.h" //
#include "Configuration.h"  // Configuration File
#include "Initialize.h"  // Load library according to configuration
#include "FlisherDuino.h"   // Flisher Library

void setup() {
  // Initialize Keyboard
  init_pins();
  init_axis();
  init_drivers();
  init_actions();
}

// Last state of the button

void loop() {
  check_buttons();
  check_axis();
  if (! DEBUG_MODE) delay(LOOP_DELAY);
  else delay(LOOP_DELAY_DEBUG);
}

// TODO: Add SHIFT REGISTER PIN CONFIGURATION
// TODO: FIX Action for special char
