GLOBAL VARIABLES:

Lab 5:

#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include <string.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define CLOCK_COUNT 15625
#define CHECK_COUNT 3125

volatile char button = 0;
volatile char prev = 0;

Lab 6:

#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include <math.h>

Lab 7:

#include <avr/io.h>
#include "util.h"
#include "lcd.h"
#include "open_interface.h"
#include "math.h"
#include <avr/interrupt.h>

volatile unsigned redge = 0;
volatile unsigned fedge = 0;
volatile enum {LOW,HIGH,DONE} state;
	volatile int numOvf = 0;

Lab 8:

#include <avr/io.h>
#include "lcd.h"
#include "open_interface.h"
#include "util.h"

unsigned pulse_width;

#define TOP 43000
//#define TOP 43000