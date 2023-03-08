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
    printf("duration %.2lf\n", duration);
    printf("distance %.2lf\n", distance);
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
  while (!(GPIO_PORTB_DATA_R & 0x4)){};
  TIMER0_CTL_R |= 0x1;
  int count = 0;
  while (GPIO_PORTB_DATA_R & 0x4){
    if (TIMER0_RIS_R & 0x1) {
      count++;
      TIMER0_ICR_R = 0x1;
    }
  }
  printf("count %d", count);
  TIMER1_CTL_R  &= ~0x1;
  return (count * 1000000);
}

void ten_ms_delay() {
    TIMER1_CTL_R |= 0x1;// Enable the timer using the GPTMCTL register
    while (!(TIMER1_RIS_R & 0x1)) {};
    TIMER1_ICR_R = 0x1;
    TIMER1_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
}