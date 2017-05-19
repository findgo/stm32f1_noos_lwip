/**
  ******************************************************************************
  * @file   commond_bits.h
  * @author  
  * @version 
  * @date    
  * @brief    ����λ�Ʋ������ֽڲ���������λ�������μ�util_bits.h
  ******************************************************************************
  * @attention 	20151110     v1.1   	jgb		�ع�
  ******************************************************************************
  */



#ifndef __COMMON_BITS_H_
#define __COMMON_BITS_H_


#include "common_def.h"

//!< 
#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32)((uint32)((Byte0) & 0x00FF) \
          + ((uint32)((Byte1) & 0x00FF) << 8) \
          + ((uint32)((Byte2) & 0x00FF) << 16) \
          + ((uint32)((Byte3) & 0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define BUILD_UINT8(loByte, hiByte) ((uint8)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)

#define HI_UINT8(a) (((a) >> 4) & 0x0F)
#define LO_UINT8(a) ((a) & 0x0F)

/* takes a byte out of a uint32 : var - uint32,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32( var, ByteNum ) (uint8)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))


//!< 
#define SWAP8_U16(v)					((((uint16_t)(v) & 0xFF00) >> 8) | \
										(((uint16_t)(v) & 0x00FF) << 8))
#define SWAP8_U24(v)					((((uint32_t)(v) & 0x00FF0000) >> 16) | \
										(((uint32_t)(v) & 0x0000FF00) << 0) | \
										(((uint32_t)(v) & 0x000000FF) << 16))
#define SWAP8_U32(v)					((((uint32_t)(v) & 0xFF000000) >> 24) | \
										(((uint32_t)(v) & 0x00FF0000) >> 8) | \
										(((uint32_t)(v) & 0x0000FF00) << 8) | \
										(((uint32_t)(v) & 0x000000FF) << 24))


//! \name binary compatibility  
#define USE_SET_BIT(__x, BitNum) 	((__x) |= (BV(BitNum)))
#define USE_CLR_BIT(__x, BitNum) 	((__x) &= ~(BV(BitNum)))
#define USE_CPL_BIT(__x ,BitNum) 	((__x) ^= (BV(BitNum)))
#define USE_GET_BIT(__x, BitNum) 	(((__x) >> (BitNum)) & 0x01)


#if 0  //�����Ժ�
#define  MEM_B( x )  ( *( (uint8_t *) (x) ) )//�õ�ָ����ַ�ϵ�һ��byte
#define  MEM_W( x )  ( *( (uint16_t *) (x) ) )//�õ�ָ����ַ�ϵ�����byte

//�õ�һ��field�ڽṹ��(struct)�е�ƫ����
#define FPOS( type, field ) ( (dword) &(( type *) 0)-> field )
//�õ�һ���ṹ����field��ռ�õ��ֽ���
#define FSIZ( type, field ) sizeof( ((type *) 0)->field )
//�õ�һ�������ĵ�ַ��word��ȣ�
#define  B_PTR( var )  ( (byte *) (void *) &(var) )
#define  W_PTR( var )  ( (word *) (void *) &(var) )

//��һ����ĸת��Ϊ��д
#define  UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )
	
//�ж��ַ��ǲ���10��ֵ������
#define  DECCHK( c ) ((c) >= '0' && (c) <= '9')
//�ж��ַ��ǲ���16��ֵ������
#define  HEXCHK( c ) ( ((c) >= '0' && (c) <= '9') ||\
                		 ((c) >= 'A' && (c) <= 'F') ||\
						 ((c) >= 'a' && (c) <= 'f') )
						 
//����IO�ռ�ӳ���ڴ洢�ռ�Ľṹ�������������
#define inp(port)         (*((volatile byte *) (port)))
#define inpw(port)        (*((volatile word *) (port)))
#define inpdw(port)       (*((volatile dword *)(port)))
#define outp(port, val)   (*((volatile byte *) (port)) = ((byte) (val)))
#define outpw(port, val)  (*((volatile word *) (port)) = ((word) (val)))
#define outpdw(port, val) (*((volatile dword *) (port)) = ((dword) (val)))
#endif

#endif

