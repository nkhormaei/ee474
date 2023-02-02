/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This header file provides method declarations for necessary functionality in
 * implementing the GPIO addresses for using Port N and J in order to blink
 * LED 1 at a 1Hz rate and use SW1/2 to stop/start the timer as well as manipulate
 * LED 2
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
#define EN0            (*((volatile uint32_t *) 0xE000E100))

// to setup leds 1 and 2
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))

// to setup sw1 and sw2 for interrupts
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC))
#define GPIOIM_J     (*((volatile uint32_t *)0x40060410))
#define GPIOIS_J     (*((volatile uint32_t *)0x40060404))
#define GPIOIBE_J    (*((volatile uint32_t *)0x40060408))
#define GPIOICR_J    (*((volatile uint32_t *)0x4006041C))
#define GPIOIEV_J    (*((volatile uint32_t *)0x4006040C))
#define EN1            (*((volatile uint32_t *) 0xE000E104))

// initializes timer as an interrupt
void timer_initc();

// initializes the switches as interrupts
void switches();

// initializes led registers
void lights();

#endif //__HEADER1_H__ 
   
