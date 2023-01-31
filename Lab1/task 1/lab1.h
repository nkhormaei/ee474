#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 
 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 

#define GPIODIR_N    (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))
 
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC))
//#define GPIOLOCK_J   (*((volatile uint32_t *)0x40060520))
//#define GPIOCR_J     (*((volatile uint32_t *)0x40060524))

void lights();
void switches();


#endif //__HEADER1_H__ 