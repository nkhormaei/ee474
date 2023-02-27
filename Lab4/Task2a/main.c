/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This file implements the traffic light system with the use of timers, such that: 
 Each time a button is pressed, the system responds if and only if the user holds the 
button for at least two seconds.
Upon reset, all LEDs are turned off. When the On/Off button is pressed, 
the system will be turned on and start in the stop state. After a delay of 5 seconds, 
the system will move to the go state. After another 5 seconds, the system will return 
to the stop state. Until a button is pressed, this should repeat indefinitely. 
If the On/Off button is pressed again, the system will be turned 
off, which means that all LEDs will be turned off. 
After the Pedestrian button is pressed and held by the user for 2 seconds while the 
system is in the go state, the system  immediately transitions to the warn state, 
and remain there for 5 seconds before moving to the stop state. 
 */ 
#include <stdint.h>
#include <stdbool.h>
#include "header.h" 
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "Lab3_Inits.h"

// initializing states for traffic light 
enum TL_States { TL_init, TL_stop, TL_warn, TL_go } TL_State;
enum frequency freq;

int main(void)
{
  freq = PRESET1; // 60 MHz
  PLL_Init(freq);
  LCD_init_traffic_light();
  Touch_Init();
  TL_State = TL_init;
  while (1) {
    unsigned long x = Touch_ReadX();
    unsigned long y = Touch_ReadY();
    LCD_SetCursor(0, 100);
    LCD_PrintInteger(x);
    LCD_SetCursor(0, 125);
    LCD_PrintInteger(y);
    Traffic_Light_System();
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
  GPTMCTL_0 |= 0x1;// Enable the timer using the GPTMCTL register
}

void LCD_init_traffic_light() {
  LCD_Init();
  LCD_ColorFill(Color4[5]);
  LCD_DrawCircle(100, 50, 35, Color4[0]);
  LCD_DrawCircle(100, 125, 35, Color4[0]);
  LCD_DrawCircle(100, 200, 35, Color4[0]);
  LCD_DrawFilledRect(200, 25, 75, 75, Color4[3]);
  LCD_DrawFilledRect(200, 125, 75, 75, Color4[3]);
  LCD_SetCursor(225, 50);
  LCD_PrintString("SW1");
  LCD_SetCursor(225, 150);
  LCD_PrintString("SW2");
}

void Red_on(void) 
{ 
    LCD_DrawFilledCircle(100, 50, 35, Color4[4]);
} 

void Red_off(void) 
{ 
    LCD_DrawFilledCircle(100, 50, 35, Color4[0]);
} 

void Yellow_on(void) 
{ 
    LCD_DrawFilledCircle(100, 125, 35, Color4[14]);
} 

void Yellow_off(void) 
{ 
    LCD_DrawFilledCircle(100, 125, 35, Color4[0]); 
} 

void Green_on(void) 
{ 
    LCD_DrawFilledCircle(100, 200, 35, Color4[2]);
} 

void Green_off(void) 
{ 
    LCD_DrawFilledCircle(100, 200, 35, Color4[0]);
} 

bool sw1_pressed() {
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  if ((x < 2900) && (x > 2500) && (y > 2000) && (y < 2700)) {
    return true;
  }
  return false;
}

bool sw2_pressed() {
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  if ((x < 2900) && (x > 2500) && (y > 1000) && (y < 1900)) {
    return true;
  }
  return false;
}

bool system_button_pressed() {
  int count = 0;
  while (sw1_pressed()) {
    if (GPTMRIS_0 & 0x1) {
        GPTMICR_0 |= 0x1;
        count +=1;
    }
    if (count == 2) {
        return true;
    }
  }
  return false;
}

int five_seconds() {
  int count = 0;
  int sys = 0;
  int ped = 0;
  while (count < 5) {
    while (sw1_pressed()) {
      if (GPTMRIS_0 & 0x1) {
        GPTMICR_0 |= 0x1;
        count +=1;
        sys +=1;
      }
      if (sys == 2) {
        return 1;
      }
    }
    while (sw2_pressed()) {
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

void Traffic_Light_System()
{
  switch(TL_State) {   // State Transitions
     case TL_init: 
        bool flag = system_button_pressed();
        if (flag) { // system button is pressed
          TL_State = TL_stop;
        }
       break;
     case TL_go:
        int result_go = five_seconds();
        if (result_go == 1) { // system button is pressed
           TL_State = TL_init;
        }
        else if (result_go == 2) { // pedestrian button is pressed
           TL_State = TL_warn;
        } else {
          TL_State = TL_stop;
        }
        break;
     case TL_warn:
        int result_warn = five_seconds();
        if (result_warn == 1) { // system button is pressed
          TL_State = TL_init;
        }
        else {
          TL_State = TL_stop;
        }
        break;
     case TL_stop:
       int result_stop = five_seconds();
        if (result_stop == 1) { // system button is pressed
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