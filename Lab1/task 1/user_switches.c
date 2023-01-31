#include <stdint.h> 
#include "lab1.h" 
 
void switches() {
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1120;  // Enable PortF and PortN GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 

    GPIODIR_N = 0x3;
    GPIODEN_N = 0x3; 
    GPIODATA_N = 0x00;
    
    GPIODIR_J = 0x00;
    GPIODEN_J = 0x3;
    GPIOLOCK_J = 0x4C4F434B;
    GPIOCR_J = 0xFF;
    
    while (1){
      
    }
}

int user_switches(void) {
  switches();
  return 0;
}