/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This file provides the implementation for turning on/of the LEDs
 * sequentially with the 1Hz timer as an interrupt
 */ 
#include <stdint.h> 
#include "header.h" 

// to order to the LEDs
int counter;

int main(void)
{
  counter = 0;
  lights();
  timer_initc();
  while (1) {};
  return 0;
}

void timer_initc() {
  volatile unsigned short delay = 0; 
  delay++;           // Delay 2 more cycles before access Timer registers 
  delay++;           // Refer to Page. 756 of Datasheet for info 
  RCGCTIMER |= 0x1; // Enable the appropriate TIMERn bit in the RCGCTIMER register
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
    RCGCGPIO |= 0xFFFF;  // Enable Ports
    GPIODIR_F = 0x11;   // Set PF0 to output 
    GPIODEN_F = 0x11;   // Set PF0 to digital port 
    GPIODIR_N = 0x3; // setting bits for the N ports
    GPIODEN_N = 0x3; 
}

// interrupt method instigated by timer flag
void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // clearing flag
  if (counter == 0) { // using counter to determine which LED to turn on/off
      GPIODATA_N |= 0x1;
  } else if (counter == 1) {
      GPIODATA_N |= 0x2;
  } else if (counter == 2) {
      GPIODATA_F |= 0x1;
  } else if (counter == 3) {
      GPIODATA_F |= 0x2;
  } else if (counter == 4) {
      GPIODATA_N &= ~0x1;
  } else if (counter == 5) {
      GPIODATA_N &= ~0x2;
  } else if (counter == 6) {
      GPIODATA_F &= ~0x1;
  } else if (counter == 7) {
      GPIODATA_F &= ~0x2;
  }
  if (counter == 7) {
    counter = 0; // resetting counter
  } else {
    counter += 1; // incrementing value
  }
}