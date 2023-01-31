#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 
 
#define RCGCGPIO        (*((volatile uint32_t *)0x400FE608))

#define GPIOAMSEL_L     (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_L       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_L       (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_L     (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_L      (*((volatile uint32_t *)0x4005C3FC))

// changed 62 to 5C on the gpio registers for port E

void Red_on(void);

 
// turn off LED connected to PL2 
void Red_off(void);


// turn on LED connected to PL3
void Yellow_on(void); 

 
// turn off LED connected to PL3 
void Yellow_off(void); 


// turn on LED connected to PL4
void Green_on(void);

 
// turn off LED connected to PL4 
void Green_off(void); 

void Traffic_Light_System();


#endif //__HEADER1_H__  