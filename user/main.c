#include "app_cfg.h"

//for driver
#include "usart.h"
#include "systick.h"
#include "debug.h"
#include "netconf.h"

#include "helloworld.h"

static void prvClockInit(void);
static void prvnvicInit(void);


int main(void)
{	
	//prvClockInit();
	SystemCoreClockUpdate();
	prvnvicInit();
	Systick_Configuration();
	Usart_Configuration();
    netconf_init();
    
    HelloWorld_init();
#ifdef DEBUG_MSG
    DBG_VERBOS("init success!\r\n");
	funcheckinit();
#endif
	while(1)
	{
        net_Periodic_Handle();
		
#ifdef DEBUG_MSG
		funchecktask();
#endif

	}
	//Should never reach this point!
}

#if 0
/*
 *=============================================================================
 *						  System Clock Configuration
 *=============================================================================
 *		 System Clock source		  | PLL(HSE)
 *-----------------------------------------------------------------------------
 *		 SYSCLK 					  | 72000000 Hz
 *-----------------------------------------------------------------------------
 *		 HCLK					  | 72000000 Hz
 *-----------------------------------------------------------------------------
 *		 PCLK1					  | 36000000 Hz
 *-----------------------------------------------------------------------------
 *		 PCLK2					  | 72000000 Hz
 *-----------------------------------------------------------------------------
 *		 ADCCLK					  | 12000000 Hz
 *-----------------------------------------------------------------------------
 *		 AHB Prescaler			  | 1
 *-----------------------------------------------------------------------------
 *		 APB1 Prescaler 			  | 2
 *-----------------------------------------------------------------------------
 *		 APB2 Prescaler 			  | 1
 *-----------------------------------------------------------------------------
 *		 ADC Prescaler 			  | 6
 *-----------------------------------------------------------------------------
 *		 HSE Frequency			  | 8000000 Hz
 *-----------------------------------------------------------------------------
 *		 PLL MUL					  | 9
 *-----------------------------------------------------------------------------
 *		 VDD						  | 3.3 V
 *-----------------------------------------------------------------------------
 *		 Flash Latency			  | 2 WS
 *-----------------------------------------------------------------------------
 *=============================================================================
*/
//Clock configuration
static void prvClockInit(void)
{
  ErrorStatus HSEStartUpStatus;

  RCC_DeInit();
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);
  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* AHB = DIV1 , HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* APB2 = DIV1, PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* APB1 = DIV2, PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* ADCCLK = PCLK2/6 = 72 / 6 = 12 MHz*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08);

	SystemCoreClockUpdate();
  } else {
    //Cannot start xtal oscillator!
    while(1); 
  }
}
#endif
//nvic configuration
static void prvnvicInit(void)
{
    /* Set the Vector Table base location at 0x08000000 */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

