/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 2/19/23
 * This file provides the implementation for showing the distance measurement
 of an object in inches on the LCD using an ultrasound sensor. 
Process: Sets output pin high for 10ms, then uses an interrupt on the
input pin to enable a timer of 1ms which increments a count for as long
as the echo pin is high. Then uses this duration to compute the distance
the object is from the sensor.
 */ 
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lab3_Inits.h"
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

enum frequency freq; // device clock frequency
char length[100]; // lcd string
bool notdone; // process flag
float count; // microsecond count

float Measure_duration(void); // returns microsecond count of echo signal
void ten_us_delay(void); // provides 10 ms delay

int main(void) {
  // Select system clock frequency preset
  freq = PRESET2; // 60 MHz
  LCD_Init();
  LCD_ColorFill(Color4[5]); // fill screen
  PLL_Init(freq);  // Set system clock frequency to 60 MHz
  Timer_Init();
  Port_Init(); 
  
  float distance;
  float duration; 

  while(1) {  
    duration = Measure_duration();   
    distance = (duration * 0.034 / 2) / 2.54; // distance in inches
    printf("duration %.6f\n", duration);
    printf("distance %.6f\n", distance);
    LCD_SetCursor(0, 0);
    sprintf(length, "Distance is %.6f inches\n", distance);
    LCD_Printf(length); // print distance to lcd
  }
  return 0;
}

float Measure_duration() {
  notdone = true;
  count = 0;
  GPIO_PORTE_DATA_R &= ~0x2;
  ten_us_delay();
  GPIO_PORTE_DATA_R |= 0x2; // set input pin high for 10 us
  ten_us_delay();
  GPIO_PORTE_DATA_R &= ~0x2;
  while (notdone) {}; // hold until echo signal is complete
  printf("count %.6f\n", count);
  return count;
}

void PortB_Handler() {
  GPIO_PORTB_ICR_R = 0x4; // clear port b interrupt
  if (GPIO_PORTB_DATA_R & 0x4) { // if echo high
    TIMER0_CTL_R |= 0x1; // enable timer 
  } else { // echo low
    notdone = false; // echo complete
    TIMER0_CTL_R  &= ~0x1; // disable timer
  }
}

void Timer0_Handler() {
  count++; // increment count of 1 ms
  TIMER0_ICR_R = 0x1; // clear timer interrupt
}

void ten_us_delay() {
    TIMER1_CTL_R |= 0x1;// Enable the timer using the GPTMCTL register
    while (!(TIMER1_RIS_R & 0x1)) {}; // wait for interrupt flag
    TIMER1_ICR_R = 0x1; // clear the interrupt flag
    TIMER1_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
}