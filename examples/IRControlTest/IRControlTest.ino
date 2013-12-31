/**
 * This is an example for checking the proper operation
 * of the Sparkfun Remote
 * A IR receiver is needed for the operation of the system.
 * The code was tested on a TSOP38238.
 */

#include <IRremote.h>
#include "IRRemoteControl.h"

#define RECV_PIN 11

// Creates an IRRemoteControl instance
IRRemoteControl remote(RECV_PIN);

void setup()
{
	remote.enable();  // Starts the receiver
	remote.pair(POWER, power);  // Pairs buttons to functions
	remote.pair(A, a);
	remote.pair(B, b);
	remote.pair(C, c);
	remote.pair(UP, up);
	remote.pair(DOWN, down);
	remote.pair(LEFT, left);
	remote.pair(RIGHT, right);
	remote.pair(SELECT, select);
	
	Serial.begin(9600);  // Initializes serial port
	// Waits for serial port to connect. Needed for Leonardo only
	while ( !Serial ) ;
}

void loop()
{
	remote.check();
}

void power() { Serial.println("POWER"); }
void a() { Serial.println("A"); }
void b() { Serial.println("B"); }
void c() { Serial.println("C"); }
void up() { Serial.println("UP"); }
void down() { Serial.println("DOWN"); }
void left() { Serial.println("LEFT"); }
void right() { Serial.println("RIGHT"); }
void select() { Serial.println("SELECT"); }
