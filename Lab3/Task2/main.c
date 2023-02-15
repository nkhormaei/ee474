#include <stdint.h> 
#include <stdio.h>
#include "header.h" 
#include "Lab3_Inits.h"


uint32_t ADC_value;
uint32_t UART0_value;

int main()
{
  // Select system clock frequency preset
  enum frequency freq = PRESET1; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART_Init();           // Initializes UART registers
  float temp; // changed this to temp
  
  GPIODIR_J = 0x00;
  GPIODEN_J = 0x3;
  GPIOPUR_J = 0x3;
  
  
  while(1) {  
    PLL_Init(freq);        // Set system clock frequency depending on switch 
    temp = (147.5 - ((75)* (3.3) * (ADC_value)) / 4096.0);
    //sendTemp(temp);
    if (GPIODATA_J & 0x1) {
      freq = PRESET1;
      //GPTMCTL_0 &= ~(0x1);
      //GPTMTAILR_0 = 12000000;
      //GPTMCTL_0 |= 0x1;
    } else if (GPIODATA_J & 0x2) {
      freq = PRESET3;
      //GPTMCTL_0 &= ~(0x1);
      //GPTMTAILR_0 = 120000000;
      //GPTMCTL_0 |= 0x1;
    }
    sendTemp(temp);
  }
  return 0;
}

void sendTemp (float temp) {
  // create char array
  // loop through bits
  // check if uart is busy
  // if uart is busy then wait
  // if uart is not busy then send 
  char str[32];
  sprintf(str, "Temperature is %.2f\r\n", temp);
  for (int i = 0; i < 32; i++) {
    while ((UART0FR & 0x8)) {};
    UART0DR = str[i];
  }
  

}
void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8; // module 0, but we want SS3
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3 & 0xFFF;
  
  GPTMICR_0 |= 0x1;
}

//void UART0_Handler(void) {
  //UART0CTL = 0x0; // disable
  //while (!(UART0FR & 0x8)) {};// wait til transmission complete
  //UART0_value = UART0DR & 0xFF; // read data
  //UART0LCRH &= ~0x10; //  Flush the transmit FIFO by clearing bit 4 (FEN) in the line control register (UARTLCRH)
  //UART0LCRH |= 0x10; // Reprogram the control register
  //UART0CTL = 0x1; // Enable the UART
  
//}