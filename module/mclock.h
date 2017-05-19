/**
  ******************************************************************************
  * @file   mod_clock.c
  * @author  
  * @version 
  * @date    
  * @brief   ϵͳʱ������
  ******************************************************************************
  * @attention      v1.1    jgb     �ع�        			 20151112  
  * @attention      v1.2    jgb     �������������淶          20170427
  ******************************************************************************
  */
#ifndef __MCLOCK_H_
#define __CLOCK_H_

#include "app_cfg.h"

#define CLOCKTICK_RATE_HZ    (1000)   // 1000hz
#define CLOCKTICK_RATE_MS   (1000 / CLOCKTICK_RATE_HZ)

uint32_t mcu_getCurSysctime(void);
uint32_t mcu_elapsedSystime(void);
void mcu_systime_isr_callback(void);

#endif

