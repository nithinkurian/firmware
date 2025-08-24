#include<stdint.h>
#include "stm32h743xx.h"

#define SRAM_START    0x24000000U
#define SRAM_SIZE   ( (512U)*(1024U)) //512K
#define SRAM_END    (SRAM_START) +  (SRAM_SIZE)

#define STACK_START   SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;

//prototype of main
int main(void);

void __libc_init_array(void);


/* function prototypes of STM32H743 system  exception and IRQ handlers */

void Reset_Handler(void);
void NMI_Handler(void)                        __attribute__ ((weak,alias("Default_Handler")));
void HardFault_Handler(void)                  __attribute__ ((weak,alias("Default_Handler")));
void MemManage_Handler(void)                  __attribute__ ((weak,alias("Default_Handler")));
void BusFault_Handler(void)                   __attribute__ ((weak,alias("Default_Handler")));
void UsageFault_Handler(void)                 __attribute__ ((weak,alias("Default_Handler")));
                                                                                                   /* Reserved                 */                      
                                                                                                   /* Reserved                 */                      
                                                                                                   /* Reserved                 */                      
                                                                                                   /* Reserved                 */                      
void SVC_Handler(void)                        __attribute__ ((weak,alias("Default_Handler")));
void DebugMon_Handler(void)                   __attribute__ ((weak,alias("Default_Handler")));
                                                                                                   /* Reserved                 */                      
void PendSV_Handler(void)                     __attribute__ ((weak,alias("Default_Handler")));
void SysTick_Handler(void)                    __attribute__ ((weak,alias("Default_Handler")));
void WWDG1_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* Window Watchdog interrupt                   */
void PVD_PVM_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* PVD through EXTI line                       */
void RTC_TAMP_STAMP_CSS_LSE_IRQHandler(void)  __attribute__ ((weak,alias("Default_Handler")));     /* RTC tamper, timestamp                       */
void RTC_WKUP_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* RTC Wakeup interrupt                        */
void FLASH_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* Flash memory                                */
void RCC_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* RCC global interrupt                        */
void EXTI0_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line 0 interrupt                       */
void EXTI1_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line 1 interrupt                       */
void EXTI2_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line 2 interrupt                       */
void EXTI3_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line 3interrupt                        */
void EXTI4_IRQHandler (void)                  __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line 4interrupt                        */
void DMA_STR0_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream0                                */
void DMA_STR1_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream1                                */
void DMA_STR2_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream2                                */
void DMA_STR3_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream3                                */
void DMA_STR4_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream4                                */
void DMA_STR5_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream5                                */
void DMA_STR6_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream6                                */
void ADC1_2_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* ADC1 and ADC2                               */
void FDCAN1_IT0_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* FDCAN1 Interrupt 0                          */
void FDCAN2_IT0_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* FDCAN2 Interrupt 0                          */
void FDCAN1_IT1_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* FDCAN1 Interrupt 1                          */
void FDCAN2_IT1_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* FDCAN2 Interrupt 1                          */
void EXTI9_5_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line[9:5] interrupts                   */
void TIM1_BRK_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* TIM1 break interrupt                        */
void TIM1_UP_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* TIM1 update interrupt                       */
void TIM1_TRG_COM_IRQHandler(void)            __attribute__ ((weak,alias("Default_Handler")));     /* TIM1 trigger and commutation                */
void TIM_CC_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* TIM1 capture / compare                      */
void TIM2_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* TIM2 global interrupt                       */
void TIM3_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* TIM3 global interrupt                       */
void TIM4_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* TIM4 global interrupt                       */
void I2C1_EV_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C1 event interrupt                        */
void I2C1_ER_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C1 error interrupt                        */
void I2C2_EV_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C2 event interrupt                        */
void I2C2_ER_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C2 error interrupt                        */
void SPI1_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI1 global interrupt                       */
void SPI2_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI2 global interrupt                       */
void USART1_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* USART1 global interrupt                     */
void USART2_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* USART2 global interrupt                     */
void USART3_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* USART3 global interrupt                     */
void EXTI15_10_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* EXTI Line[15:10] interrupts                 */
void RTC_ALARM_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* RTC alarms (A and B)                        */
                                                                       				                     /* Reserved                     */
void TIM8_BRK_TIM12_IRQHandler(void)          __attribute__ ((weak,alias("Default_Handler")));     /* TIM8 and 12 break global                    */
void TIM8_UP_TIM13_IRQHandler(void)           __attribute__ ((weak,alias("Default_Handler")));     /* TIM8 and 13 update global                   */
void TIM8_TRG_COM_TIM14_IRQHandler(void)      __attribute__ ((weak,alias("Default_Handler")));     /* TIM8 and 14 trigger /commutation and global */
void TIM8_CC_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* TIM8 capture / compare                      */
void DMA1_STR7_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA1 Stream7                                */
void FMC_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* FMC global interrupt                        */
void SDMMC1_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* SDMMC global interrupt                      */
void TIM5_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* TIM5 global interrupt                       */
void SPI3_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI3 global interrupt                       */
void UART4_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* UART4 global interrupt                      */
void UART5_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* UART5 global interrupt                      */
void TIM6_DAC_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* TIM6 global interrupt                       */
void TIM7_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* TIM7 global interrupt                       */
void DMA2_STR0_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream0 interrupt                      */
void DMA2_STR1_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream1 interrupt                      */
void DMA2_STR2_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream2 interrupt                      */
void DMA2_STR3_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream3 interrupt                      */
void DMA2_STR4_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream4 interrupt                      */
void ETH_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* Ethernet global interrupt                   */
void ETH_WKUP_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* Ethernet wakeup through EXTI                */
void FDCAN_CAL_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* CAN2TX interrupts                           */
                                                                                                   /* Reserved                 */                                
                                                                                                   /* Reserved                 */                                
                                                                                                   /* Reserved                 */                                
                                                                                                   /* Reserved                 */                                
void DMA2_STR5_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream5 interrupt                      */
void DMA2_STR6_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream6 interrupt                      */
void DMA2_STR7_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* DMA2 Stream7 interrupt                      */
void USART6_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* USART6 global interrupt                     */
void I2C3_EV_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C3 event interrupt                        */
void I2C3_ER_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C3 error interrupt                        */
void OTG_HS_EP1_OUT_IRQHandler(void)          __attribute__ ((weak,alias("Default_Handler")));     /* OTG_HS out global interrupt                 */
void OTG_HS_EP1_IN_IRQHandler(void)           __attribute__ ((weak,alias("Default_Handler")));     /* OTG_HS in global interrupt                  */
void OTG_HS_WKUP_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* OTG_HS wakeup interrupt                     */
void OTG_HS_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* OTG_HS global interrupt                     */
void DCMI_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* DCMI global interrupt                       */
                                                                                                   /* Reserved                  */
                                                                                                   /* Reserved                  */
void FPU_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* Floating point unit interrupt               */
void UART7_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* UART7 global interrupt                      */
void UART8_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* UART8 global interrupt                      */
void SPI4_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI4 global interrupt                       */
void SPI5_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI5 global interrupt                       */
void SPI6_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SPI6 global interrupt                       */
void SAI1_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SAI1 global interrupt                       */
void LTDC_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* LCD-TFT global interrupt                    */
void LTDC_ER_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* LCD-TFT error interrupt                     */
void DMA2D_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* DMA2D global interrupt                      */
void SAI2_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SAI2 global interrupt                       */
void QUADSPI_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* QuadSPI global interrupt                    */
void LPTIM1_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPTIM1 global interrupt                     */
void CEC_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* HDMI-CEC global interrupt                   */
void I2C4_EV_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C4 event interrupt                        */
void I2C4_ER_IRQHandler(void)                 __attribute__ ((weak,alias("Default_Handler")));     /* I2C4 error interrupt                        */
void SPDIF_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* SPDIFRX global interrupt                    */
void OTG_FS_EP1_OUT_IRQHandler(void)          __attribute__ ((weak,alias("Default_Handler")));     /* OTG_FS out global interrupt                 */
void OTG_FS_EP1_IN_IRQHandler(void)           __attribute__ ((weak,alias("Default_Handler")));     /* OTG_FS in global interrupt                  */
void OTG_FS_WKUP_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* OTG_FS wakeup                               */
void OTG_FS_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* OTG_FS global interrupt                     */
void DMAMUX1_OV_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* DMAMUX1 overrun interrupt                   */
void HRTIM1_MST_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 master timer interrupt               */
void HRTIM1_TIMA_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 timer A interrupt                    */
void HRTIM_TIMB_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 timer B interrupt                    */
void HRTIM1_TIMC_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 timer C interrupt                    */
void HRTIM1_TIMD_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 timer D interrupt                    */
void HRTIM_TIME_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 timer E interrupt                    */
void HRTIM1_FLT_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* HRTIM1 fault interrupt                      */
void DFSDM1_FLT0_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* DFSDM1 filter 0 interrupt                   */
void DFSDM1_FLT1_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* DFSDM1 filter 1 interrupt                   */
void DFSDM1_FLT2_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* DFSDM1 filter 2 interrupt                   */
void DFSDM1_FLT3_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* DFSDM1 filter 3 interrupt                   */
void SAI3_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SAI3 global interrupt                       */
void SWPMI1_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* SWPMI global interrupt                      */
void TIM15_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* TIM15 global interrupt                      */
void TIM16_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* TIM16 global interrupt                      */
void TIM17_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* TIM17 global interrupt                      */
void MDIOS_WKUP_IRQHandler(void)              __attribute__ ((weak,alias("Default_Handler")));     /* MDIOS wakeup                                */
void MDIOS_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* MDIOS global interrupt                      */
void JPEG_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* JPEG global interrupt                       */
void MDMA_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* MDMA                                        */
                                                                                                   /* Reserved                           */
void SDMMC_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* SDMMC global interrupt                      */
void HSEM0_IRQHandler(void)                   __attribute__ ((weak,alias("Default_Handler")));     /* HSEM global interrupt 1                     */
                                                                                                   /* Reserved                           */
void ADC3_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* ADC3 global interrupt                       */
void DMAMUX2_OVR_IRQHandler(void)             __attribute__ ((weak,alias("Default_Handler")));     /* DMAMUX2 overrun interrupt                   */
void BDMA_CH1_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 1 interrupt                    */
void BDMA_CH2_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 2 interrupt                    */
void BDMA_CH3_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 3 interrupt                    */
void BDMA_CH4_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 4 interrupt                    */
void BDMA_CH5_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 5 interrupt                    */
void BDMA_CH6_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 6 interrupt                    */
void BDMA_CH7_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 7 interrupt                    */
void BDMA_CH8_IRQHandler(void)                __attribute__ ((weak,alias("Default_Handler")));     /* BDMA channel 8 interrupt                    */
void COMP_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* COMP1 and COMP2                             */
void LPTIM2_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPTIM2 timer interrupt                      */
void LPTIM3_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPTIM2 timer interrupt                      */
void LPTIM4_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPTIM2 timer interrupt                      */
void LPTIM5_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPTIM2 timer interrupt                      */
void LPUART_IRQHandler(void)                  __attribute__ ((weak,alias("Default_Handler")));     /* LPUART global interrupt                     */
void WWDG1_RST_IRQHandler(void)               __attribute__ ((weak,alias("Default_Handler")));     /* Window Watchdog interrupt                   */
void CRS_IRQHandler(void)                     __attribute__ ((weak,alias("Default_Handler")));     /* Clock Recovery System globa                 */
                                                                                                   /* Reserved                           */
void SAI4_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* SAI4 global interrupt                       */
                                                                                                   /* Reserved                           */
                                                                                                   /* Reserved                           */
void WKUP_IRQHandler(void)                    __attribute__ ((weak,alias("Default_Handler")));     /* WKUP1 to WKUP6 pins                         */


uint32_t vectors[] __attribute__ ((section (".isr-vector"))) = {
	STACK_START,
	(uint32_t)Reset_Handler,
	(uint32_t)NMI_Handler,
	(uint32_t)HardFault_Handler,          
	(uint32_t)MemManage_Handler,          
	(uint32_t)BusFault_Handler,           
	(uint32_t)UsageFault_Handler,         
	0,
	0,
	0,
	0,
	(uint32_t)SVC_Handler,                
	(uint32_t)DebugMon_Handler,           
	0,                    
	(uint32_t)PendSV_Handler,             
	(uint32_t)SysTick_Handler,            
	(uint32_t)WWDG1_IRQHandler,          
	(uint32_t)PVD_PVM_IRQHandler,         
	(uint32_t)RTC_TAMP_STAMP_CSS_LSE_IRQHandler,
	(uint32_t)RTC_WKUP_IRQHandler,        
	(uint32_t)FLASH_IRQHandler,         
	(uint32_t)RCC_IRQHandler,          
	(uint32_t)EXTI0_IRQHandler,       
	(uint32_t)EXTI1_IRQHandler,      
	(uint32_t)EXTI2_IRQHandler,           
	(uint32_t)EXTI3_IRQHandler,           
	(uint32_t)EXTI4_IRQHandler ,          
	(uint32_t)DMA_STR0_IRQHandler,        
	(uint32_t)DMA_STR1_IRQHandler,        
	(uint32_t)DMA_STR2_IRQHandler,        
	(uint32_t)DMA_STR3_IRQHandler,        
	(uint32_t)DMA_STR4_IRQHandler,        
	(uint32_t)DMA_STR5_IRQHandler,        
	(uint32_t)DMA_STR6_IRQHandler,        
	(uint32_t)ADC1_2_IRQHandler,          
	(uint32_t)FDCAN1_IT0_IRQHandler,      
	(uint32_t)FDCAN2_IT0_IRQHandler,      
	(uint32_t)FDCAN1_IT1_IRQHandler,      
	(uint32_t)FDCAN2_IT1_IRQHandler,      
	(uint32_t)EXTI9_5_IRQHandler,         
	(uint32_t)TIM1_BRK_IRQHandler,        
	(uint32_t)TIM1_UP_IRQHandler,         
	(uint32_t)TIM1_TRG_COM_IRQHandler,    
	(uint32_t)TIM_CC_IRQHandler,          
	(uint32_t)TIM2_IRQHandler,            
	(uint32_t)TIM3_IRQHandler,            
	(uint32_t)TIM4_IRQHandler,            
	(uint32_t)I2C1_EV_IRQHandler,         
	(uint32_t)I2C1_ER_IRQHandler,         
	(uint32_t)I2C2_EV_IRQHandler,         
	(uint32_t)I2C2_ER_IRQHandler,         
	(uint32_t)SPI1_IRQHandler,            
	(uint32_t)SPI2_IRQHandler,            
	(uint32_t)USART1_IRQHandler,          
	(uint32_t)USART2_IRQHandler,          
	(uint32_t)USART3_IRQHandler,          
	(uint32_t)EXTI15_10_IRQHandler,       
	(uint32_t)RTC_ALARM_IRQHandler,       
	0,                                
	(uint32_t)TIM8_BRK_TIM12_IRQHandler,  
	(uint32_t)TIM8_UP_TIM13_IRQHandler,   
	(uint32_t)TIM8_TRG_COM_TIM14_IRQHandler,
	(uint32_t)TIM8_CC_IRQHandler,         
	(uint32_t)DMA1_STR7_IRQHandler,       
	(uint32_t)FMC_IRQHandler,             
	(uint32_t)SDMMC1_IRQHandler,          
	(uint32_t)TIM5_IRQHandler,            
	(uint32_t)SPI3_IRQHandler,            
	(uint32_t)UART4_IRQHandler,           
	(uint32_t)UART5_IRQHandler,           
	(uint32_t)TIM6_DAC_IRQHandler,        
	(uint32_t)TIM7_IRQHandler,            
	(uint32_t)DMA2_STR0_IRQHandler,       
	(uint32_t)DMA2_STR1_IRQHandler,       
	(uint32_t)DMA2_STR2_IRQHandler,       
	(uint32_t)DMA2_STR3_IRQHandler,       
	(uint32_t)DMA2_STR4_IRQHandler,       
	(uint32_t)ETH_IRQHandler,             
	(uint32_t)ETH_WKUP_IRQHandler,        
	(uint32_t)FDCAN_CAL_IRQHandler,       
	0,                                
	0,                                
	0,                                
	0,                                
	(uint32_t)DMA2_STR5_IRQHandler,       
	(uint32_t)DMA2_STR6_IRQHandler,       
	(uint32_t)DMA2_STR7_IRQHandler,       
	(uint32_t)USART6_IRQHandler,          
	(uint32_t)I2C3_EV_IRQHandler,         
	(uint32_t)I2C3_ER_IRQHandler,         
	(uint32_t)OTG_HS_EP1_OUT_IRQHandler,  
	(uint32_t)OTG_HS_EP1_IN_IRQHandler,   
	(uint32_t)OTG_HS_WKUP_IRQHandler,     
	(uint32_t)OTG_HS_IRQHandler,          
	(uint32_t)DCMI_IRQHandler,            
	0,                                
	0,                                
	(uint32_t)FPU_IRQHandler,             
	(uint32_t)UART7_IRQHandler,           
	(uint32_t)UART8_IRQHandler,           
	(uint32_t)SPI4_IRQHandler,            
	(uint32_t)SPI5_IRQHandler,            
	(uint32_t)SPI6_IRQHandler,            
	(uint32_t)SAI1_IRQHandler,            
	(uint32_t)LTDC_IRQHandler,            
	(uint32_t)LTDC_ER_IRQHandler,         
	(uint32_t)DMA2D_IRQHandler,           
	(uint32_t)SAI2_IRQHandler,            
	(uint32_t)QUADSPI_IRQHandler,         
	(uint32_t)LPTIM1_IRQHandler,          
	(uint32_t)CEC_IRQHandler,             
	(uint32_t)I2C4_EV_IRQHandler,         
	(uint32_t)I2C4_ER_IRQHandler,         
	(uint32_t)SPDIF_IRQHandler,           
	(uint32_t)OTG_FS_EP1_OUT_IRQHandler,  
	(uint32_t)OTG_FS_EP1_IN_IRQHandler,   
	(uint32_t)OTG_FS_WKUP_IRQHandler,     
	(uint32_t)OTG_FS_IRQHandler,          
	(uint32_t)DMAMUX1_OV_IRQHandler,      
	(uint32_t)HRTIM1_MST_IRQHandler,      
	(uint32_t)HRTIM1_TIMA_IRQHandler,     
	(uint32_t)HRTIM_TIMB_IRQHandler,      
	(uint32_t)HRTIM1_TIMC_IRQHandler,     
	(uint32_t)HRTIM1_TIMD_IRQHandler,     
	(uint32_t)HRTIM_TIME_IRQHandler,      
	(uint32_t)HRTIM1_FLT_IRQHandler,      
	(uint32_t)DFSDM1_FLT0_IRQHandler,     
	(uint32_t)DFSDM1_FLT1_IRQHandler,     
	(uint32_t)DFSDM1_FLT2_IRQHandler,     
	(uint32_t)DFSDM1_FLT3_IRQHandler,     
	(uint32_t)SAI3_IRQHandler,            
	(uint32_t)SWPMI1_IRQHandler,          
	(uint32_t)TIM15_IRQHandler,           
	(uint32_t)TIM16_IRQHandler,           
	(uint32_t)TIM17_IRQHandler,           
	(uint32_t)MDIOS_WKUP_IRQHandler,      
	(uint32_t)MDIOS_IRQHandler,           
	(uint32_t)JPEG_IRQHandler,            
	(uint32_t)MDMA_IRQHandler,            
	0,                                
	(uint32_t)SDMMC_IRQHandler,           
	(uint32_t)HSEM0_IRQHandler,           
	0,                                
	(uint32_t)ADC3_IRQHandler,            
	(uint32_t)DMAMUX2_OVR_IRQHandler,     
	(uint32_t)BDMA_CH1_IRQHandler,        
	(uint32_t)BDMA_CH2_IRQHandler,        
	(uint32_t)BDMA_CH3_IRQHandler,        
	(uint32_t)BDMA_CH4_IRQHandler,        
	(uint32_t)BDMA_CH5_IRQHandler,        
	(uint32_t)BDMA_CH6_IRQHandler,        
	(uint32_t)BDMA_CH7_IRQHandler,        
	(uint32_t)BDMA_CH8_IRQHandler,        
	(uint32_t)COMP_IRQHandler,            
	(uint32_t)LPTIM2_IRQHandler,          
	(uint32_t)LPTIM3_IRQHandler,          
	(uint32_t)LPTIM4_IRQHandler,          
	(uint32_t)LPTIM5_IRQHandler,          
	(uint32_t)LPUART_IRQHandler,          
	(uint32_t)WWDG1_RST_IRQHandler,       
	(uint32_t)CRS_IRQHandler,             
	0,                                
	(uint32_t)SAI4_IRQHandler,            
	0,                                 
	0,                                 
	(uint32_t)WKUP_IRQHandler     
}; 

#define FLASH_ACR_LATENCY_7WS                (0x00000007UL)
#define FLASH_LATENCY_DEFAULT                FLASH_ACR_LATENCY_7WS 
#define FLASH_ACR_LATENCY_Pos                (0U)
#define FLASH_ACR_LATENCY_Msk                (0xFUL << FLASH_ACR_LATENCY_Pos)  /*!< 0x0000000F: bit4 is kept only for legacy purpose */
#define FLASH_ACR_LATENCY                    FLASH_ACR_LATENCY_Msk             /*!< Read Latency */

#define RCC_CR_HSION_Pos                       (0U)
#define RCC_CR_HSION_Msk                       (0x1UL << RCC_CR_HSION_Pos)     /*!< 0x00000001 */
#define RCC_CR_HSION                           RCC_CR_HSION_Msk                /*!< Internal High Speed clock enable */

void SystemInit (void)
{
// #if defined (DATA_IN_D2_SRAM)
//  __IO uint32_t tmpreg;
// #endif /* DATA_IN_D2_SRAM */

  /* FPU settings ------------------------------------------------------------*/
  //#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    
    *((volatile uint32_t*)0xE000ED88UL) |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
    //SCB->CPACR |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
  //#endif
  /* Reset the RCC clock configuration to the default reset state ------------*/

   /* Increasing the CPU frequeny */
  if(FLASH_LATENCY_DEFAULT  > (*((volatile uint32_t*)0x52002000UL) | FLASH_ACR_LATENCY))
  //if(FLASH_LATENCY_DEFAULT  > (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)))
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    *((volatile uint32_t*)0x52002000UL) = (*((volatile uint32_t*)0x52002000UL) & (~(FLASH_ACR_LATENCY))) | (FLASH_LATENCY_DEFAULT);
    //MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_DEFAULT));
  }

  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, HSECSSON, CSION, HSI48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON bits */
  RCC->CR &= 0xEAF6ED7FU;

   /* Decreasing the number of wait states because of lower CPU frequency */
  if(FLASH_LATENCY_DEFAULT  < (*((volatile uint32_t*)0x52002000UL) | FLASH_ACR_LATENCY))
  //if(FLASH_LATENCY_DEFAULT  < (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)))
  {
    *((volatile uint32_t*)0x52002000UL) = (*((volatile uint32_t*)0x52002000UL) & (~(FLASH_ACR_LATENCY))) | (FLASH_LATENCY_DEFAULT);
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    //MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_DEFAULT));
  }

// #if defined(D3_SRAM_BASE)
  /* Reset D1CFGR register */
  RCC->D1CFGR = 0x00000000;

  /* Reset D2CFGR register */
  RCC->D2CFGR = 0x00000000;

  /* Reset D3CFGR register */
  RCC->D3CFGR = 0x00000000;
// #else
//   /* Reset CDCFGR1 register */
//   RCC->CDCFGR1 = 0x00000000;

//   /* Reset CDCFGR2 register */
//   RCC->CDCFGR2 = 0x00000000;

//   /* Reset SRDCFGR register */
//   RCC->SRDCFGR = 0x00000000;
// #endif
  /* Reset PLLCKSELR register */
  RCC->PLLCKSELR = 0x02020200;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x01FF0000;
  /* Reset PLL1DIVR register */
  RCC->PLL1DIVR = 0x01010280;
  /* Reset PLL1FRACR register */
  RCC->PLL1FRACR = 0x00000000;

  /* Reset PLL2DIVR register */
  RCC->PLL2DIVR = 0x01010280;

  /* Reset PLL2FRACR register */
  RCC->PLL2FRACR = 0x00000000;
  /* Reset PLL3DIVR register */
  RCC->PLL3DIVR = 0x01010280;

  /* Reset PLL3FRACR register */
  RCC->PLL3FRACR = 0x00000000;

  /* Reset HSEBYP bit */
  RCC->CR &= 0xFFFBFFFFU;

  /* Disable all interrupts */
  RCC->CIER = 0x00000000;

//#if (STM32H7_DEV_ID == 0x450UL)
  /* dual core CM7 or single core line */
  if((*((volatile uint32_t*)0x5C001000UL) & 0xFFFF0000U) < 0x20000000U)
  //if((DBGMCU->IDCODE & 0xFFFF0000U) < 0x20000000U)
  {
    /* if stm32h7 revY*/
    /* Change  the switch matrix read issuing capability to 1 for the AXI SRAM target (Target 7) */
    *((volatile uint32_t*)0x51008108) = 0x000000001U;
  }
//#endif

// #if defined (DATA_IN_D2_SRAM)
//   /* in case of initialized data in D2 SRAM (AHB SRAM) , enable the D2 SRAM clock (AHB SRAM clock) */
// #if defined(RCC_AHB2ENR_D2SRAM3EN)
//   RCC->AHB2ENR |= (RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN | RCC_AHB2ENR_D2SRAM3EN);
// #elif defined(RCC_AHB2ENR_D2SRAM2EN)
//   RCC->AHB2ENR |= (RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN);
// #else
//   RCC->AHB2ENR |= (RCC_AHB2ENR_AHBSRAM1EN | RCC_AHB2ENR_AHBSRAM2EN);
// #endif /* RCC_AHB2ENR_D2SRAM3EN */

//   tmpreg = RCC->AHB2ENR;
//   (void) tmpreg;
// #endif /* DATA_IN_D2_SRAM */

// #if defined(DUAL_CORE) && defined(CORE_CM4)
//   /* Configure the Vector Table location add offset address for cortex-M4 ------------------*/
// #if defined(USER_VECT_TAB_ADDRESS)
//   SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal D2 AXI-RAM or in Internal FLASH */
// #endif /* USER_VECT_TAB_ADDRESS */

// #else

  /*
   * Disable the FMC bank1 (enabled after reset).
   * This, prevents CPU speculation access on this bank which blocks the use of FMC during
   * 24us. During this time the others FMC master (such as LTDC) cannot use it!
   */
  *((volatile uint32_t*)0x52004000) =  0x000030D2;
  //FMC_Bank1_R->BTCR[0] = 0x000030D2;

  /* Configure the Vector Table location -------------------------------------*/
// #if defined(USER_VECT_TAB_ADDRESS)
//   SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal D1 AXI-RAM or in Internal FLASH */
// #endif /* USER_VECT_TAB_ADDRESS */

// #endif /*DUAL_CORE && CORE_CM4*/

}

void Reset_Handler(void)
{
    //ldr   sp, =_estack; may not be needed
    // from c reset handler this may not be proper

    SystemInit();

	//Copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	uint8_t *pDst = (uint8_t*)&_sdata;//SRAM
	uint8_t *pSrc = (uint8_t*)&_la_data;//FLASH
	
	for(uint32_t  i=0; i < size; i++)
	{
		*pDst++ = *pSrc++;
	}
	
	//Init the .bss section to zero in SRAM
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	pDst = (uint8_t*)&_sbss;//SRAM
	
	for(uint32_t  i=0; i < size; i++)
	{
		*pDst++ = 0;
	}
	
	//init for standard library
	__libc_init_array();
	
	//call main()
	main();
}

void Default_Handler(void)
{
	while(1);
}
