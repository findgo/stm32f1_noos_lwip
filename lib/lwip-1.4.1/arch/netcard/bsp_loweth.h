

#ifndef __BSP_LOWETH_H_
#define __BSP_LOWETH_H_

#include "stm32f10x.h"
#include "stm32_eth.h"
#include "stdlib.h"

/* Private define ------------------------------------------------------------*/
#define DP83848_PHY        /* Ethernet pins mapped on STM3210C-EVAL Board */
#define PHY_ADDRESS       0x01 /* Relative to STM3210C-EVAL Board */

//#define MII_MODE          /* MII mode for STM3210C-EVAL Board (MB784) (check jumpers setting) */
#define RMII_MODE       /* RMII mode for STM3210C-EVAL Board (MB784) (check jumpers setting) */
// 使能硬件校验
//#define CHECKSUM_BY_HARDWARE

void bsp_lowethInit(void);


#endif

