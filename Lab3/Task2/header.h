#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

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

// timer registers
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCFG_0      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0    (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0      (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0     (*((volatile uint32_t *)0x40030024))

// ******************** CLOCK CONTROL REGISTERS ********************** //
#define MOSCCTL      (*(volatile uint32_t *) 0x400FE07C)
#define RIS          (*(volatile uint32_t *) 0x400FE050)
#define RSCLKCFG     (*(volatile uint32_t *) 0x400FE0B0)
#define PLLFREQ0     (*(volatile uint32_t *) 0x400FE160)
#define PLLFREQ1     (*(volatile uint32_t *) 0x400FE164)
#define PLLSTAT      (*(volatile uint32_t *) 0x400FE168)
#define MEMTIM0      (*(volatile uint32_t *) 0x400FE0C0)

// ******************** UART CONTROL REGISTERS ********************** //
#define RCGCUART     (*(volatile uint32_t *) 0x400FE618)
#define UART0CTL     (*(volatile uint32_t *) 0x4000C030)
#define UART0LCRH    (*(volatile uint32_t *) 0x4000C02C)
#define UART0IM      (*(volatile uint32_t *) 0x4000C038)
#define UART0DR      (*(volatile uint32_t *) 0x4000C000)
#define UART0FR      (*(volatile uint32_t *) 0x4000C018)
#define UART0IBRD    (*(volatile uint32_t *) 0x4000C024)
#define UART0FBRD    (*(volatile uint32_t *) 0x4000C028)
#define GPIOAFSEL_A  (*(volatile uint32_t *) 0x40058420)
#define GPIOPCTL_A   (*(volatile uint32_t *) 0x4005852C)
#define UART0CC      (*(volatile uint32_t *) 0x4000CFC8)

#define GPIODEN_A    (*(volatile uint32_t *) 0x4005851C)

#endif //__HEADER1_H__ 