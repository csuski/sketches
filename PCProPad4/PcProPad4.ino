/*	PCProPad4.ino
*
*	This sketch send the commands from a PCProPad4 wired up to an Arduino
*	to the connected computer.
*
*	The PCProPad4 has 4 buttons that can be wired up to 4 digital I/O pins.
*	It has an X/Y game pad that is wired up to 2 analog pins.
*	All four buttons can also be setup in a semi-auto or automatic setting,
*	however, in order to take advantage of these they must be setup with
*	interrupts.
*
*	The Arduino Uno only has two interrupts so for this system only two buttons
*	can be set to perform interupts. This isn't too bad because there are only 
*	three mouse buttons which can be emulated anyways. 
*
*	Created by Christopher Suski
*	Created on June 5th, 2015
*	Last Modified June 5th, 2015
*
*
*	This is free and unencumbered software released into the public domain.
*/

// DEFINE THE DIRECTIONS FOR THE JOYSTICK
#define UP 0x1
#define DOWN 0x2
#define LEFT 0x4
#define RIGHT 0x8

// The digital pins each button is wired to
const int ButtonAPin = 0;
const int ButtonBPin = 3;
const int ButtonCPin = 2;
const int ButtonDPin = 5;

// The analog pins each button is wired to
const int JoystickXPin = A0;
const int JoystickYPin = A1;

// Set the interrupt to use for each button, -1 will disable the interrupt
// and instead it will be detected in the loop
const int ButtonAInterrupt = -1;
const int ButtonBInterrupt = 1;
const int ButtonCInterrupt = 0;
const int ButtonDInterrupt = -1;

// Wire up which buttons go to which mouse click
const int LeftMouseClick = ButtonAPin;
const int RightMouseClick = ButtonBPin;
const int MiddleMouseClick = ButtonCPin;

// Verbose output
//		if false only log what the mouse is doing / would do
//		if true log everything coming off the inputs
const bool Verbose = true;

// These values define when the values off the analog pins that represent the
// direction pad being pressed one way or the other
const int AnalogHigh = 900;
const int AnalogLow = 550;

// The speed to move the mouse
const int MouseMoveSpeed = 10;

void setup()
{
	Serial.begin(9600);
	pinMode(ButtonAPin, INPUT);
	pinMode(ButtonBPin, INPUT);
	pinMode(ButtonCPin, INPUT);
	pinMode(ButtonDPin, INPUT);

	if (ButtonAInterrupt >= 0) 
	{
		attachInterrupt(ButtonAInterrupt, A_Button_Pressed, LOW);
		if (Verbose) Serial.println("A Button using interrupt.");
	}
	if (ButtonBInterrupt >= 0)
	{
		attachInterrupt(ButtonBInterrupt, B_Button_Pressed, LOW);
		if (Verbose) Serial.println("B Button using interrupt.");
	}
	if (ButtonCInterrupt >= 0)
	{
		attachInterrupt(ButtonCInterrupt, C_Button_Pressed, LOW);
		if (Verbose) Serial.println("C Button using interrupt.");
	}
	if (ButtonDInterrupt >= 0)
	{
		attachInterrupt(ButtonDInterrupt, D_Button_Pressed, LOW);
		if (Verbose) Serial.println("D Button using interrupt.");
	}
}

void loop()
{
	ReadButtonPresses();
	int directions = GetMovementDirections();
	MoveMouse(directions);
	
	delay(1000);
}

void ReadButtonPresses()
{
	//bool aPressed = !digitalRead(ButtonAPin);
	//bool bPressed = !digitalRead(ButtonBPin);
	//bool cPressed = !digitalRead(ButtonCPin);
	//bool dPressed = !digitalRead(ButtonDPin);

	//Serial.println(aPressed);
	//Serial.println(bPressed);
	//Serial.println(cPressed);
	//Serial.println(dPressed);

	// Debounce?

	// Get the buttons that are not set for interrupts
	if (ButtonAInterrupt < 0 && !digitalRead(ButtonAPin))
		A_Button_Pressed();
	if (ButtonBInterrupt < 0 && !digitalRead(ButtonBPin))
		B_Button_Pressed();
	if (ButtonCInterrupt < 0 && !digitalRead(ButtonCPin))
		C_Button_Pressed();
	if (ButtonDInterrupt < 0 && !digitalRead(ButtonDPin))
		D_Button_Pressed();
}



void A_Button_Pressed() 
{
	if (Verbose) Serial.println("A Button Pressed");
	ClickMouse(ButtonAPin);
}

void B_Button_Pressed() 
{
	if (Verbose) Serial.println("B Button Pressed");
	ClickMouse(ButtonBPin);
}

void C_Button_Pressed() 
{
	if (Verbose) Serial.println("C Button Pressed");
	ClickMouse(ButtonCPin);
}

void D_Button_Pressed() 
{
	if (Verbose) Serial.println("D Button Pressed");
	ClickMouse(ButtonDPin);
}


int GetMovementDirections() 
{
	int direction = 0;
	int xValue = analogRead(JoystickXPin);
	int yValue = analogRead(JoystickYPin);
	//if (Verbose)
	//{
	//	Serial.print("X Value = ");
	//	Serial.println(xValue);
	//}
	//if (Verbose)
	//{
	//	Serial.print("Y Value = ");
	//	Serial.println(yValue);
	//}

	if (xValue < AnalogLow) 
		direction |= RIGHT;
	else if (xValue > AnalogHigh)
		direction |= LEFT;
	if (yValue < AnalogLow)
		direction |= DOWN;
	else if (yValue > AnalogHigh)
		direction |= UP;
	return direction;
}

void MoveMouse(int directions) 
{
	int xMove = 0, yMove = 0;
	if ((directions & LEFT) == LEFT)
		xMove = -1 * MouseMoveSpeed;
	if ((directions & RIGHT) == RIGHT)
		xMove = MouseMoveSpeed;
	if ((directions & DOWN) == DOWN)
		yMove = -1 * MouseMoveSpeed;
	if ((directions & UP) == UP)
		yMove = MouseMoveSpeed;

	if (xMove != 0 || yMove != 0)
	{
		Serial.print("Move Mouse X = ");
		Serial.print(xMove);
		Serial.print(", Y = ");
		Serial.println(yMove);
		//Mouse.move(xMove, yMove, 0);
	}
}


void ClickMouse(int buttonPin) 
{
	if (LeftMouseClick == buttonPin) 
	{
		//Mouse.click(MOUSE_LEFT);
		Serial.println("Left Mouse Click");
	}
	if (MiddleMouseClick == buttonPin)
	{
		//Mouse.click(MOUSE_MIDDLE);
		Serial.println("Middle Mouse Click");
	}
	if (RightMouseClick == buttonPin)
	{
		//Mouse.click(MOUSE_RIGHT);
		Serial.println("Right Mouse Click");
	}
}