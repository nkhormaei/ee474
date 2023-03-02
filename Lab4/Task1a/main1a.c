/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 2/19/23
 * This file provides the implementation for initializing
and filling in the LCD screen
 */ 
#include <stdint.h> 
#include <stdio.h>
#include "SSD2119_Display.h" 
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

int main()
{
  LCD_Init();
  unsigned short color = Color4[5];
  LCD_ColorFill(color);
  while (1) {};
  return 0;
}
