

#include "dns_parse.h"
#include "lwip/memp.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"
#include "lwip/timers.h"
#include "lwip/err.h"
#include "lwip/dns.h"
#include "debug.h"

#if LWIP_DNS == 1

// 如果DHCP没开的话， DNS服务器地址要自己设一个
#if LWIP_DHCP == 0
/** DNS server IP address */
#define DNS_SERVER_ADDRSTRING   "208.67.222.222"  /* resolver1.opendns.com */
#endif

// the domain name you want parse
static const char *hostname = "www.baidu.com";
static ip_addr_t hostIpaddr;
static void dns_found_cb(const char *name, ip_addr_t *ipaddr, void *callback_arg);

void dns_parseInit(void)
{
    int ret;
    ip_addr_t dns_server_ipaddr;

#if LWIP_DHCP == 0    
    ip4_addr_set_u32(&dns_server_ipaddr, ipaddr_addr(DNS_SERVER_ADDRSTRING));
    dns_setserver(DNS_MAX_SERVERS - 1,&dns_server_ipaddr);
#endif

    ret = dns_gethostbyname(hostname,&hostIpaddr,dns_found_cb,&hostIpaddr);
    if(ret == ERR_ARG){
        DBG_VERBOS("host ip is: %s\r\n",ipaddr_ntoa(&hostIpaddr));
        return;
    }else if(ret == ERR_OK){
        DBG_ERR("%s:dns_gethostbyname failed,%s\r\n",__FUNCTION__,lwip_strerr(ret));
        return;
    }
    DBG_VERBOS("domain name parse going\r\n");
}

static void dns_found_cb(const char *name, ip_addr_t *ipaddr, void *callback_arg)
{
    if(ipaddr){
        DBG_VERBOS("DNS:lookup \"%s\" ip is: \"%s\"\r\n",name,ipaddr_ntoa(ipaddr)); 
        ((ip_addr_t *)callback_arg)->addr = ipaddr->addr;
   }else{
        DBG_ERR("DNS: could not be found \r\n"); 
   }
}


#endif

