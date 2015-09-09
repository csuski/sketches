/*	GamePort.ino
 *	
 *	Test code that dumps out all the possible analog and digital signals for a
 *	Game Port connection to the serial output. This will allow you to check and
 *	ensure it is wired up correctly and investigate the the output.
 *
 *	The Game Port is a 15 pin connection. To wire it up completely examine the
 *  diagram at github.com/csuski/sketches/gameport.  Not all connections may need
 *  to be wired up or even exist.
 *
 *	Created by Christopher Suski
 *	Created on June 5th, 2015
 *	Last Modified June 5th, 2015
 *
 *
 *
 *	This is free and unencumbered software released into the public domain.
 */

// The digital pins each button is wired to
const int Button1Pin = 2;
const int Button2Pin = 3;
const int Button3Pin = 4;
const int Button4Pin = 5;

// The analog pins each button is wired to
const int Joystick1XPin = A0;
const int Joystick1YPin = A1;
const int Joystick2XPin = A2;
const int Joystick2YPin = A3;

// How long to wait to report to state
const long DelayTimeMS = 500;

// Max size of the status string
const int BufferSize = 131;

void setup()
{
	Serial.begin(38400);
	pinMode(Button1Pin, INPUT);
	pinMode(Button2Pin, INPUT);
	pinMode(Button3Pin, INPUT);
	pinMode(Button4Pin, INPUT);
}

void loop()
{
	char statusString[BufferSize];
	
	snprintf(statusString, BufferSize,
		"Button 1: %1d, Button 2: %1d, Button 3: %1d, Button 4: %1d, \
		Joystick 1 X: %04d, Joystick 1 Y: %04d, Joystick 2 X: %04d, Joystick 2 Y: %04d",
		digitalRead(Button1Pin), digitalRead(Button2Pin), digitalRead(Button3Pin),
		digitalRead(Button4Pin), analogRead(Joystick1XPin), analogRead(Joystick1YPin),
		analogRead(Joystick2XPin), analogRead(Joystick2YPin));

	Serial.println(statusString);


	delay(DelayTimeMS);
}
