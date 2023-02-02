/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This header file provides method declarations for necessary functionality in
 * implementing the traffic light system as well as GPIO addresses for using Port E
 * to access the breadboard lights and buttons. 
 */ 

#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

// to turn on necessary ports
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

// to set up timer 0A for interrupts
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0      (*((volatile uint32_t *)0x40030024))
#define EN0            (*((volatile uint32_t *)0xE000E100))

// To set up and change the data for GPIO Port E: LEDS and breadboard buttons
#define GPIOAMSEL_E   (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E   (*((volatile uint32_t *)0x4005C420))
#define GPIODIR_E  (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E  (*((volatile uint32_t *)0x4005C51C))
#define GPIOPUR_E  (*((volatile uint32_t *)0x4005C510))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))               
#define GPIOIM_E  (*((volatile uint32_t *)0x4005C410))
#define GPIOIS_E  (*((volatile uint32_t *)0x4005C404))
#define GPIOIBE_E (*((volatile uint32_t *)0x4005C408))
#define GPIOICR_E (*((volatile uint32_t *)0x4005C41C))
#define GPIOIEV_E (*((volatile uint32_t *)0x4005C40C))

// initializes timer and interrupt registers
void timer_initc();

// initializes breadbord buttons for interrupts
void buttons();

// Sets up the LEDs and buttons
void led_init();

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

// Implementation for the traffic light FSM
void Traffic_Light_System();

#endif //__HEADER1_H__ 