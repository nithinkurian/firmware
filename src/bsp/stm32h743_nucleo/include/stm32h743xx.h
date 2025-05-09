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
    __vol uint32_t OTYPE;    //GPIO port output type register        Offset 0x04
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

/*
 *  EXTI peripheral Register Definition Structure
 */
typedef struct
{
    __vol uint32_t RTSR1;           //Offset 0x00
    __vol uint32_t FTSR1;           //Offset 0x04
    __vol uint32_t SWIER1;          //Offset 0x08
    __vol uint32_t D3PMR1;          //Offset 0x0C
    __vol uint32_t D3PCR1L;         //Offset 0x10
    __vol uint32_t D3PCR1H;         //Offset 0x14
    __vol uint32_t RESERVED1[2];    //Offset 0x18 - 0x1C
    __vol uint32_t RTSR2;           //Offset 0x20
    __vol uint32_t FTSR2;           //Offset 0x24
    __vol uint32_t SWIER2;          //Offset 0x28
    __vol uint32_t D3PMR2;          //Offset 0x2c
    __vol uint32_t D3PCR2L;         //Offset 0x30
    __vol uint32_t D3PCR2H;         //Offset 0x34
    __vol uint32_t RESERVED2[2];    //Offset 0x38 - 0x3c
    __vol uint32_t RTSR3;           //Offset 0x40
    __vol uint32_t FTSR3;           //Offset 0x44
    __vol uint32_t SWIER3;          //Offset 0x48
    __vol uint32_t D3PMR3;          //Offset 0x4c
    __vol uint32_t D3PCR3L;         //Offset 0x50
    __vol uint32_t D3PCR3H;         //Offset 0x54
    __vol uint32_t RESERVED3[10];   //Offset 0x58 - 0x7c
    __vol uint32_t CPUIMR1;         //Offset 0x80
    __vol uint32_t CPUEMR1;         //Offset 0x84
    __vol uint32_t CPUPR1;          //Offset 0x88
    __vol uint32_t RESERVED4;       //Offset 0x8c
    __vol uint32_t CPUIMR2;         //Offset 0x90
    __vol uint32_t CPUEMR2;         //Offset 0x94
    __vol uint32_t CPUPR2;          //Offset 0x98
    __vol uint32_t RESERVED5;       //Offset 0x9c
    __vol uint32_t CPUIMR3;         //Offset 0xA0
    __vol uint32_t CPUEMR3;         //Offset 0xA4
    __vol uint32_t CPUPR3;          //Offset 0xA8
}EXTI_RegDef_t;

/*
 *  System configuration controller Register Definition Structure
 */
typedef struct
{
    __vol uint32_t RESERVED1;      /*!< Reserved,                                           Address offset: 0x00        */
    __vol uint32_t PMCR;           /*!< SYSCFG peripheral mode configuration register,      Address offset: 0x04        */
    __vol uint32_t EXTICR[4];      /*!< SYSCFG external interrupt configuration registers,  Address offset: 0x08-0x14   */
    __vol uint32_t CFGR;           /*!< SYSCFG configuration registers,                     Address offset: 0x18        */
    __vol uint32_t RESERVED2;      /*!< Reserved,                                           Address offset: 0x1C        */
    __vol uint32_t CCCSR;          /*!< SYSCFG compensation cell control/status register,   Address offset: 0x20        */
    __vol uint32_t CCVR;           /*!< SYSCFG compensation cell value register,            Address offset: 0x24        */
    __vol uint32_t CCCR;           /*!< SYSCFG compensation cell code register,             Address offset: 0x28        */
    __vol uint32_t PWRCR;          /*!< PWR control register,                               Address offset: 0x2C        */
    __vol uint32_t RESERVED3[61];  /*!< Reserved, 0x30-0x120                                                            */
    __vol uint32_t PKGR;           /*!< SYSCFG package register,                            Address offset: 0x124       */
    __vol uint32_t RESERVED4[118]; /*!< Reserved, 0x128-0x2FC                                                           */
    __vol uint32_t UR0;            /*!< SYSCFG user register 0,                             Address offset: 0x300       */
    __vol uint32_t UR1;            /*!< SYSCFG user register 1,                             Address offset: 0x304       */
    __vol uint32_t UR2;            /*!< SYSCFG user register 2,                             Address offset: 0x308       */
    __vol uint32_t UR3;            /*!< SYSCFG user register 3,                             Address offset: 0x30C       */
    __vol uint32_t UR4;            /*!< SYSCFG user register 4,                             Address offset: 0x310       */
    __vol uint32_t UR5;            /*!< SYSCFG user register 5,                             Address offset: 0x314       */
    __vol uint32_t UR6;            /*!< SYSCFG user register 6,                             Address offset: 0x318       */
    __vol uint32_t UR7;            /*!< SYSCFG user register 7,                             Address offset: 0x31C       */
    __vol uint32_t UR8;            /*!< SYSCFG user register 8,                             Address offset: 0x320       */
    __vol uint32_t UR9;            /*!< SYSCFG user register 9,                             Address offset: 0x324       */
    __vol uint32_t UR10;           /*!< SYSCFG user register 10,                            Address offset: 0x328       */
    __vol uint32_t UR11;           /*!< SYSCFG user register 11,                            Address offset: 0x32C       */
    __vol uint32_t UR12;           /*!< SYSCFG user register 12,                            Address offset: 0x330       */
    __vol uint32_t UR13;           /*!< SYSCFG user register 13,                            Address offset: 0x334       */
    __vol uint32_t UR14;           /*!< SYSCFG user register 14,                            Address offset: 0x338       */
    __vol uint32_t UR15;           /*!< SYSCFG user register 15,                            Address offset: 0x33C       */
    __vol uint32_t UR16;           /*!< SYSCFG user register 16,                            Address offset: 0x340       */
    __vol uint32_t UR17;           /*!< SYSCFG user register 17,                            Address offset: 0x344       */

} SYSCFG_RegDef_t;


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
#define EXTI                        ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG                      ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)





/**********************Clock Enable Macros for Peripherals************************/

/*
 *  Clock Enable Macros for GPIOx Peripherals
 */
#define GPIOA_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,0)
#define GPIOB_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,1)
#define GPIOC_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,2)
#define GPIOD_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,3)
#define GPIOE_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,4)
#define GPIOF_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,5)
#define GPIOG_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,6)
#define GPIOH_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,7)
#define GPIOI_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,8)
#define GPIOJ_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,9)
#define GPIOK_PERI_CLK_EN()         SET_BIT(RCC->AHB4ENR,10)

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
#define SYSCFG_PERI_CLK_EN()         SET_BIT(RCC->APB4ENR,1)

/**********************Clock Disable Macros for Peripherals************************/

/*
 *  Clock Disable Macros for GPIOx Peripherals
 */
#define GPIOA_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,0)
#define GPIOB_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,1)
#define GPIOC_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,2)
#define GPIOD_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,3)
#define GPIOE_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,4)
#define GPIOF_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,5)
#define GPIOG_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,6)
#define GPIOH_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,7)
#define GPIOI_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,8)
#define GPIOJ_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,9)
#define GPIOK_PERI_CLK_DI()         CLEAR_BIT(RCC->AHB4ENR,10)

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
#define SYSCFG_PERI_CLK_DI()         CLEAR_BIT(RCC->APB4ENR,1)

/**********************Reset Register Macros for Peripherals************************/

/*
 *  Reset Register Macros for GPIOx Peripherals
 */
#define GPIOA_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,0,1,1); CLEAR_BITS(RCC->AHB4RSTR,0,1);} while(0)
#define GPIOB_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,1,1,1); CLEAR_BITS(RCC->AHB4RSTR,1,1);} while(0)
#define GPIOC_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,2,1,1); CLEAR_BITS(RCC->AHB4RSTR,2,1);} while(0)
#define GPIOD_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,3,1,1); CLEAR_BITS(RCC->AHB4RSTR,3,1);} while(0)
#define GPIOE_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,4,1,1); CLEAR_BITS(RCC->AHB4RSTR,4,1);} while(0)
#define GPIOF_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,5,1,1); CLEAR_BITS(RCC->AHB4RSTR,5,1);} while(0)
#define GPIOG_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,6,1,1); CLEAR_BITS(RCC->AHB4RSTR,6,1);} while(0)
#define GPIOH_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,7,1,1); CLEAR_BITS(RCC->AHB4RSTR,7,1);} while(0)
#define GPIOI_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,8,1,1); CLEAR_BITS(RCC->AHB4RSTR,8,1);} while(0)
#define GPIOJ_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,9,1,1); CLEAR_BITS(RCC->AHB4RSTR,9,1);} while(0)
#define GPIOK_REG_RESET()           do{ SET_BITS(RCC->AHB4RSTR,10,1,1); CLEAR_BITS(RCC->AHB4RSTR,10,1);} while(0)

/*******************************MISC MACROS*********************************/
#define HSI_CLK                 64000000U
#define SYSTICK_TIM_CLK         HSI_CLK
#define NO_PR_BITS_IMPLEMENTED  4


/*
 *  Returns port code from GPIOx base address
 */
#define GPIO_BASEADDR_T0_CODE(x)   ((x == GPIOA)? 0 :\
                                    (x == GPIOB)? 1 :\
                                    (x == GPIOC)? 2 :\
                                    (x == GPIOD)? 3 :\
                                    (x == GPIOE)? 4 :\
                                    (x == GPIOF)? 5 :\
                                    (x == GPIOG)? 6 :\
                                    (x == GPIOH)? 7 :\
                                    (x == GPIOI)? 8 :\
                                    (x == GPIOJ)? 9 :\
                                    (x == GPIOK)? 10 :0 )

/*
 *  IRQ (Interrupt Request) Numbers
 */

#define IRQ_NO_EXTI0                6
#define IRQ_NO_EXTI1                7
#define IRQ_NO_EXTI2                8
#define IRQ_NO_EXTI3                9
#define IRQ_NO_EXTI4                10
#define IRQ_NO_EXTI9_5              23
#define IRQ_NO_EXTI15_10            40

/*
 *  NVIC IRQ (Interrupt Request) Priority
 */

#define NVIC_IRQ_PRIORITY0          0
#define NVIC_IRQ_PRIORITY1          1
#define NVIC_IRQ_PRIORITY2          2
#define NVIC_IRQ_PRIORITY3          3
#define NVIC_IRQ_PRIORITY4          4
#define NVIC_IRQ_PRIORITY5          5
#define NVIC_IRQ_PRIORITY6          6
#define NVIC_IRQ_PRIORITY7          7
#define NVIC_IRQ_PRIORITY8          8
#define NVIC_IRQ_PRIORITY9          9
#define NVIC_IRQ_PRIORITY10         10
#define NVIC_IRQ_PRIORITY11         11
#define NVIC_IRQ_PRIORITY12         12
#define NVIC_IRQ_PRIORITY13         13
#define NVIC_IRQ_PRIORITY14         14
#define NVIC_IRQ_PRIORITY15         15

 #endif // STM32H743XX_H
