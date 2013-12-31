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
 * Dependecies: You'll need to download and install the IRremote library
 * 				https://github.com/shirriff/Arduino-IRremote
 * 				Thank you Ken Shirriff!
 * License: Copyright (c) 2013 Nick Lamprianidis 
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: IRRemoteControl.cpp
 * File description: Implementation of methods for the IRRemoteControl library
 */

#include "IRRemoteControl.h"

// Creates an instance and initializes instance variables
IRRemoteControl::IRRemoteControl(uint8_t recvPin) : buttonAddress(address)
{
	for (uint8_t i = 0; i < 9; ++i) funcPointer[i] = NULL;
	
	irrecv = new IRrecv(recvPin);
}

// Starts the receiver
void IRRemoteControl::enable()
{
	irrecv->enableIRIn();
}

// Pairs buttons with functions
// Each time a button is pressed, its paired function will be called
void IRRemoteControl::pair(button b, func f)
{
	funcPointer[b] = f;
}

// Checks if a command has been received
// and executes the appropriate functions
void IRRemoteControl::check()
{
	if ( irrecv->decode(&results) ) 
	{
		for (uint8_t b = 0; b < numButtons; ++b)
		{
			if ( results.value == buttonAddress[b] )
			{
				if ( funcPointer[b] ) funcPointer[b]();
				break;
			}
		}
    	irrecv->resume();
	}
}
