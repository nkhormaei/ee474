#include <stdint.h> 
#include "header.h" 

// initializing states for traffic light 
enum TL_States { TL_init, TL_stop, TL_warn, TL_go } TL_State;
int counter;
// main function of the program 
int main(void)
{
  timer_initc();
  buttons();
  led_init();
  TL_State = TL_init;
  counter = 0;
  while (1) {
// Traffic_Light_System();
  }
  return 0;
}



void timer_initc() {
  volatile unsigned short delay = 0;
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  RCGCTIMER |= 0x1; // Enable the appropriate TIMERn bit in the RCGCTIMER register
  GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
  GPTMCFG_0 = 0x00; // Write 0x0000.0000 to the GPTMCFG register, 
  GPTMCFG_0 &= 0x00; //select 32-bit mode using the GPTMCFG register
  
  GPTMTAMR_0 &= ~0x10; // Configure the TACDIR bit of the GPTMTAMR register to count down
  GPTMTAMR_0 |= 0x2; // Puts in periodic timer mode
  GPTMTAILR_0 = 16000000;// Load the value 16,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 16 MHz oscillator
  GPTMIMR_0 = 0x1; // Configure GPTMIMR register for interrupts
  EN0 |= (1 << 19u);
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
  GPIOIEV_E = ~0x3;   /* falling edge trigger */
  GPIOICR_E |= 0x3;  /* clear any prior interrupt */
  GPIOIM_E |= 0x3;   /* unmask interrupt */
  // ENSURE THESE ARE ONLY NECESSARY REGISTER CONFIGURATION FOR SWITCHES
}

// initializing leds
void led_init() {
  RCGCGPIO  |= 0xFFFF;
  GPIOAMSEL_E &= ~0x1F;          // disable analog function of PE0/1/2/3/4
  GPIOAFSEL_E &= ~0x1F;          // set PE/1/2/3/4 regular port function 
  GPIODIR_E |= 0x1C;             // set PE2/3/4 to output 
  GPIODIR_E &= ~0x3;             // set PE0/1 to input
  GPIODEN_E |= 0x1F;             // enable digital output on PE0/1/2/3/4
}

void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // clearing flag
  if (counter == 0) {
      Red_on();
      Yellow_on();
      Green_on();
      counter +=1;
  } else {
    Red_off();
    Yellow_off();
    Green_off();
    counter = 0; 
  }
}

void Button_Interrupt_Handler() { // changed this to switch
  GPIOICR_E |= 0x3;  /* clear any prior interrupt */
  if (GPIODATA_E & 0x1) {
    GPTMCTL_0 &= ~0x1; // Disable the timer using the GPTMCTL register
  } else {
    GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
  }
}


// initializing red led on
void Red_on(void) 
{ 
    GPIODATA_E |= 0x4; 
} 

// initializing red led off
void Red_off(void) 
{ 
    GPIODATA_E &= ~0x4; 
} 

// initializing yellow led on
void Yellow_on(void) 
{ 
    GPIODATA_E |= 0x8; 
    
} 

// initializing yellow led off
void Yellow_off(void) 
{ 
    GPIODATA_E &= ~0x8; 
} 

// initializing green led on
void Green_on(void) 
{ 
    GPIODATA_E |= 0x10; 
} 

// initializing green led off
void Green_off(void) 
{ 
    GPIODATA_E &= ~0x10; 
} 

// function is checking if button is pressed and setting count
//bool system_button_pressed() {
//  int count = 0;
//  while (GPIODATA_E & 0x1) {
//    if (GPTMRIS_0 & 0x1) {
//        GPTMICR_0 |= 0x1;
//        count +=1;
//    }
//    if (count == 2) {
//        return true;
//    }
//  }
//  return false;
//}

int five_seconds() {
  int count = 0;
  int sys = 0;
  int ped = 0;
  while (count < 5) {
    while (GPIODATA_E & 0x1) {
      if (GPTMRIS_0 & 0x1) {
        GPTMICR_0 |= 0x1;
        count +=1;
        sys +=1;
      }
      if (sys == 2) {
        return 1;
      }
    }
    while (GPIODATA_E & 0x2) {
      if (GPTMRIS_0 & 0x1) {
        GPTMICR_0 |= 0x1;
        count +=1;
        ped +=1;
      }
      if (ped == 2) {
        return 2;
      }
    }
    if (GPTMRIS_0 & 0x1) {
        GPTMICR_0 |= 0x1;
        count +=1;
    }
  }
  return 0; 
}

// function for traffic light system state machine
void Traffic_Light_System()
{
  switch(TL_State) {   // State Transitions
     case TL_init: 
      //  bool flag = system_button_pressed();
     //   if (flag) {
          TL_State = TL_stop;
       // }
       break;
     case TL_go:
        int result_go = five_seconds();
        if (result_go == 1) {
           TL_State = TL_init;
        }
        else if (result_go == 2) {
           TL_State = TL_warn;
        } else {
          TL_State = TL_stop;
        }
        break;
     case TL_warn:
        int result_warn = five_seconds();
        if (result_warn == 1) {
          TL_State = TL_init;
        }
        else {
          TL_State = TL_stop;
        }
        break;
     case TL_stop:
       int result_stop = five_seconds();
        if (result_stop == 1) {
           TL_State = TL_init;
        }
        else {
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