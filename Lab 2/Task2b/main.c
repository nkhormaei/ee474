/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This file provides the implementation for using timers to blink LED1 at a rate of 1 Hz.
 * and have SW1 and SW2 buttons interrupt the program. When SW1 is pressed, the timer stops
 * counting down; instead, LED2 is turned on. When SW2 is pressed, the timer starts counting
 * down again, returning LED1 back to its blinking behavior. This step consequently turns off LED2 
 */ 
#include <stdint.h> 
#include "header.h" 

// used to control LED1's state
int counter;

int main(void)
{
  lights();
  timer_initc();
  switches();
  while (1) {};
  return 0;
}

void timer_initc() {
  RCGCTIMER |= 0xFFFF; // Enable the appropriate TIMERn bit in the RCGCTIMER register
  GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
  GPTMCFG_0 = 0x00; // Write 0x0000.0000 to the GPTMCFG register, 
  GPTMCFG_0 &= 0x00; //select 32-bit mode using the GPTMCFG register
  
  GPTMTAMR_0 &= ~0x10; // Configure the TACDIR bit of the GPTMTAMR register to count down
  GPTMTAMR_0 |= 0x2; // Puts in periodic timer mode
  GPTMTAILR_0 = 16000000;// Load the value 16,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 16 MHz oscillator
  GPTMIMR_0 = 0x1; // Configure GPTMIMR register for interrupts
  EN0 = 1 << 19u;
  GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
}

void lights() {
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0xFFFF;  // Enable Ports
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
    
    GPIODIR_N = 0x3; // setting bits for the N ports
    GPIODEN_N = 0x3; 
    counter = 0;

}

void switches() {
  GPIODIR_J = 0x00;
  GPIODEN_J = 0x3;
  GPIOPUR_J = 0x3;
  EN1 = 1 << 19u;
  GPIOIM_J |= 0x7F;
  
  GPIOIS_J &= ~0x3;  /* make bit 1, 0 edge sensitive */
  GPIOIBE_J &= ~0x3; /* trigger is controlled by IEV */
  GPIOIEV_J = ~0x3;   /* falling edge trigger */
  GPIOICR_J |= 0x3;  /* clear any prior interrupt */
  GPIOIM_J |= 0x3;   /* unmask interrupt */
}

// timer interrupt handler, turns on and off LED1 periodically
void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // clearing flag
  if (counter == 0) {
      GPIODATA_N |= 0x2; // turn on LED 1
      counter +=1;
  } else {
    GPIODATA_N &= ~0x2; // turn off LED1
    counter = 0; 
  }
}

// switch interrupt handler, implements stalling LED1 and turning on LED2 as appropriate
void Switch_Interrupt_Handler() {
  GPIOICR_J |= 0x3;  /* clear any prior interrupt */
  if (GPIODATA_J & 0x2) {
    GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
    GPIODATA_N |= 0x1; // turn on LED2
  } else {
    GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
    GPIODATA_N &= ~0x1; // turn off LED2
  }
}