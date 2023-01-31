#include <stdint.h> 
#include "lab1.h" 

/*
This part of the lab (task 1) had 2 main goals- 1) turn on the lights in a specific pattern
2) have the switches control the lights on the board
This turns on the LED1 (D1) whenever switch 1 (SW1) is pressed, and turns 
on the LED2 (D2) whenever switch 2 (SW2) is pressed
*/
int main(void) 
{ 
    
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1120;  // Enable PortF PortN Port J GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
 
        
    GPIODIR_J = 0x00;
    GPIODEN_J = 0x3;
    GPIOPUR_J = 0x3;
    
       
    
    switches();
    
    //lights(); // commented to show the switches method during demonstration
   
    
    return 0; 
} 

// function used to turn off and on the various leds on the boards dependent on the switches
void switches() {

    GPIODATA_F = 0x0;
  
    while (1) {
      uint32_t switch_one = (GPIODATA_J & 0x1); // looking at first bit for switch 1
      uint32_t switch_two = (GPIODATA_J & 0x2); // looking at second bi for switch 2
      
      if (switch_one == 0x0) {
        GPIODATA_N |= 0x2; // setting to the first led at index 1 to 1
      } else {
        GPIODATA_N &= ~0x2; // setting to the first led at index 1 to 0 (keeping everything else the same)
      } 
      if (switch_two == 0x0) {
        GPIODATA_N |= 0x1; 
      } else {
        GPIODATA_N &= ~0x1;
      }     
    }          
}

// function used to turn off and on the various leds on the boards
void lights() {
  
  GPIODIR_F = 0x11;   // Set PF0 to output 
  GPIODEN_F = 0x11;   // Set PF0 to digital port 
    
  GPIODIR_N = 0x3; // setting bits for the N ports
  GPIODEN_N = 0x3; 
  
  
  GPIODATA_F = 0x11;  // Set PF0 to 1 
    
  GPIODATA_N = 0x3;  // Set PF0 to 1
  
  while (1) { 
      GPIODATA_F = 0x00;  // Set PF0 to 0 
      GPIODATA_N = 0x00;
      for (int j = 0; j < 1000000; j++) {} // delay
      GPIODATA_F = 0x11;  // Set PF0 to 0
      GPIODATA_N = 0x3;
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_F = 0x10;  // Set PF0 to 0
      GPIODATA_N = 0x2;
      for (int j = 0; j < 1000000; j++) {}
    
    } 
}  




 
