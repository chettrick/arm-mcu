/* Abstract services for controlling LED's */

// $Id$

// LED masks (not all are implemented)

#define LED1	0x01
#define LED2	0x02
#define LED3	0x04
#define LED4	0x08
#define LED5	0x10
#define LED6	0x20
#define LED7	0x40
#define LED8	0x80

// Initialize the LED's (to the off state)

void LEDS_initialize(void);

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void);

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask);
