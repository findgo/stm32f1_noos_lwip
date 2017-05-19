/**
  ******************************************************************************
  * @file   mtimers.h
  * @author  
  * @version 
  * @date    
  * @brief     ����mclock.h
  ******************************************************************************
  * @attention 	  v1.1    jgb     jiangguobao        20151110
  * @attention      v1.2    jgb     �������������淶          20170427
  ******************************************************************************
  */
/*
;   �ö�ʱ����ʱ�������ɾ��������������Ҫ���µ���start;
;   
;
;
*/


#ifndef __MTIMERS_H_
#define __MTIMERS_H_

#include "app_cfg.h"
#include "mclock.h"

//!< 
#define tm_ms(__x)      ((__x) / CLOCKTICK_RATE_MS)
#define tm_s(__x)       tm_ms((__x) * 1000L)
#define tm_min(__x)     tm_s((__x) * 60L)


typedef struct mtimer_s 
{
    uint32_t start;
    uint32_t timeout;
    bool enable;
}mtimer_t;

//��̬��ʼ��
#define MTIMER_INIT() { 0,0,false }  
//��̬��ʼ��
#define INIT_MTIMER(ptr)			do{\
                                (ptr)->start = 0; \
                                (ptr)->timeout = 0; \
                                (ptr)->enable = false;\
                            }while (0)
// ����һ��mtimer����
#define DELCARE_MTIMER(t) mtimer_t t = MTIMER_INIT()

void mtimer_start(mtimer_t *t,uint32_t timeout);
void mtimer_modify(mtimer_t *t,uint32_t timeout);
void mtimer_del(mtimer_t *t);
bool mtimer_expired(mtimer_t *t);


#endif

