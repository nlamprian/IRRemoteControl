/**
 * This is an example that makes use of a Sparkfun Remote
 * for controlling an LED Strip based on the WS2812 LEDs
 * A IR receiver is needed for the operation of the system.
 * The code was tested on a TSOP38238.
 *
 * The buttons function as follows:
 * POWER: Turns the strip on/off
 * A: Puts a red color on the strip *
 * B: Puts a green color on the strip *
 * C: Puts a blue color on the strip *
 * UP: Increases the brightness of the LEDs
 * DOWN: Decreases the brightness of the LEDs
 * LEFT: Sets part of the rainbow colors on the strip ** /
 *       Shifts this window of colors in one direction
 * RIGHT: Sets part of the rainbow colors on the strip ** /
 *        Shifts this window of colors in the other direction
 * SELECT: Sets a random color on the strip
 *
 * * A-B-C sequences with successive button presses executed
 *   within 1 second, set the appropriate color on the strip
 *   e.g. Pressing A-B, sets a yellow on the strip
 *        Pressing A-C, sets a pink on the strip
 *        Pressing A-B-C, sets a white on the strip
 *
 * ** Rainbow colors are not preserved upon restarting (POWER-POWER) the strip
 */

#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#include <IRremote.h>
#include "IRRemoteControl.h"

#define RECV_PIN 11
#define STRIP_PIN 9
#define NUM_PIXELS 60

// Creates an Adafruit_NeoPixel instance
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, STRIP_PIN, NEO_GRB + NEO_KHZ800);

uint8_t status = 1;  // Strip state: ON/OFF
uint32_t lastColor;  // Current color on the strip
uint8_t brightness = 100;
uint16_t offset = 0;  // Used in the raindow function
long timeRef;  // Used for measuring delay in the A-B-C sequences

// Creates an IRRemoteControl instance
IRRemoteControl remote(RECV_PIN);


void setup()
{
	initStrip();

	remote.enable();  // Starts the receiver
	remote.pair(POWER, power);  // Pairs buttons to functions
	remote.pair(A, red);
	remote.pair(B, green);
	remote.pair(C, blue);
	remote.pair(UP, brightnessUp);
	remote.pair(DOWN, brightnessDown);
	remote.pair(LEFT, rainbowLeft);
	remote.pair(RIGHT, rainbowRight);
	remote.pair(SELECT, randomColor);
}

void loop()
{
	// Checks if a button is pressed
	// and executes the corresponding function
	remote.check();
	// Optional: Do your thing here. Just keep it short ;)
}


// Initializes the LED strip
void initStrip()
{
	strip.begin();
	lastColor = strip.Color(brightness, brightness, brightness);
	setColor(lastColor);
	strip.show();
}

// Turns the LED strip on and off
// When turning on, the color from the last operation appears
void power()
{
	if ( status )
	{
		setColor(strip.Color(0, 0, 0));
		status = 0;
	}
	else
	{
		setColor(lastColor);
		status = 1;
	}
}

// Sets red on the LED strip
// If called within 1 second from the last call of red/green/blue,
// it adds red to the existing color
void red()
{
	if ( status )
	{
		if ( (unsigned long)(millis() - timeRef) < 1000 )
			lastColor += strip.Color(brightness, 0, 0);
		else
			lastColor = strip.Color(brightness, 0, 0);
			
		timeRef = millis();
		setColor(lastColor);
	}
}

// Sets green on the LED strip
// If called within 1 second from the last call of red/green/blue,
// it adds green to the existing color
void green()
{
	if ( status )
	{
		if ( (unsigned long)(millis() - timeRef) < 1000 )
			lastColor += strip.Color(0, brightness, 0);
		else
			lastColor = strip.Color(0, brightness, 0);
		
		timeRef = millis();
		setColor(lastColor);
	}
}

// Sets blue on the LED strip
// If called within 1 second from the last call of red/green/blue,
// it adds blue to the existing color
void blue()
{
	if ( status )
	{
		if ( (unsigned long)(millis() - timeRef) < 1000 )
			lastColor += strip.Color(0, 0, brightness);
		else
			lastColor = strip.Color(0, 0, brightness);
		
		timeRef = millis();
		setColor(lastColor);
	}
}

// Increases brightness of the strip
void brightnessUp()
{
	if ( status )
	{
		if ( brightness > 235 ) brightness = 255;
		else brightness += 20;
		strip.setBrightness(brightness);
		strip.show();
	}
}

// Decreases brightness of the strip
void brightnessDown()
{
	if ( status )
	{
		if ( brightness < 20 ) brightness = 10;
		else brightness -= 20;
		strip.setBrightness(brightness);
		strip.show();
	}
}

// Sets/Shifts (in one direction)
// a window of rainbow colors on the strip
void rainbowLeft()
{
	offset = ( offset + 20 ) % 255;
	for (uint16_t i = 0; i < strip.numPixels(); ++i)
		strip.setPixelColor(i, Wheel((i + offset) & 255));
    strip.show();
}

// Sets/Shifts (in the other direction)
// a window of rainbow colors on the strip
void rainbowRight()
{
	offset = ( offset - 20 ) % 255;
	for (uint16_t i = 0; i < strip.numPixels(); ++i)
		strip.setPixelColor(i, Wheel((i + offset) & 255));
    strip.show();
}

// Sets a random color on the strip
void randomColor()
{
	if ( status )
	{
		lastColor = strip.Color(rand() % 256, rand() % 256, rand() % 256);
		setColor(lastColor);
	}
}

// Fills the strip with the given color
void setColor(uint32_t c)
{
	for (uint16_t i = 0; i < strip.numPixels(); ++i)
		strip.setPixelColor(i, c);
	strip.setBrightness(brightness);
	strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
	if ( WheelPos < 85 )
	{
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	else if ( WheelPos < 170 )
	{
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else
	{
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}
