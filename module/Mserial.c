
 
#include "mserial.h"


typedef struct {
    uint8_t *ptxbuf;
    uint16_t txHead;    //���ͻ�����ͷ
    uint16_t txTail;    //���ͻ�����β
    uint16_t txcount;   //���ͻ�����Ч����
    uint16_t txsize;    //���ͻ�������С

    uint8_t *prxbuf;
    uint16_t rxHead;    //���ջ�����ͷ
    uint16_t rxTail;    //���ջ�����β
    uint16_t rxcount;   //���ջ�����Ч����
    uint16_t rxsize;    //���ջ�������С
}comcfg_t;

//���ͻ����������ֽ���
#define SERIAL_TX_IDLE_AVAIL(ptr)   (ptr->txsize - ptr->txcount)
//���ͻ�������Ч����
#define SERIAL_TX_VALID_AVAIL(ptr)  (ptr->txcount)
//���ͻ������Ƿ��пɶ�����
#define IS_SERIAL_TX_VALID(ptr) (ptr->txcount > 0)

//���ջ����������ֽ���
#define SERIAL_RX_IDLE_AVAIL(ptr)   (ptr->rxsize - ptr->rxcount)
//���ջ�������Ч�ֽ���   
#define SERIAL_RX_VALID_AVAIL(ptr)  (ptr->rxcount)
//���ջ������Ƿ��пɶ�����
#define IS_SERIAL_RX_VALID(ptr) (ptr->rxcount > 0)

//private 
#if COM_USE_NUM >= 1
static uint8_t Com0TxBuf[COM0_TX_MAX_SIZE]; //���ͻ�����
static uint8_t Com0RxBuf[COM0_RX_MAX_SIZE]; //���ջ�����
static comcfg_t comcfg0 = {&Com0TxBuf[0], 0, 0, 0, COM0_TX_MAX_SIZE, &Com0RxBuf[0], 0, 0, 0, COM0_RX_MAX_SIZE}; // serial����ʵ��
#endif
#if COM_USE_NUM >= 2
static uint8_t Com1TxBuf[COM1_TX_MAX_SIZE]; //���ͻ�����
static uint8_t Com1RxBuf[COM1_RX_MAX_SIZE]; //���ջ�����
static comcfg_t comcfg1 = {&Com1TxBuf[0], 0, 0, 0, COM1_TX_MAX_SIZE, &Com1RxBuf[0], 0, 0, 0, COM1_RX_MAX_SIZE}; // serial����ʵ��
#endif
#if COM_USE_NUM >= 3
static uint8_t Com2TxBuf[COM2_TX_MAX_SIZE]; //���ͻ�����
static uint8_t Com2RxBuf[COM2_RX_MAX_SIZE]; //���ջ�����
static comcfg_t comcfg2 = {&Com2TxBuf[0], 0, 0, 0, COM2_TX_MAX_SIZE, &Com2RxBuf[0], 0, 0, 0, COM2_RX_MAX_SIZE}; // serial����ʵ��
#endif
#if COM_USE_NUM >= 4
static uint8_t Com3TxBuf[COM3_TX_MAX_SIZE]; //���ͻ�����
static uint8_t Com3RxBuf[COM3_RX_MAX_SIZE]; //���ջ�����
static comcfg_t comcfg3 = {&Com3TxBuf[0], 0, 0, 0, COM3_TX_MAX_SIZE, &Com3RxBuf[0], 0, 0, 0, COM3_RX_MAX_SIZE}; // serial����ʵ��
#endif




static comcfg_t *GetUseCom(uint8_t COM)
{
    switch(COM){
#if COM_USE_NUM >= 1
    case COM0:
        return &comcfg0;
#endif
#if COM_USE_NUM >= 2
    case COM1:
        return &comcfg1;
#endif
#if COM_USE_NUM >= 3
    case COM2:
        return &comcfg2;
#endif
#if COM_USE_NUM >= 4
    case COM3:
        return &comcfg3;
#endif
    default:
        return &comcfg0;
    }
}



/**
  * @brief  ���ͻ�������������
  * @param  buf: Ҫ���뻺���������� Len: ���뻺���������ݳ��� 
  * @note   
  * @retval number to buf
  */
static uint16_t SerialTxBufPut(comcfg_t *cfg,uint8_t *buf, uint16_t len)
{
    uint16_t availcount;
    
    availcount = SERIAL_TX_IDLE_AVAIL(cfg);
    if (availcount < len) {   // �жϷ��ͻ����Ƿ����㹻�ռ�
        len = availcount;
    }

    availcount = len;
    
    while(availcount){
        cfg->ptxbuf[cfg->txTail] = *buf++;
        cfg->txcount++;
        if (++cfg->txTail >= cfg->txsize){
            cfg->txTail = 0;
        } 
        availcount--;
    }

    return len;
}
/**
  * @brief  ���ͻ�������һ������
  * @param  dat: Ҫ���뻺����������
  * @note   
  * @retval true or false
  */
static uint16_t SerialTxBytePut(comcfg_t *cfg,uint8_t dat)
{
    if (SERIAL_TX_IDLE_AVAIL(cfg) > 0){  // �жϷ��ͻ����Ƿ����㹻�ռ�  
        cfg->ptxbuf[cfg->txTail] = dat;
        cfg->txcount++;
        if (++cfg->txTail >= cfg->txsize){
            cfg->txTail = 0;
        } 
        return 1;
    }

  return 0;
}

/**
  * @brief  ���ͻ�����ȡ��һ���ֽ�����
  * @param  dat: Ҫȡ�����������ݵ�ַ
  * @note   
  * @retval ����ȡ�����ֽ���
  * @note       �жϷ���ȡ����ʱ��Ҫ����
  */
uint16_t SerialTxBytePop(comcfg_t *cfg,uint8_t *dat)
{
    if(IS_SERIAL_TX_VALID(cfg)){//���ͻ������Ƿ�������
        *dat = cfg->ptxbuf[cfg->txHead];
        cfg->txcount--;
        if(++cfg->txHead >= cfg->txsize){
            cfg->txHead = 0;
        }
        return 1; 
    }

    return 0;
}
/**
  * @brief  �����ͻ�������Ч�ֽ���
  * @param  
  * @note   
  * @retval ���ط��ͻ�������Ч�ֽ���
  * @note       
  */
uint16_t serialTxValidAvail(uint8_t COM)
{
    comcfg_t *cfg;
    
    cfg = GetUseCom(COM);
    return SERIAL_TX_VALID_AVAIL(cfg);
}

/**
  * @brief  ����ջ���������һ������
  * @param  dat:���������
  * @note   
  * @retval     ture or false
  * @note       �жϽ��մ�����ʱ�жϵ���
  */
bool SerialRxBytePut(comcfg_t *cfg,uint8_t dat)
{
    if(SERIAL_RX_IDLE_AVAIL(cfg) > 0){
        cfg->prxbuf[cfg->rxTail] = dat;
        cfg->rxcount++;
        if(++cfg->rxTail >= cfg->rxsize){
            cfg->rxTail = 0;
        } 
        return true;
    }

    return false;
}

/**
  * @brief  �ӽ��ջ�����ȡ��len������
  * @param  buf:ȡ�����ݵĻ�����,len: ���ݳ���
  * @note   
  * @retval  ����ȡ�����ݵ�ʵ�ʸ���
  */
static uint16_t SerialRxBufPop(comcfg_t *cfg,uint8_t *buf, uint16_t len)
{
    uint16_t cnt = 0;
    
    while(IS_SERIAL_RX_VALID(cfg) && (cnt < len))//���ջ�����������
    {
        *buf++ = cfg->prxbuf[cfg->rxHead];//�ӽ��ջ�������ȡ����
        cfg->rxcount--;
        if(++cfg->rxHead >= cfg->rxsize){
            cfg->rxHead = 0;
        }
        cnt++;
    }

    return cnt;
}
/**
  * @brief  �ӽ��ջ�����ȡ��len������
  * @param  buf:ȡ�����ݵĻ�����,len: ���ݳ���
  * @note   
  * @retval  ����ȡ�����ݵ�ʵ�ʸ���
  */
uint16_t serialRxValidAvail(uint8_t COM)
{
    comcfg_t *cfg;
    
    cfg = GetUseCom(COM);
    return SERIAL_RX_VALID_AVAIL(cfg);
}

//����һ�����Ϳ��ж�
static void Start_TXEtransmit(uint8_t COM,comcfg_t *cfg)
{
    //���÷�����ɿ��ж�
    if(IS_SERIAL_TX_VALID(cfg)){//������
        switch(COM){
#if COM_USE_NUM >= 1
            case COM0:
                COM0TxIEEnable();
                break;
#endif
#if COM_USE_NUM >= 2
            case COM1:
                COM1TxIEEnable();
                break;
#endif
#if COM_USE_NUM >= 3
            case COM2:
                COM2TxIEEnable();
                break;
#endif
#if COM_USE_NUM >= 4
            case COM3:
                COM3TxIEEnable();
                break;
#endif
        }
    }
}
//����һ����������ж�
static void Start_TXCtransmit(uint8_t COM,comcfg_t *cfg)
{
    uint8_t temp;
        
    if(SerialTxBytePop(cfg,&temp)){
         switch(COM){
#if COM_USE_NUM >= 1
            case COM0:
                COM0PutByte(temp);
                break;
#endif
#if COM_USE_NUM >= 2
            case COM1:
                COM1PutByte(temp);
                break;
#endif
#if COM_USE_NUM >= 3
            case COM2:
                COM2PutByte(temp);
                break;
#endif
#if COM_USE_NUM >= 4
            case COM3:
                COM3PutByte(temp);
                break;
#endif
        }
    }
   
}
/**
  * @brief  TX�������Ϊlen������
  * @param  buf:������ݻ�����,len:������ݳ���
  * @note   
  * @retval  number write
  */
uint16_t Serial_WriteBuf(uint8_t COM,uint8_t *buf,uint16_t len)
{
    uint16_t count;
    halIntState_t bintstate;
    comcfg_t *cfg;

    cfg = GetUseCom(COM);
    ENTER_SAFE_ATOM_CODE(bintstate);
    count = SerialTxBufPut(cfg,buf, len);
    EXIT_SAFE_ATOM_CODE(bintstate);
    
    //���÷�������ж� has some bug
//    Start_TXCtransmit(COM,cfg);

    //���÷�����ɿ��ж�
    Start_TXEtransmit(COM,cfg);
    
    return count;
}



uint16_t Serial_WriteByte(uint8_t COM,uint8_t dat)
{
    uint16_t count;
    halIntState_t bintstate;
    comcfg_t *cfg;

    cfg = GetUseCom(COM);
    ENTER_SAFE_ATOM_CODE(bintstate);
    count = SerialTxBytePut(cfg,dat);
    
    //���÷�������ж� has some bug
//    Start_TXCtransmit(COM,cfg);
    Start_TXEtransmit(COM,cfg);

    EXIT_SAFE_ATOM_CODE(bintstate);

    return count;
}

/**
  * @brief  �ӽ���ȡ��len������
  * @param  buf:�������ݻ�����,len:�������ݳ���
  * @note   
  * @retval  ����ȡ�����ݵ�ʵ�ʸ���
  */
uint16_t Serial_Read(uint8_t COM,uint8_t *buf, uint16_t len)
{
    uint16_t length;
    halIntState_t bintstate;
    comcfg_t *cfg;

    cfg = GetUseCom(COM);
    ENTER_SAFE_ATOM_CODE(bintstate);
    length = SerialRxBufPop(cfg,buf, len);
    EXIT_SAFE_ATOM_CODE(bintstate);
    
    return length;
}

/***********only for Isr callback***********/
/**
  * @brief  ���Ϳ��жϵ��ú���
  * @param  None
  * @note   
  * @note    
  * @note   
  * @retval  None
  */
void COM0_TXE_Isr_callback(void)
{
    uint8_t temp;
    halIntState_t bintstate;

    ENTER_SAFE_ATOM_CODE(bintstate);
    if(SerialTxBytePop(&comcfg0,&temp)){
        COM0PutByte(temp);
    }else{
        COM0TxIEDisable();
    }
    EXIT_SAFE_ATOM_CODE(bintstate);
}
/**
  * @brief  ��������жϻص�����
  * @param  None
  * @note   
  * @retval  None
  */
void COM0_TXC_Isr_callback(void)
{


}
/**
  * @brief  �����жϻص�����
  * @param  None
  * @note   
  * @retval  None
  */
void COM0_RX_Isr_callback(void)
{
    uint8_t temp = COM0GetByte();
    halIntState_t bintstate;

    ENTER_SAFE_ATOM_CODE(bintstate);    
    SerialRxBytePut(&comcfg0,temp);
    EXIT_SAFE_ATOM_CODE(bintstate);
}

