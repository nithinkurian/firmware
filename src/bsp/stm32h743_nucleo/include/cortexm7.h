#ifndef CORTEX_M7_H
#define CORTEX_M7_H

#include "common.h"


/*****************************Base Address of Core Hardware******************************/
#define SCS_BASEADDR        (0xE000E000UL)             /*!< System Control Space Base Address */
#define SYSTICK_BASEADDR    (SCS_BASEADDR +  0x0010UL) /*!< SysTick Base Address */
#define SCB_BASEADDR        (SCS_BASEADDR +  0x0D00UL) /*!< System Control Block Base Address */


/*********************Private Peripheral Register Definition Structure********************/

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __vol uint32_t CSR;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __vol uint32_t RVR;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __vol uint32_t VAL;                   /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __vol uint32_t CALIB;                 /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_RegDef_t;

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __vol uint32_t CPUID;                 //CPUID Base Register                                       	Offset: 0x000 (R/ )
  __vol uint32_t ICSR;                  //Interrupt Control and State Register                      	Offset: 0x004 (R/W)
  __vol uint32_t VTOR;                  //Vector Table Offset Register                              	Offset: 0x008 (R/W)
  __vol uint32_t AIRCR;                 //Application Interrupt and Reset Control Register          	Offset: 0x00C (R/W)
  __vol uint32_t SCR;                   //System Control Register                                   	Offset: 0x010 (R/W)
  __vol uint32_t CCR;                   //Configuration Control Register                            	Offset: 0x014 (R/W)
  __vol uint8_t  SHPR[12U];             //System Handlers Priority Registers (4-7, 8-11, 12-15)     	Offset: 0x018 (R/W)
  __vol uint32_t SHCSR;                 //System Handler Control and State Register                	  Offset: 0x024 (R/W)
  __vol uint32_t CFSR;                  //Configurable Fault Status Register                       	  Offset: 0x028 (R/W)
  __vol uint32_t HFSR;                  //HardFault Status Register                                	  Offset: 0x02C (R/W)
  __vol uint32_t DFSR;                  //Debug Fault Status Register                              	  Offset: 0x030 (R/W)
  __vol uint32_t MMFAR;                 //MemManage Fault Address Register                         	  Offset: 0x034 (R/W)
  __vol uint32_t BFAR;                  //BusFault Address Register                                	  Offset: 0x038 (R/W)
  __vol uint32_t AFSR;                  //Auxiliary Fault Status Register                             Offset: 0x03C (R/W)
} SCB_RegDef_t;


/*****************************Private Peripheral Definition*******************************/

#define SCB                 ((SCB_RegDef_t*)SCB_BASEADDR)         /*!< SCB configuration struct */
#define SYSTICK             ((SysTick_RegDef_t*)SYSTICK_BASEADDR) /*!< SysTick configuration struct */



#endif // STM32H743XX_H
