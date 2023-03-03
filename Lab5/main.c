/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 2/19/23
 * This file provides the implementation for showing the distance measurement of an object
  in inches on the LCD
 */ 
#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "ADC_Header.h"
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

uint32_t ADC_value;
enum frequency freq;

char length[100];

int main(void) {
  volatile unsigned short delay = 0; 
  
  // Select system clock frequency preset
  freq = PRESET2; // 60 MHz
  LCD_Init();
  PortE_Init(); 
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  //ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  Touch_Init();
  
  float distance;
  float duration; 

  
  while(1) {  
    // need some sort of function to calculate the time difference between the trig and echo pin
    duration = Measure_distance();   
    distance = (duration * 0.034 / 2) / 2.54; // distance in inches
    
    LCD_SetCursor(0, 0);
    sprintf(length, "Distance is %.2lf inches\n", distance);
   
    LCD_Printf(length);
    
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // Clear the ADC0 interrupt flag
  ADCISC |= 0x8; // module 0, but we want SS3
  // Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3 & 0xFFF;
  GPTMICR_0 |= 0x1;
}
