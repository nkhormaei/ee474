/**
 * EE/CSE 474: Lab3 drivers header file for PLL
as well as method declarations for initialzing timer and GPIO for 
ultrasound purposes
 */

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes Timer 0 as an input
void Timer_Init(void);

// Initialize pin E1(output) and B2 (input)
void Port_Init(void);

#endif  // _Lab3_Inits_H_
