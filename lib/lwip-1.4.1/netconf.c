/* Includes ------------------------------------------------------------------*/
#include "lwip/memp.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"
#include "lwip/timers.h"
#include "ethernetif.h"

#include "app_cfg.h"
#include "arch/sys_arch.h"
#include <stdio.h>
#include "netconf.h"
#include "bsp_loweth.h"

#define MAX_DHCP_TRIES	4


/* Private macro -------------------------------------------------------------*/
static struct netif netif;
static uint32_t IPaddress = 0;



static void TcpipInitDone(void *arg);
static void net_pkt_intConfig(void);


/** * @brief Init_LwIP initialize the LwIP */
void netconf_init(void) 
{  
    struct ip_addr ipaddr;  
    struct ip_addr netmask;  
    struct ip_addr gw; 
    uint8_t macaddress[6]={'A','R','M','E','T','H'}; 

    bsp_lowethInit(); // ��ʼ������GPIO �ж� DMA�ȵײ�
    net_pkt_intConfig(); // �������ݽ����ж�
    // ��ʼ��
#if NO_SYS
    lwip_init();  
#else
    sys_sem_t sem;

    //sys_sem_new(&sem, 0);
    tcpip_init(NULL, NULL);
    //sys_sem_wait(&sem);
    //sys_sem_free(&sem);
#endif


#if LWIP_DHCP /* ����DHCP������ */
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#else
    /* ���þ�̬IP */
/*
    IP4_ADDR(&ipaddr, 192, 168, 3, 116); // ��������ӿڵ�ip��ַ  
    IP4_ADDR(&netmask, 255, 255, 255, 0);    // ��������  
    IP4_ADDR(&gw, 192, 168, 3, 1);   // ����  
*/
    inet_aton("192.168.1.116",&ipaddr);
	inet_aton("255.255.255.0",&netmask);
	inet_aton("192.168.1.1",&gw);

#endif
      Set_MAC_Address(macaddress); //����MAC��ַ
 
    // ��ʼ��netcard ��LWIP�Ľӿڣ�����Ϊ����ӿڽṹ�塢ip��ַ��  
    // �������롢���ء�������Ϣָ�롢��ʼ�����������뺯��  
#if !NO_SYS
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input); 
#else
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, ethernet_input);  
#endif 
    // ����Ĭ������  
    netif_set_default(&netif);  

#if LWIP_DHCP
    /*  Creates a new DHCP client for this interface on the first call.
    Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
    the predefined regular intervals after starting the client.
    You can peek in the netif->dhcp struct for the actual DHCP status.*/
    dhcp_start(&netif);
#endif
    netif_set_up(&netif);
}

/**   
* @brief TcpipInitDone wait for tcpip init being done  
*   
* @param arg the semaphore to be signaled  
*/
static void TcpipInitDone(void *arg)
{
#if !NO_SYS
	sys_sem_t *sem;
	sem = arg;
	sys_sem_signal(sem); 
#endif
}  


#if NO_SYS
void net_Periodic_Handle(void)
{
    // ��ѯ�������ݣ�Ҫ�����ж�
    //net_pkt_handle();
    
    /** Handle timeouts for NO_SYS==1 (i.e. without using
     * tcpip_thread/sys_timeouts_mbox_fetch(). Uses sys_now() to call timeout
     * handler functions when timeouts expire.
     *
     * Must be called periodically from your main loop.
     */
    sys_check_timeouts();
}
#endif 

// �жϽӿڵ��ã��������ݰ�
/** * @brief  Ethernet ISR */
void net_pkt_handle(void)
{
  /* Read a received packet from the Ethernet buffers and send it to the lwIP for handling */
    while(ETH_GetRxPktSize() != 0) 
    {     
        ethernetif_input(&netif);
    }
}

/* @brief Display_IPAddress Display IP Address  */
void Display_IPAddress(void) 
{     
	if(IPaddress != netif.ip_addr.addr){
		/* IP ��ַ�����ı�*/
		__IO uint8_t iptab[4];
		
		 /* read the new IP address */
		 IPaddress = netif.ip_addr.addr;
	} 
#if LWIP_DHCP
	else if(IPaddress == 0){  
		// �ȴ�DHCP����IP                  
		/* If no response from a DHCP server for MAX_DHCP_TRIES times */         
		/* stop the dhcp client and set a static IP address */         
		if(netif.dhcp->tries > MAX_DHCP_TRIES){
			/* ����DHCP���Դ��������þ�̬IP���� */
			struct ip_addr ipaddr;
			struct ip_addr netmask;
			struct ip_addr gw;
			dhcp_stop(&netif);
			IP4_ADDR(&ipaddr, 192, 168, 1, 116);
			IP4_ADDR(&netmask, 255, 255, 255, 0);
			IP4_ADDR(&gw, 192, 168, 1, 1);
			netif_set_addr(&netif, &ipaddr , &netmask, &gw); 
		}
	} 
#endif 
}  


// ���������յ����ݰ��ж�
static void net_pkt_intConfig(void)
{
    NVIC_InitTypeDef   NVIC_InitStructure;
            
    /* Enable the Ethernet global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   
}

/* @brief  This function handles ETH interrupt request. */
void ETH_IRQHandler(void)
{
    /* Handles all the received frames */
    net_pkt_handle();

    /* Clear the Eth DMA Rx IT pending bits */
    ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
    ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
}

/* @brief  This function ETH wakeup request. */
void ETH_WKUP_IRQHandler(void)
{


}

