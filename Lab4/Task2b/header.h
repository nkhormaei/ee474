/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This header file provides method declarations for necessary functionality in
 * implementing the GPIO addresses for using Port E and timer 0A,
 * in order to turn use the timer as an interrupt in 
 */ 

#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

// initialize LCD with traffic light system layout
void LCD_init_traffic_light(void);

// turn on LED connected to PE2 
void Red_on(void);
 
// turn off LED connected to PE2 
void Red_off(void);

// turn on LED connected to PE3
void Yellow_on(void); 
 
// turn off LED connected to PE3 
void Yellow_off(void); 

// turn on LED connected to PE4
void Green_on(void);

// turn off LED connected to PE4 
void Green_off(void); 

#endif //__HEADER1_H__ 