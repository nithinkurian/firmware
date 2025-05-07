#include "hal_clock_measurement_test.h"
#include <stdint.h>


#define RCC_BASE_ADDR           0x58024400UL

#define RCC_CFGR_OFFSET         0x10UL
#define RCC_CFGR_ADDR           ((RCC_BASE_ADDR) + (RCC_CFGR_OFFSET))

#define RCC_AHB4ENR_OFFS        0xE0UL
#define RCC_AHB4ENR_ADDR        ((RCC_BASE_ADDR) + (RCC_AHB4ENR_OFFS))

#define PORTC_BA_ADDR           0x58020800UL
#define PORTC_MODER_OFFSET      0x0UL
#define PORTC_MODER_ADDR        ((PORTC_BA_ADDR) + (PORTC_MODER_OFFSET))

#define PORTC_AFRH_OFFSET       0x24UL
#define PORTC_AFRH_ADDR         ((PORTC_BA_ADDR) + (PORTC_AFRH_OFFSET))


void mco2_output()
{
    //Select Desired clock for MCOX (2) signal
    uint32_t *pRCC_CFGR_Reg = (uint32_t *)RCC_CFGR_ADDR;
    //Set MCO2 clk to sys clock (0)
    //clear
    *pRCC_CFGR_Reg &= ~(7 << 29);
    //Set prescaler to 8
    //clear
    *pRCC_CFGR_Reg &= ~(0xF << 25);
    //set
    *pRCC_CFGR_Reg |= (0x8 << 25);

    //Output MCO2 signal to GPIO PIN PC9
    //PC9 D44 CN8 4
    //AF0 MCO2
    //Enable PORTC Peripheral clock
    uint32_t *pRCC_AHB4ENR_Reg = (uint32_t *)RCC_AHB4ENR_ADDR;
    //set
    *pRCC_AHB4ENR_Reg |= (1 << 2);
    //Set PC9 to Alternate function
    uint32_t *pPORTC_MODER_Reg = (uint32_t *)PORTC_MODER_ADDR;
    //clear
    *pPORTC_MODER_Reg &= ~(3 << 18);
    //set
    *pPORTC_MODER_Reg |= (2 << 18);

    //Select Alternate function 0 for MCO2
    uint32_t *pPORTC_AFRH_Reg = (uint32_t *)PORTC_AFRH_ADDR;
    //clear
    *pPORTC_AFRH_Reg &= ~(0xF << 4);
}