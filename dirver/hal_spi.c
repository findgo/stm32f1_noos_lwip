#include "hal_spi.h"
void SPI1_Init(uint16_t baud)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

    HAL_SPI1_GPIO_CLOCK_EN();	
    HAL_SPI1_ACTIVE_CLOCK_EN();
    
	//--- ����SPI1��SCK,MISO MOSI 
	GPIO_InitStructure.GPIO_Pin = HAL_SPI1_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  // ���ù���
	GPIO_Init(HAL_SPI1_SCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HAL_SPI1_MOSI_PIN;
	GPIO_Init(HAL_SPI1_MOSI_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HAL_SPI1_MISO_PIN;
	GPIO_Init(HAL_SPI1_MISO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	    
    GPIO_InitStructure.GPIO_Pin =  HAL_SPI1_CS_PIN;
	GPIO_Init(HAL_SPI1_CS_PORT, &GPIO_InitStructure);
  
    HAL_SPI1_CS_HIGH();
    
	//--- SPI1
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
#if HAL_SPI1_MODE == 0
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;      //��̬      :ʱ������Ϊ��
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;    //λ����    :λ�ڵ�һ�������غ�
#elif HAL_SPI1_MODE == 1
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;       //��̬      :ʱ������Ϊ��
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;     //λ����    :λ�ڵڶ��������غ�
#elif HAL_SPI1_MODE == 2
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;       //��̬      :ʱ������Ϊ��
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       //λ����    :λ�ڵ�һ���½���
#elif HAL_SPI1_MODE == 3
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;         //��̬      :ʱ������Ϊ��
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;        //λ����    :λ�ڵ�һ���½���
#else
    #error "set SPI1 mode error,it must be (0 - 3)"
#endif

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = baud;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);	
		
	//--- ʹ��SPI1 
	SPI_Cmd(SPI1, ENABLE); 
}

uint8_t SPI1_ReadWrite(uint8_t writedat)
{
	/* Loop while DR register in not emplty */
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, writedat);
	
	/* Wait to receive a byte */
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);
}

void SPI2_Init(uint16_t baud)
{
  	SPI_InitTypeDef SPI_InitStructure;
   	GPIO_InitTypeDef GPIO_InitStructure;

   	//--- ʹ��SPI2
    HAL_SPI2_GPIO_CLOCK_EN();
    HAL_SPI2_ACTIVE_CLOCK_EN();

    //--- ����SPI2��SCK,MISO MOSI 
    GPIO_InitStructure.GPIO_Pin = HAL_SPI2_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  // ���ù���
	GPIO_Init(HAL_SPI2_SCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HAL_SPI2_MOSI_PIN;
	GPIO_Init(HAL_SPI2_MOSI_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HAL_SPI2_MISO_PIN;
	GPIO_Init(HAL_SPI2_MISO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	    
    GPIO_InitStructure.GPIO_Pin =  HAL_SPI2_CS_PIN;
	GPIO_Init(HAL_SPI2_CS_PORT, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	    
    GPIO_InitStructure.GPIO_Pin =  HAL_SPI2_CS_PIN;
	GPIO_Init(HAL_SPI2_CS_PORT, &GPIO_InitStructure);

    HAL_SPI2_CS_HIGH();
	//--- SPI2
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//����		:˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//ģʽ		:����ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						//���ݴ�С	:8λģʽ
#if HAL_SPI2_MODE == 0
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//��̬		:ʱ������Ϊ��
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//λ����	:λ�ڵ�һ�������غ�
#elif HAL_SPI2_MODE == 1
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;       //��̬      :ʱ������Ϊ��
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;     //λ����    :λ�ڵڶ��������غ�
#elif HAL_SPI2_MODE == 2
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;       //��̬      :ʱ������Ϊ��
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       //λ����    :λ�ڵ�һ���½���
#elif HAL_SPI2_MODE == 3
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		    //��̬		:ʱ������Ϊ��
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		//λ����	:λ�ڵ�һ���½���
#else
    #error "set SPI2 mode error,it must be (0 - 3)"
#endif
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								//NSS����	:�ڲ�����
	SPI_InitStructure.SPI_BaudRatePrescaler = baud; 						//�ٶ�		:256����Ƶ��Ϊ�����ģ��
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						//λ����	:�Ӹ��ֽڿ�ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;								//У��		:�˴��������
	SPI_Init(SPI2, &SPI_InitStructure);				    

	//--- SPI1
	SPI_Cmd(SPI2, ENABLE);
}
uint8_t SPI2_ReadWrite(uint8_t writedat)
{					 
   /* Loop while DR register in not emplty */
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

   /* Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(SPI2, writedat);

   /* Wait to receive a byte */
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

   /* Return the byte read from the SPI bus */
   return SPI_I2S_ReceiveData(SPI2);
}	

/************************************************** end of file ***********************************************************/

