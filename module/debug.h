
/*
 * debug ����ģ�飬ʹ�ú���Ҫ������DEBUG_MSG
 * �����ض���fput,ֱ�ӿ���ͷ�ļ� ����REDIR_FPUT(ch)�ĺ�
 * Ĭ��ֻ���� err, ��warn��verbos��������
 * 
 */


#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "app_cfg.h"
#include "mserial.h"

#define DEBUG_LEVEL_VERBOS  0x01
#define DEBUG_LEVEL_WARN    0x02
#define DEBUG_LEVEL_ERROR   0x04

#ifdef DEBUG_MSG

extern bool dbg_verbos;
extern bool dbg_warn;
extern bool dbg_err;

#define DBG_VERBOS(fmt, args...)                    \
do {                                                \
    if (dbg_verbos) {                           \
        printf(fmt, ##args);                        \
    }                                               \
} while (0)

#define DBG_WARN(fmt, args...)                      \
do {                                                \
    if (dbg_warn) {                             \
        printf(fmt, ##args);                        \
    }                                               \
} while (0)

#define DBG_ERR(fmt, args...)                     \
    do {                                                \
        if (dbg_err) {                              \
            printf(fmt, ##args);                        \
        }                                               \
    } while (0)

//�ض���fput  �û�����
#define REDIR_FPUT(ch)   (void)Serial_WriteByte(COM0,ch);
#else

#define DBG_VERBOS(fmt, args...)
#define DBG_WARN(fmt, args...)
#define DBG_ERR(fmt, args...)

#endif

void dbg_set_dbg_level(uint8_t level);
void dbg_print_dbg_level(void);
void  funcheckinit(void);
void  funchecktask(void);


#endif

