#ifndef STM32H743XX_H
#define STM32H743XX_H

#include "cortexm7.h"

/********************Base Address of Flash and SRAM memories*********************/
#define FLASH_BASEADDR              0x08000000U //LENGTH = 2048K End 0x0820 0000
#define SYSTEM_MEM_BASEADDR         0x1FF00000U //LENGTH = 128K  End 0x1FF2 0000
#define DTCMRAM_BASEADDR            0x20000000U //LENGTH = 128K  End 0x2002 0000
#define SRAM_BASEADDR               0x24000000U //LENGTH = 512K  End 0x2408 0000
#define SRAM123_BASEADDR            0x30000000U //LENGTH = 288K  End 0x3004 8000
#define SRAM4_BASEADDR              0x38000000U //LENGTH = 64K   End 0x3801 0000

/*************Base Address of AHBx and APBx Bus Peripheral Addresses**************/
#define PERIPH_BASEADDR             0x40000000U
#define APB1_PERIPH_BASEADDR        PERIPH_BASEADDR
#define APB2_PERIPH_BASEADDR        0x40010000U
#define AHB1_PERIPH_BASEADDR        0x40020000U
#define AHB2_PERIPH_BASEADDR        0x48020000U
#define APB3_PERIPH_BASEADDR        0x50000000U
#define AHB3_PERIPH_BASEADDR        0x51000000U
#define APB4_PERIPH_BASEADDR        0x58000000U
#define AHB4_PERIPH_BASEADDR        0x58020000U

/***************************Base Address of Peripherals***************************/
/*
 *  Base Address of Peripheral in APB1 Bus 0x40000000U
 */
#define SPI2_I2S2_BASEADDR          (APB1_PERIPH_BASEADDR + 0x3800U)
#define SPI3_I2S3_BASEADDR          (APB1_PERIPH_BASEADDR + 0x3C00U)
#define USART2_BASEADDR             (APB1_PERIPH_BASEADDR + 0x4400U)
#define USART3_BASEADDR             (APB1_PERIPH_BASEADDR + 0x4800U)
#define UART4_BASEADDR              (APB1_PERIPH_BASEADDR + 0x4C00U)
#define UART5_BASEADDR              (APB1_PERIPH_BASEADDR + 0x5000U)
#define I2C1_BASEADDR               (APB1_PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR               (APB1_PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR               (APB1_PERIPH_BASEADDR + 0x5C00U)
#define UART7_BASEADDR              (APB1_PERIPH_BASEADDR + 0x7800U)
#define UART8_BASEADDR              (APB1_PERIPH_BASEADDR + 0x7C00U)
                                    
/*                                  
 *  Base Address of Peripheral in APB2 Bus 0x40010000U
 */
#define USART1_BASEADDR             (APB2_PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR             (APB2_PERIPH_BASEADDR + 0x1400U)
#define SPI1_I2S1_BASEADDR          (APB2_PERIPH_BASEADDR + 0x3000U)
#define SPI4_BASEADDR               (APB2_PERIPH_BASEADDR + 0x3400U)
#define SPI5_BASEADDR               (APB2_PERIPH_BASEADDR + 0x5000U)

/*
 *  Base Address of Peripheral in AHB1 Bus 0x40020000U
 */
#define ADC1_ADC2_BASEADDR          (AHB1_PERIPH_BASEADDR + 0x2000U)
#define USB1_OTG_HS_BASEADDR        (AHB1_PERIPH_BASEADDR +0x20000U)
#define USB2_OTG_FS_BASEADDR        (AHB1_PERIPH_BASEADDR +0x60000U)


/*
 *  Base Address of Peripheral in AHB2 Bus 0x48020000U
 */

/*
 *  Base Address of Peripheral in APB3 Bus 0x50000000U
 */

/*
 *  Base Address of Peripheral in AHB3 Bus 0x51000000U
 */


/*
 *  Base Address of Peripheral in APB4 Bus 0x58000000U
 */
#define EXTI_BASEADDR               (APB4_PERIPH_BASEADDR + 0x0000U)
#define SYSCFG_BASEADDR             (APB4_PERIPH_BASEADDR + 0x0400U)
#define LPUART1_BASEADDR            (APB4_PERIPH_BASEADDR + 0x0C00U)
#define SPI6_BASEADDR               (APB4_PERIPH_BASEADDR + 0x1400U)
#define I2C4_BASEADDR               (APB4_PERIPH_BASEADDR + 0x1C00U)

/*
 *  Base Address of Peripheral in AHB4 Bus 0x58020000U
 */
#define GPIOA_BASEADDR              (AHB4_PERIPH_BASEADDR +0x0000U)
#define GPIOB_BASEADDR              (AHB4_PERIPH_BASEADDR +0x0400U)
#define GPIOC_BASEADDR              (AHB4_PERIPH_BASEADDR +0x0800U)
#define GPIOD_BASEADDR              (AHB4_PERIPH_BASEADDR +0x0C00U)
#define GPIOE_BASEADDR              (AHB4_PERIPH_BASEADDR +0x1000U)
#define GPIOF_BASEADDR              (AHB4_PERIPH_BASEADDR +0x1400U)
#define GPIOG_BASEADDR              (AHB4_PERIPH_BASEADDR +0x1800U)
#define GPIOH_BASEADDR              (AHB4_PERIPH_BASEADDR +0x1C00U)
#define GPIOI_BASEADDR              (AHB4_PERIPH_BASEADDR +0x2000U)
#define GPIOJ_BASEADDR              (AHB4_PERIPH_BASEADDR +0x2400U)
#define GPIOK_BASEADDR              (AHB4_PERIPH_BASEADDR +0x2800U)
#define RCC_BASEADDR                (AHB4_PERIPH_BASEADDR +0x4400U)
#define ADC3_BASEADDR               (AHB4_PERIPH_BASEADDR +0x6000U)


/*********************Peripheral Register Definition Structure********************/

/*
 *  GPIO peripheral Register Definition Structure
 */
typedef struct
{
    __vol uint32_t MODER;     //GPIO port mode register               Offset 0x00
    __vol uint32_t OTYPER;    //GPIO port output type register        Offset 0x04
    __vol uint32_t OSPEEDR;   //GPIO port output speed register       Offset 0x08
    __vol uint32_t PUPDR;     //GPIO port pull-up/pull-down register  Offset 0x0C
    __vol uint32_t IDR;       //GPIO port input data register         Offset 0x10
    __vol uint32_t ODR;       //GPIO port output data register        Offset 0x14
    __vol uint32_t BSRR;      //GPIO port bit set/reset register      Offset 0x18
    __vol uint32_t LCKR;      //GPIO port configuration lock register Offset 0x1C
    __vol uint32_t AFR[2];    //GPIO alternate function register      Offset 0x20
}GPIO_RegDef_t;

/*
 *  RCC peripheral Register Definition Structure
 */
typedef struct
{
    __vol uint32_t CR;              //Offset 0x00
    __vol uint32_t ICSCR;           //Offset 0x04
    __vol uint32_t CRRCR;           //Offset 0x08
    __vol uint32_t CSICFGR;         //Offset 0x0C
    __vol uint32_t CFGR;            //Offset 0x10
    __vol uint32_t RESERVED1;       //Offset 0x14
    __vol uint32_t D1CFGR;          //Offset 0x18
    __vol uint32_t D2CFGR;          //Offset 0x1C
    __vol uint32_t D3CFGR;          //Offset 0x20
    __vol uint32_t RESERVED2;       //Offset 0x24
    __vol uint32_t PLLCKSELR;       //Offset 0x28
    __vol uint32_t PLLCFGR;         //Offset 0x2c
    __vol uint32_t PLL1DIVR;        //Offset 0x30
    __vol uint32_t PLL1FRACR;       //Offset 0x34
    __vol uint32_t PLL2DIVR;        //Offset 0x38
    __vol uint32_t PLL2FRACR;       //Offset 0x3c
    __vol uint32_t PLL3DIVR;        //Offset 0x40
    __vol uint32_t PLL3FRACR;       //Offset 0x44
    __vol uint32_t RESERVED3;       //Offset 0x48
    __vol uint32_t D1CCIPR;         //Offset 0x4c
    __vol uint32_t D2CCIP1R;        //Offset 0x50
    __vol uint32_t D2CCIP2R;        //Offset 0x54
    __vol uint32_t D3CCIPR;         //Offset 0x58
    __vol uint32_t RESERVED4;       //Offset 0x5c
    __vol uint32_t CIER;            //Offset 0x60
    __vol uint32_t CIFR;            //Offset 0x64
    __vol uint32_t CICR;            //Offset 0x68
    __vol uint32_t RESERVED5;       //Offset 0x6c
    __vol uint32_t BDCR;            //Offset 0x70
    __vol uint32_t CSR;             //Offset 0x74
    __vol uint32_t RESERVED6;       //Offset 0x78
    __vol uint32_t AHB3RSTR;        //Offset 0x7c
    __vol uint32_t AHB1RSTR;        //Offset 0x80
    __vol uint32_t AHB2RSTR;        //Offset 0x84
    __vol uint32_t AHB4RSTR;        //Offset 0x88
    __vol uint32_t APB3RSTR;        //Offset 0x8c
    __vol uint32_t APB1LRSTR;       //Offset 0x90
    __vol uint32_t APB1HRSTR;       //Offset 0x94
    __vol uint32_t APB2RSTR;        //Offset 0x98
    __vol uint32_t APB4RSTR;        //Offset 0x9c
    __vol uint32_t GCR;             //Offset 0xA0
    __vol uint32_t RESERVED7;       //Offset 0xA4
    __vol uint32_t D3AMR;           //Offset 0xA8
    __vol uint32_t RESERVED8[9];    //Offset 0xAc
    __vol uint32_t RSR;             //Offset 0xD0
    __vol uint32_t AHB3ENR;         //Offset 0xD4
    __vol uint32_t AHB1ENR;         //Offset 0xD8
    __vol uint32_t AHB2ENR;         //Offset 0xDc
    __vol uint32_t AHB4ENR;         //Offset 0xE0
    __vol uint32_t APB3ENR;         //Offset 0xE4
    __vol uint32_t APB1LENR;        //Offset 0xE8
    __vol uint32_t APB1HENR;        //Offset 0xEc
    __vol uint32_t APB2ENR;         //Offset 0xF0
    __vol uint32_t APB4ENR;         //Offset 0xF4
    __vol uint32_t RESERVED9;       //Offset 0xF8
    __vol uint32_t AHB3LPENR;       //Offset 0xFc
    __vol uint32_t AHB1LPENR;       //Offset 0x100
    __vol uint32_t AHB2LPENR;       //Offset 0x104
    __vol uint32_t AHB4LPENR;       //Offset 0x108
    __vol uint32_t APB3LPENR;       //Offset 0x10c
    __vol uint32_t APB1LLPENR;      //Offset 0x110
    __vol uint32_t APB1HLPENR;      //Offset 0x114
    __vol uint32_t APB2LPENR;       //Offset 0x118
    __vol uint32_t APB4LPENR;       //Offset 0x11c
    __vol uint32_t RESERVED10[5];   //Offset 0x120
    __vol uint32_t C1_AHB3ENR;      //Offset 0x134
    __vol uint32_t C1_AHB1ENR;      //Offset 0x138
    __vol uint32_t C1_AHB2ENR;      //Offset 0x13c
    __vol uint32_t C1_AHB4ENR;      //Offset 0x140
    __vol uint32_t C1_APB3ENR;      //Offset 0x144
    __vol uint32_t C1_APB1LENR;     //Offset 0x148
    __vol uint32_t C1_APB1HENR;     //Offset 0x14c
    __vol uint32_t C1_APB2ENR;      //Offset 0x150
    __vol uint32_t C1_APB4ENR;      //Offset 0x154
    __vol uint32_t RESERVED11;      //Offset 0x158
    __vol uint32_t C1_AHB3LPENR;    //Offset 0x15c
    __vol uint32_t C1_AHB1LPENR;    //Offset 0x160
    __vol uint32_t C1_AHB2LPENR;    //Offset 0x164
    __vol uint32_t C1_AHB4LPENR;    //Offset 0x168
    __vol uint32_t C1_APB3LPENR;    //Offset 0x16c
    __vol uint32_t C1_APB1LLPENR;   //Offset 0x170
    __vol uint32_t C1_APB1HLPENR;   //Offset 0x174
    __vol uint32_t C1_APB2LPENR;    //Offset 0x178
    __vol uint32_t C1_APB4LPENR;    //Offset 0x17c
}RCC_RegDef_t;


/*****************************Peripheral Definition*******************************/
#define GPIOA                       ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                       ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                       ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                       ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                       ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                       ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                       ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH                       ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI                       ((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ                       ((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK                       ((GPIO_RegDef_t*)GPIOK_BASEADDR)

#define RCC                         ((RCC_RegDef_t*)RCC_BASEADDR)

/**********************Clock Enable Macros for Peripherals************************/

/*
 *  Clock Enable Macros for GPIOx Peripherals
 */
#define GPIOA_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 0))
#define GPIOB_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 1))
#define GPIOC_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 2))
#define GPIOD_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 3))
#define GPIOE_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 4))
#define GPIOF_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 5))
#define GPIOG_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 6))
#define GPIOH_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 7))
#define GPIOI_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 8))
#define GPIOJ_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 9))
#define GPIOK_PERI_CLK_EN()         (RCC->AHB4ENR |= (1 << 10))

/*
 *  Clock Enable Macros for I2Cx Peripherals
 */

/*
 *  Clock Enable Macros for SPIx Peripherals
 */

/*
 *  Clock Enable Macros for USARTx Peripherals
 */

/*
 *  Clock Enable Macros for SYSCFG Peripherals
 */

/**********************Clock Disable Macros for Peripherals************************/

/*
 *  Clock Disable Macros for GPIOx Peripherals
 */
#define GPIOA_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 0))
#define GPIOB_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 1))
#define GPIOC_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 2))
#define GPIOD_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 3))
#define GPIOE_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 4))
#define GPIOF_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 5))
#define GPIOG_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 6))
#define GPIOH_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 7))
#define GPIOI_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 8))
#define GPIOJ_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 9))
#define GPIOK_PERI_CLK_DI()         (RCC->AHB4ENR &= ~(1 << 10))

/*
 *  Clock Disable Macros for I2Cx Peripherals
 */

/*
 *  Clock Disable Macros for SPIx Peripherals
 */

/*
 *  Clock Disable Macros for USARTx Peripherals
 */

/*
 *  Clock Disable Macros for SYSCFG Peripherals
 */




/*******************************MISC Constants*********************************/
#define HSI_CLK             64000000U
#define SYSTICK_TIM_CLK     HSI_CLK


 #endif // STM32H743XX_H
