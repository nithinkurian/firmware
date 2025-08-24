#include "hal_clock_measurement_test.h"
#include <stdint.h>
#include "stm32h743xx.h"

void switch_to_HSE()
{
    //Note this will switch system clock to HSE
    //Enable HSE
    SET_BIT(RCC->CR,16);

    //Wait for HSE to be stable
    while(!(READ_BIT(RCC->CR,17)));

    //Switch system clock to HSE
    WRITE_REG(RCC->CFGR,0,0x2,0x7);
}


void mco2_output()
{
    //if you want to measure HSE uncomment below function
    //switch_to_HSE();

    //Select Desired clock for MCOX (2) signal
    //Set MCO2 clk to sys clock (0)
    //clear
    CLEAR_BITS(RCC->CFGR,29,0x7);
    //Set prescaler to 8
    WRITE_REG(RCC->CFGR,25,0x8,0xF);

    //Output MCO2 signal to GPIO PIN PC9
    //PC9 D44 CN8 4
    //AF0 MCO2
    //Enable PORTC Peripheral clock
    GPIOC_PERI_CLK_EN();
    //Set PC9 to Alternate function
    WRITE_REG(GPIOC->MODER,18,0x2,0x3);

    //Select Alternate function 0 for MCO2
    //clear
    CLEAR_BITS(GPIOC->AFR[1],4,0xF);
}