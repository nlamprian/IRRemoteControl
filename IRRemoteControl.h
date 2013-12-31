/**
 * Name: IRRemoteControl
 * Author: Nick Lamprianidis (paign10.ln@gmail.com)
 * Version: 1.0
 * Description: This is a wrapper on the IRremote library that enables
 *              a more natural way of setting up the IR Remote Control
 *              from Sparkfun and developing applications with it.
 *              The code can be easily adjusted to support other remote
 *              controllers. You just need to update the "button",
 * 				"numButtons" and "address" variables.
 * Dependecies: You'll need to download the IRremote library
 * 				https://github.com/shirriff/Arduino-IRremote
 * 				Thank you Ken Shirriff!
 * License: Copyright (c) 2013 Nick Lamprianidis 
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: IRRemoteControl.h
 * File description: Definitions and methods for the IRRemoteControl library
 */

#ifndef IRRemoteControl_h
#define IRRemoteControl_h

#include <Arduino.h>
#include <IRremote.h>

// List of the remote's buttons
enum button
{
	POWER,
	A,
	B,
	C,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SELECT
};

const uint8_t numButtons = 9;  // # of buttons on the remote

// Commands for the buttons, in the order they appear in the enumeration "button"
const uint32_t address[] = { 0x10EFD827, 0x10EFF807, 0x10EF7887,
							 0x10EF58A7, 0x10EFA05F, 0x10EF00FF,
							 0x10EF10EF, 0x10EF807F, 0x10EF20DF };

// Signature of the functions that will be paired with buttons
typedef void (*func)();

// Class for setting up a remote and controlling responses to remote triggers
class IRRemoteControl
{
public:
    IRRemoteControl(uint8_t recvPin);
    void enable();
    void pair(button b, func f);
    void check();

private:
	const uint32_t *buttonAddress;
	func funcPointer[numButtons];
	IRrecv *irrecv;
	decode_results results;
};

#endif  // IRRemoteControl
