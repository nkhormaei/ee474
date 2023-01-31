#include <stdint.h> 
#include "header.h" 

/*
This part of the lab (task 1) had 2 main goals- 1) turn on the lights in a specific pattern
depending on the timers instead of delays
*/
int counter;
// main function of the program 
int main(void)
{
  lights();
  timer_initc();
  switches();
  while (1) {};
  return 0;
}

// function used to intialize timer registers and cast certain bits
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

// function used to initialize lights on the board
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
  
  // ENSURE THESE ARE ONLY NECESSARY REGISTER CONFIGURATION FOR SWITCHES
}

void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // clearing flag
  if (counter == 0) {
      GPIODATA_N |= 0x2;
      counter +=1;
  } else {
    GPIODATA_N &= ~0x2;
    counter = 0; 
  }
}

void Switch_Interrupt_Handler() { // changed this to switch
  GPIOICR_J |= 0x3;  /* clear any prior interrupt */
  if (GPIODATA_J & 0x2) {
    GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
    GPIODATA_N |= 0x1;
  } else {
    GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
    GPIODATA_N &= ~0x1;
  }
}