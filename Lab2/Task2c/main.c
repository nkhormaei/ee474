/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This file implements the traffic light system using interrupts on the buttons
 * and 1Hz timer. 
 */ 
#include <stdint.h> 
#include <stdbool.h> 
#include "header.h" 

// initializing states for traffic light 
enum TL_States { TL_init, TL_stop, TL_warn, TL_go } TL_State;

// keeps track of how long system button is held
int sysCounter;

// keeps track of how long pedestrian button is held
int pedCounter;

// keeps track of 5 second timer
int fiveCounter;

// indicates whether button pressed corresponds to system or pedestrian
bool sysOrPed;

// indicates whether button is being pressed or released
bool active;

int main(void)
{
  timer_initc();
  buttons();
  led_init();
  TL_State = TL_init;
  sysCounter = 0;
  pedCounter = 0;
  fiveCounter = 0;
  while (1) {
    Traffic_Light_System();
  }
  return 0;
}

void timer_initc() {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1; // Enable the appropriate TIMERn bit in the RCGCTIMER register
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
  GPTMCFG_0 = 0x0; // Write 0x0000.0000 to the GPTMCFG register, 
  GPTMCFG_0 &= 0x0; //select 32-bit mode using the GPTMCFG register
  
  //GPTMTAMR_0 &= ~0x02; // Configure the TACDIR bit of the GPTMTAMR register to count down
  GPTMTAMR_0 |= 0x2; // Puts in periodic timer mode
  GPTMTAILR_0 = 0xF42400;// Load the value 16,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 16 MHz oscillator
  
  EN0 = (1<<19u);
  GPTMIMR_0 = 0x1; // Configure GPTMIMR register for interrupts
  GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
}

void buttons() {
  GPIODIR_E = 0x00;
  GPIODEN_E = 0x3;
  GPIOPUR_E = 0x3;
  EN0 |= (1 << 4u);
  GPIOIM_E |= 0x7F;
  
  GPIOIS_E &= ~0x3;  /* make bit 1, 0 edge sensitive */
  GPIOIBE_E &= ~0x3; /* trigger is controlled by IEV */
  //GPIOIEV_E = ~0x3;   /* falling edge trigger */
  GPIOICR_E |= 0x3;  /* clear any prior interrupt */
  GPIOIM_E |= 0x3;   /* unmask interrupt */
  // ENSURE THESE ARE ONLY NECESSARY REGISTER CONFIGURATION FOR SWITCHES
}

void led_init() {
  volatile unsigned short delay = 0;
  RCGCGPIO  |= 0xFFFF;
  delay++;
  delay++;
  GPIOAMSEL_E &= ~0x1F;          // disable analog function of PE0/1/2/3/4
  GPIOAFSEL_E &= ~0x1F;          // set PE/1/2/3/4 regular port function 
  GPIODIR_E |= 0x1C;             // set PE2/3/4 to output 
  GPIODIR_E &= ~0x3;             // set PE0/1 to input
  GPIODEN_E |= 0x1F;             // enable digital output on PE0/1/2/3/4
}

void Red_on(void) 
{ 
    GPIODATA_E |= 0x4; 
} 

void Red_off(void) 
{ 
    GPIODATA_E &= ~0x4; 
} 

void Yellow_on(void) 
{ 
    GPIODATA_E |= 0x8; 
    
} 

void Yellow_off(void) 
{ 
    GPIODATA_E &= ~0x8; 
} 

void Green_on(void) 
{ 
    GPIODATA_E |= 0x10; 
} 

void Green_off(void) 
{ 
    GPIODATA_E &= ~0x10; 
}

// timer interrupt method used to control counters for FSM
void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // clearing flag
  fiveCounter += 1;
  if (active) {
    if (sysOrPed) {
      sysCounter += 1;
    } else {
      pedCounter +=1;
    }
  }
}

// button interrupt method used to set flags for timer interrupt
void Button_Interrupt_Handler() {
  GPIOICR_E |= 0x3;  // clear any prior interrupt
  if (active) {
    active = false;
    sysCounter = 0;
    pedCounter = 0;
  } else {
    active = true;
    if (GPIODATA_E & 0x1) { // checking if system button pressed
      sysOrPed = true;
    } else {
      sysOrPed = false;
    }
  }
}

void Traffic_Light_System()
{
  switch(TL_State) {   // State Transitions
     case TL_init: 
        if (sysCounter == 2) { // system button pressed
          sysCounter == 0;
          TL_State = TL_stop;
        }
        fiveCounter = 0;
       break;
     case TL_go:
        if (sysCounter == 2) { // system button pressed
           sysCounter = 0;
           TL_State = TL_init;
        }
        else if (pedCounter == 2) { // pedestrian button pressed
           pedCounter = 0;
           fiveCounter = 0;
           TL_State = TL_warn;
        } else if (fiveCounter == 5) { // five seconds passed
          fiveCounter = 0;
          TL_State = TL_stop;
        }
        break;
     case TL_warn:
        if (sysCounter == 2) { // system button pressed
          sysCounter = 0;
          TL_State = TL_init;
        }
        else if (fiveCounter == 5) { // five seconds passed
          fiveCounter = 0;
          TL_State = TL_stop;
        }
        break;
     case TL_stop:
        if (sysCounter == 2) { // system button pressed
           sysCounter = 0;
           TL_State = TL_init;
        }
        else if (fiveCounter == 5) { // five seconds passed
          fiveCounter = 0;
          TL_State = TL_go;
        }
        break;
     default:
        TL_State = TL_init;
        break;
  } // State Transitions

  switch(TL_State) {   // State actions
     case TL_go:
        Red_off();
        Yellow_off();
        Green_on();
        break;

     case TL_warn:
        Green_off();
        Red_off();
        Yellow_on();
        break;
     
     case TL_stop:
        Green_off();
        Yellow_off();
        Red_on();
        break;
     default:
        Red_off();
        Yellow_off();
        Green_off();
        break;
   } // State actions
}