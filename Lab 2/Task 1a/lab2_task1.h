/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This header file provides method declarations for necessary functionality in
 * implementing the GPIO addresses for using Port F, N and timer 0A,
 * in order to turn on and off LEDs 1-4 in a periodic pattern
 */ 

#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

// to turn on necessary ports
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

// to set up timer 0a
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0     (*((volatile uint32_t *)0x40030024))

// to setup leds 3 and 4
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 

// to setup leds 1 and 2
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))

// initializes timer registers
void timer_initc();

// initializes led registers
void lights();

// performs turning all the leds on and off sequentially
// at the rate of the timer (1Hz)
void polling_GPIO();

#endif //__HEADER1_H__ 
   

