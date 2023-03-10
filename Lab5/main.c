/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 2/19/23
 * This file provides the implementation for showing the distance measurement of an object
  in inches on the LCD
 */ 
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lab3_Inits.h"
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"


enum frequency freq;

char length[100];

bool notdone;

float count;

float Measure_distance(void);
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
    printf("duration %.6f\n", duration);
    printf("distance %.6f\n", distance);
    LCD_SetCursor(0, 0);
    sprintf(length, "Distance is %.6f inches\n", distance);
   
    LCD_Printf(length);
    
  }
  return 0;
}

float Measure_distance() {
  notdone = true;
  count = 0;
  GPIO_PORTE_DATA_R &= ~0x2;
  ten_ms_delay();
  GPIO_PORTE_DATA_R |= 0x2;
  ten_ms_delay();
  GPIO_PORTE_DATA_R &= ~0x2;
  while (notdone) {};
  
//  while (!(GPIO_PORTB_DATA_R & 0x4)){};
//  TIMER0_CTL_R |= 0x1;
//  int count = 0;
//  int loop = 0;
//  while ((GPIO_PORTB_DATA_R & 0x4)){
//    loop++;
//    if (TIMER0_RIS_R & 0x1) {
//      count++;
//      TIMER0_ICR_R = 0x1;
//    }
//  }
//  printf("count %d\n", count);
//  printf("loop %d\n", loop);
//  TIMER0_CTL_R  &= ~0x1;
  printf("count %.6f\n", count);
  return (count / 10.0);
}

void PortB_Handler() {
  GPIO_PORTB_ICR_R = 0x4;
  if (GPIO_PORTB_DATA_R & 0x4) {
    TIMER0_CTL_R |= 0x1;
  } else {
    notdone = false;
    TIMER0_CTL_R  &= ~0x1;
  }
}

void Timer0_Handler() {
  count++;
  TIMER0_ICR_R = 0x1;
}

void ten_ms_delay() {
    TIMER1_CTL_R |= 0x1;// Enable the timer using the GPTMCTL register
    while (!(TIMER1_RIS_R & 0x1)) {};
    TIMER1_ICR_R = 0x1;
    TIMER1_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
}