#ifndef _ADC_HEADER_H_
#define _ADC_HEADER_H_

#include <stdint.h>
// ******************** GPIO LED REGISTERS ********************** //
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 

#define GPIODIR_N    (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))

// ******************** ADC REGISTERS ********************** //
#define RCGCADC      (*((volatile uint32_t *) 0x400FE638))
#define ALTCLKCFG    (*((volatile uint32_t *) 0x400FE138))
#define ADCCC        (*((volatile uint32_t *) 0x40038FC8))
#define GPIODEN_E    (*((volatile uint32_t *) 0x4005C15C))
#define GPIOAMSEL_E  (*((volatile uint32_t *) 0x4005C528))
#define GPIOAFSEL_E  (*((volatile uint32_t *) 0x4005C420))
#define ADCACTSS     (*((volatile uint32_t *) 0x40038000))
#define ADCEMUX      (*((volatile uint32_t *) 0x40038014))
#define ADCSSMUX     (*((volatile uint32_t *) 0x40038040))
#define ADCSSCTL3    (*((volatile uint32_t *) 0x400380A4))
#define ADCRIS       (*((volatile uint32_t *) 0x40038004))

#endif  // _ADC_HEADER_H_