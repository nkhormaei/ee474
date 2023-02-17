/**
 * EE/CSE 474: Lab3 drivers starter code
 */
#include "Lab3_Inits.h"
#include "header.h"
#include <stdint.h> 

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0; 
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC |= 0x1;
 
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= 0x10;
  
  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x8;
  
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= (~0x8);
  
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0x8;
  
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS &= (~0x8);
  
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX |= 0x5000;
  
  // 2.17: Enable ADC0 SS3
  ADCACTSS |= 0x8;

}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
  
  // from last lab, initializing timer
  volatile unsigned short delay = 0; 
  delay++;           // Delay 2 more cycles before access Timer registers 
  delay++;           // Refer to Page. 756 of Datasheet for info 
  RCGCTIMER |= 0x1; // Enable the appropriate TIMERn bit in the RCGCTIMER register
  GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
  
  GPTMCFG_0 = 0x00; // Write 0x0000.0000 to the GPTMCFG register, 
  GPTMCFG_0 &= 0x00; //select 32-bit mode using the GPTMCFG register
  
  GPTMTAMR_0 &= ~0x10; // Configure the TACDIR bit of the GPTMTAMR register to count down
  GPTMTAMR_0 |= 0x2; // Puts in periodic timer mode
  
  GPTMTAILR_0 = 60000000;// Load the value 60,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 16 MHz oscillator
  GPTMIMR_0 = 0x1; // Configure GPTMIMR register for interrupts
  
  // from this lab
  GPTMADCEV |= 0x1;
  GPTMCTL_0 |= 0x20;
    
  GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
  
}

void UART_Init(void) {
  volatile unsigned short delay = 0;
  RCGCUART = 0x4; // enable clock for UART module 0 and 2
  delay++; // delay 3 cycles
  delay++;
  delay++;
  
  RCGCGPIO |= 0x1; // enable port A
  delay++; // delay
  delay++;
  // for PA 6, PA 7
  GPIOAFSEL_A |= 0xC0; // set A6 A7 for alternative hardware function  1100 0011
  GPIOPCTL_A |= 0x11000000; // programming pmcn field to assign UART signal to GPIO A6, A7
  GPIODEN_A |= 0xC0; // digital for port A's 6 and 7
  GPIODR2R_A |= 0xC0;
  
  UART2CTL = 0x0; // disable for setting registers
  UART2IBRD |= 0x68; // integer baud-rate divisor (104)
  UART2FBRD |= 0xB; // fractional baud-rate divisor (11)
  UART2LCRH |= 0x60; // set word length to 8 bit and FIFO
  UART2CC = 0x5; // set clock to ALTCLKCFG
  UART2CTL |= 0x300; // enable UART transmit and recieve and RTS
  UART2CTL |= 0x1; // enable UART
} 
//  NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
