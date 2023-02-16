#include <stdint.h> 
#include <stdio.h>
#include "header.h" 
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
  while (!(UART0FR & 0x40)) {}; // wait til recieve FIFO full
//  char temp[32] = UART0DR;
  char value;
  for (int i = 0; i < 32; i++) {
    //UART0DR = temp[i]; // write back to UART0DR
    while ((UART0FR & 0x8)) {}; // wait til bit has been written
    value = (char)(UART0DR & 0xFF);
    //while ((UART0FR & 0x8)) {}; // wait til bit has been written
    printf("%c\n", value);
    
    // this is what I think we will send over back using bluetooth
    UART0DR = value;
    
  
  }
}