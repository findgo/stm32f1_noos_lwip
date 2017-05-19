/*
********************************************************************************
*                                   
* ģ������ : SPI1����ģ��    
* �ļ����� : bsp_spi1.h
* ��    �� : V0.1
* ˵    �� : ����SPI1��ز���
* �޸ļ�¼ :
*   �汾��  ����        ����      ˵��
*   V0.1    2012-11-26  �쿭      �������ļ�
*
*
********************************************************************************
*/
#ifndef __BSP_SPI1_H
#define __BSP_SPI1_H

/* ����ͷ�ļ� *****************************************************************/
#include "stm32f10x.h"
/* �ⲿ�������� ***************************************************************/
/*
 * RST ---- PA3
 * INT ---- PA1
 * NSS ---- PA4
 * SCK ---- PA5
 * SI  ---- PA7
 * SO  ---- PA6
 */
/*����Ӳ��IO*/
#define HAL_SPI_SCK_PORT 		GPIOA
#define HAL_SPI_SCK_PIN	 		GPIO_Pin_5
#define HAL_SPI_MISO_PORT 		GPIOA
#define HAL_SPI_MISO_PIN	 	GPIO_Pin_6
#define HAL_SPI_MOSI_PORT 		GPIOA
#define HAL_SPI_MOSI_PIN	 	GPIO_Pin_7
#define HAL_SPI_CS_PORT 		GPIOA
#define HAL_SPI_CS_PIN			GPIO_Pin_4
#define HAL_SPI_GPIO_CLOCK_EN()	do{RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA ,ENABLE );}while(0)


#define HAL_SPI_ACTIVE SPI1
#define HAL_SPI_ACTIVE_CLOCK_EN()	do{RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 ,ENABLE );}while(0)

/* �ⲿ������ *****************************************************************/
/* �ⲿ������ *****************************************************************/
/* �ⲿ���� *******************************************************************/
/* �ⲿ�������� ***************************************************************/
void BSP_ConfigSPI1(void);
uint8_t BSP_SPI1SendByte(uint8_t byte);
uint8_t BSP_SPI1ReceiveByte(void);

#endif
/***************************************************************END OF FILE****/
