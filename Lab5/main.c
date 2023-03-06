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
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"


enum frequency freq;

char length[100];

uint32_t Measure_distance(void);
void ten_ms_delay(void);

int main(void) {
  volatile unsigned short delay = 0; 
  
  // Select system clock frequency preset
  freq = PRESET2; // 60 MHz
  LCD_Init();
  LCD_ColorFill(Color4[5]);
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  Timer_Init(); // Initialize Timer0A to trigger ADC0
  PortE_Init(); 

  
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

uint32_t Measure_distance() {
  GPIO_PORTE_DATA_R &= ~0x1;
  ten_ms_delay();
  GPIO_PORTE_DATA_R |= 0x1;
  ten_ms_delay();
  GPIO_PORTE_DATA_R &= ~0x1;
  int start, end;
  while (1) {
  //TIMER0_ICR_R = 0x4;
    while ((TIMER0_RIS_R & 0x4) == 0);
    if (GPIO_PORTE_DATA_R & 0x2) {
      end = TIMER0_TAR_R;
      TIMER0_ICR_R = 0x4;
      while ((TIMER0_RIS_R & 0x4) == 0);
      start = TIMER0_TAR_R;
      return (start-end);
    }
  }
}

void ten_ms_delay() {
    TIMER1_CTL_R |= 0x1;// Enable the timer using the GPTMCTL register
    int i = 10;
    while (i > 0) {
      if (TIMER1_RIS_R & 0x1) {
        TIMER1_ICR_R |= 0x1;
        i--;
      }
    }
    TIMER1_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
}