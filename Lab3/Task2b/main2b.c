/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 2/16/23
 * This file provides the implementation for receives a single character
 via UART and immediately transmits back the character that it receives 
 */ 
#include <stdint.h> 
#include <stdio.h>
#include "header2b.h" 
#include "Lab3_Inits.h"

int main()
{
  // Select system clock frequency preset
  enum frequency freq = PRESET1; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART_Init();           // Initializes UART registers
  while(1) {  
    recieveSend();
  }
  return 0;
}

void recieveSend() {
  while ((UART2FR & (1 << 4)) != 0) {}; // checking Rx
  char value = UART2DR;
  UART2DR = value;
  while (!(UART2FR & 0x80)) {}; // checking Tx 
}