# FlisherArduinoControllers

Arduino Sketch file for my custom controllers intially built for Star Citizen.
The intent is to make a versatile code with a simple config that other people can reuse easily.

I'm uploading this version so my friends car look at the code, v1.0 should be release by end of June 2020 with a more complete feature set.

Version 0.6

Required Library: 
	Joystick.h: https://github.com/MHeironimus/ArduinoJoystickLibrary, Allow your Pro Micro or Leonardo to become a PC Joystick
	Keyboard.h: Built-in Arduino IDE, Allow the use of keyboard action
	ShiftIn.h: Allow use of Shift Register 74HC165, https://github.com/InfectedBytes/ArduinoShiftIn

Current Feature:
	Input:
		Regular Button by pin status
		Shift Register by bits status
		
	Actions:
		Button: Press and Toggle
		Key: Normal(Hold), Pulse, Toggle (not recommended)
	

TODO: Input
  configurable Axis
  logic operand for on/off/on state, etc...


Nice To Have: IO
  Add Button Matrix IO
  Add dynamic loading of Keyboard and ShiftIn based on mapping
  button pulse
