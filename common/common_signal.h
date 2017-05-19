/**
  ******************************************************************************
  * @file   common_signal.h
  * @author  
  * @version 
  * @date    
  * @brief  �жϺ��뻥�����궨��
  ******************************************************************************
  * @attention 	20151110     v1.1   	jgb		�ع�
  ******************************************************************************
  */

#ifndef __COMMON_SIGNAL_H_
#define __COMMON_SIGNAL_H_

#include "common_global.h"
#include "common_def.h"

typedef bool halIntState_t;

#define OS_Enter_Criticial() 	st( __set_PRIMASK(1); )
#define OS_Exit_Criticial()		st( __set_PRIMASK(0); )

#define OSAL_ENABLE_INTERRUPTS()         st( __set_PRIMASK(0); )
#define OSAL_DISABLE_INTERRUPTS()        st( __set_PRIMASK(1); )

#define GLOABLE_INTERRUPT_ENABLED()     ((0 ==  __get_PRIMASK()) ? true : false)

//! \brief The safe ATOM code section macro
#define SAFE_ATOM_CODE(__CODE)     \
    {\
        halIntState_t bintstate = GLOABLE_INTERRUPT_ENABLED();\
        OS_Enter_Criticial();\
        __CODE;\
        if (bintstate)\
        {\
            OS_Exit_Criticial();\
        }\
    }
#define ENTER_SAFE_ATOM_CODE(bintstate)  \
            bintstate = GLOABLE_INTERRUPT_ENABLED();\
            OS_Enter_Criticial();

//! \brief Exit from the safe atom operations
#define EXIT_SAFE_ATOM_CODE(bintstate)           \
            if (bintstate)\
            {\
                OS_Exit_Criticial();\
            }

//! \brief ATOM code section macro
#define ATOM_CODE(__CODE)  \
            {\
                OS_Enter_Criticial();\
                __CODE;\
                OS_Exit_Criticial();\
            }

#define ENTER_ATOM_CODE()  OS_Enter_Criticial();             
//! \brief Exit from the atom operations
#define EXIT_ATOM_CODE()   OS_Exit_Criticial();



#endif
