/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "ADC_Header.h"

uint32_t ADC_value;
enum frequency freq;

int main(void) {
  // Select system clock frequency preset
  freq = PRESET1; // 60 MHz
  
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  
  GPIODIR_J = 0x00;
  GPIODEN_J = 0x3;
  GPIOPUR_J = 0x3;
  
  float temp; // changed this to temp
  
  while(1) {  
    PLL_Init(freq);        // Set system clock frequency depending on switch 
    temp = (147.5 - ((75)* (3.3) * (ADC_value)) / 4096.0);
    printf("%.2f\n\n", temp); // printing out temperature value
    
    if (GPIODATA_J & 0x1) {
      freq = PRESET1;
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 12000000;
      GPTMCTL_0 |= 0x1;
    } else if (GPIODATA_J & 0x2) {
      freq = PRESET3;
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 120000000;
      GPTMCTL_0 |= 0x1;
    }
    
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8; // module 0, but we want SS3
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3 & 0xFFF;
  
  GPTMICR_0 |= 0x1;
}

/*void PortJ_Handler(void) {
  GPIOICR_J |= 0x3;
  if (GPIODATA_J == 0x1) { 
    PLL_Init(PRESET3); // 12 MHz
  } else {
    PLL_Init(PRESET1); 
  }
}*/
