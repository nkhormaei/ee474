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

// to turn on necessary ports
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

// to set up timer 0A  
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0     (*((volatile uint32_t *)0x40030024))
 
// To set up and change the data for GPIO Port E: LEDS and breadboard buttons
#define GPIOAMSEL_E   (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E       (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E     (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E      (*((volatile uint32_t *)0x4005C3FC))

// Sets up the LEDs and buttons
void led_init(); 

// Sets up timer configuration
void timer_initc();

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

// Returns true if system on/off button has been pressed for two seconds
bool system_button_pressed();

// delay 5 seconds before switching states while also monitoring
// for system or pedestrian button pressed
// returns 0 if neither pedestrianor system button were pressed for
// two seconds, returns 1 if the system button was pressed for
// two seconds, returns 2 if the pedestrian button was pressed
// for two seconds
int five_seconds();

// Implementation for the traffic light FSM
void Traffic_Light_System();

#endif //__HEADER1_H__ 