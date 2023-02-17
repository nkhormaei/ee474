#ifndef _ADC_HEADER_H_
#define _ADC_HEADER_H_

// ******************** GPIO LED REGISTERS ********************** //
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

// setting up the leds
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
#define ADCSSMUX3    (*((volatile uint32_t *) 0x400380A0))
#define ADCSSEMUX3   (*((volatile uint32_t *) 0x400380B8))
#define ADCSSCTL3    (*((volatile uint32_t *) 0x400380A4))
#define ADCRIS       (*((volatile uint32_t *) 0x40038004))
#define ADCISC       (*((volatile uint32_t *) 0x4003800C))
#define GPTMCTL_0    (*((volatile uint32_t *) 0x4003000C))
#define GPTMADCEV    (*((volatile uint32_t *) 0x40030070))
#define ADCSSFIFO3   (*((volatile uint32_t *) 0x400380A8))
#define ADCIM        (*((volatile uint32_t *) 0x40038008))

#define NVIC_EN0   (*((volatile uint32_t *) 0xE000E100))
#define NVIC_EN1   (*((volatile uint32_t *) 0xE000E104))
#define NVIC_EN2   (*((volatile uint32_t *) 0xE000E108))

// ******************** Timer REGISTERS ********************** //
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0     (*((volatile uint32_t *)0x40030024))

#endif  // _ADC_HEADER_H_