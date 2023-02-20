#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "ADC_Header.h"
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

uint32_t ADC_value;
enum frequency freq;

int main(void) {
  LCD_Init();
  Touch_Init();
  // Select system clock frequency preset
  freq = PRESET1; // 60 MHz
  
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  
  float ctemp;
  float ftemp;
  
  while(1) {  
    LCD_ColorFill(Color4[5]);
    LCD_DrawFilledCircle(50, 100, 10, Color4[3]);
    LCD_SetCursor(48, 100);
    LCD_PrintString("SW1");
    LCD_DrawFilledCircle(150, 100, 10, Color4[3]);
    LCD_SetCursor(148, 100);
    LCD_PrintString("SW2");
    unsigned long x_crd = Touch_ReadX();
    unsigned long y_crd = Touch_ReadY();
    int xd1 = abs(50-x_crd);
    int yd1 = abs(100-y_crd);
    int rad1 = sqrt(xd1*xd1 + yd1*yd1);
    int xd2 = abs(150-x_crd);
    int yd2 = abs(100-y_crd);
    int rad2 = sqrt(xd2*xd2 + yd2*yd2);
    if (rad1 <= 10) { // if sw1 pressed 
      freq = PRESET1; // increase frequency
    } else if (rad2 <= 10) { // if sw2 pressed
      freq = PRESET3; // decrease frequency
    }
    PLL_Init(freq);        // Set system clock frequency depending on switch 
    ctemp = (147.5 - ((75)* (3.3) * (ADC_value)) / 4096.0);
    ftemp = ctemp * (9/5) + 32;
    LCD_SetCursor(15, 15);
    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(ctemp);
    LCD_PrintString(" C, ");
    LCD_PrintFloat(ftemp);
    LCD_PrintString(" F.");
    LCD_SetCursor(15, 30);
    LCD_PrintString("The current clock frequency is ");
    LCD_PrintInteger(freq);
    LCD_PrintString(" MHz.");
    sleep(3);
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // Clear the ADC0 interrupt flag
  ADCISC |= 0x8; // module 0, but we want SS3
  // Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3 & 0xFFF;
  GPTMICR_0 |= 0x1;
}
