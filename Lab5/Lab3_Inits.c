/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"
#include "tm4c1294ncpdt.h"

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "ADC_Header.h"

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

void Timer_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
  
  // from last lab, initializing timer
  volatile unsigned short delay = 0; 
  delay++;           // Delay 2 more cycles before access Timer registers 
  delay++;           // Refer to Page. 756 of Datasheet for info 
  SYSCTL_RCGCTIMER_R |= 0x3; // Enable the appropriate TIMERn bit in the RCGCTIMER register
  TIMER1_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
  TIMER1_CFG_R &= 0x00; //select 32-bit mode using the GPTMCFG register
  TIMER1_TAMR_R &= ~0x10; // Configure the TACDIR bit of the GPTMTAMR register to count down
  TIMER1_TAMR_R |= 0x1; // Puts in one shot timer mode
  TIMER1_TAILR_R = 60;// Load the value 60 into the GPTMTAILR to achieve a 10ms blink rate using the 60 MHz oscillator
  

  TIMER0_CTL_R  &= ~0x1; // Disable the timer using the GPTMCTL register
  TIMER0_CFG_R = 0x0; //select 16-bit mode using the GPTMCFG register
  TIMER0_TAMR_R |= 0x12; // Configure the TACDIR bit of the GPTMTAMR register to count up and periodic mode
  TIMER0_TAILR_R = 6; // Load the value 60,000,000 into the GPTMTAILR to achieve a 1s blink rate using the 60 MHz 
  
  NVIC_EN0_R = (1<<19u);
  TIMER0_IMR_R = 0x1; // Configure GPTMIMR register for interrupts

}

void PortE_Init(void) {
  volatile unsigned short delay = 0; 
  // GPIO E port 0 and 1 setup
  SYSCTL_RCGCGPIO_R |= 0x12; // Enable Port B and E GPIO
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info

  // PB2 is echo pin (input) and PE 1 is trigger pin (output)

  GPIO_PORTE_DIR_R  |= 0x2;             // set PE1 to output 
  GPIO_PORTE_DEN_R |= 0x2;  // enable digital output on PE1
  GPIO_PORTE_AFSEL_R &= ~0x2;          
  GPIO_PORTE_PCTL_R &= ~0xF0;

  GPIO_PORTB_DIR_R  &= ~0x4;             // set PB2 to input
  GPIO_PORTB_DEN_R |= 0x4;  // enable digital output on PB 2
  GPIO_PORTB_AFSEL_R |= 0x4;          
  GPIO_PORTB_PCTL_R |= 0x300;

  GPIO_PORTB_IM_R &= ~0x4;
  GPIO_PORTB_ICR_R = 0x4;
  GPIO_PORTB_IS_R &= ~0x4;
  GPIO_PORTB_IBE_R |= 0x4;
  GPIO_PORTB_RIS_R &= ~0x4;
  GPIO_PORTB_IM_R |= 0x4;
  NVIC_EN0_R |= (1 << 1);
}
// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
