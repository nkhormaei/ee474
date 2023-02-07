/* 
 * Sidharth Daga, Nick Khormaei
 * 1964629, 2033863
 * 1/24/23
 * This header file provides method declarations for necessary functionality in
 * implementing the GPIO addresses for using Port F, N and J  and timer
 */ 

#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

   
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
 
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))

#define GPTMCTL_0      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0     (*((volatile uint32_t *)0x40030024))

#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 

#define GPIODIR_N    (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))

void timer_initc();
void lights();
void polling_GPIO();


#endif //__HEADER1_H__ 
   

