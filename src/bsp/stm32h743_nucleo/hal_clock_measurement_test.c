#include "hal_clock_measurement_test.h"
#include <stdint.h>
#include "stm32h743xx.h"

void switch_to_HSE()
{
    //Note this will switch system clock to HSE
    //Enable HSE
    //set
    RCC->CR |= (0x1 << 16);

    //Wait for HSE to be stable
    while(!(RCC->CR |= (0x1 << 17)));

    //Switch system clock to HSE
    //clear
    RCC->CFGR &= ~(7 << 0);
    //set
    RCC->CFGR |= (0x2 << 0);
}


void mco2_output()
{
    //if you want to measure HSE uncomment below function
    //switch_to_HSE();

    //Select Desired clock for MCOX (2) signal
    //Set MCO2 clk to sys clock (0)
    //clear
    RCC->CFGR &= ~(7 << 29);
    //Set prescaler to 8
    //clear
    RCC->CFGR &= ~(0xF << 25);
    //set
    RCC->CFGR |= (0x8 << 25);

    //Output MCO2 signal to GPIO PIN PC9
    //PC9 D44 CN8 4
    //AF0 MCO2
    //Enable PORTC Peripheral clock
    GPIOC_PERI_CLK_EN();
    //Set PC9 to Alternate function
    //clear
    GPIOC->MODER &= ~(3 << 18);
    //set
    GPIOC->MODER |= (2 << 18);

    //Select Alternate function 0 for MCO2
    //clear
    GPIOC->AFR[1] &= ~(0xF << 4);
}