#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"

#include "dhcp.h"

#if LWIP_NETCONN

#define MAX_BUFFER_LEN 256

char sendbuf[MAX_BUFFER_LEN];

extern struct netif gnetif;

static void dhcp_thread(void *arg)
{
	struct netconn *conn;
	ip4_addr_t ipaddr;
  int ret;
	int strlen = 0;
  
  printf("Ŀ��IP��ַ:%d.%d.%d.%d \t �˿ں�:%d\n\n",      \
          DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT);
  
  printf("�뽫������λ������ΪTCP Server.��User/arch/sys_arch.h�ļ��н�Ŀ��IP��ַ�޸�Ϊ�������ϵ�IP��ַ\n\n");
  
  printf("�޸Ķ�Ӧ�ĺ궨��:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");
  
	while(1)
	{
    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL)
    {
      PRINT_DEBUG("create conn failed!\n");
      vTaskDelay(10);
      continue;
    }

    PRINT_DEBUG("create conn success...\n");
    
    //���������IP��ַ
    IP4_ADDR(&ipaddr,DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3); 			
    
    ret = netconn_connect(conn,&ipaddr,DEST_PORT);	        //���ӷ��������˿ں�5001
    if (ret == -1)
    {
      PRINT_DEBUG("Connect failed!\n");
      netconn_close(conn);
      vTaskDelay(10);
      continue;
    }
    
    PRINT_DEBUG("Connect to server successful!\n");
    
    strlen = sprintf(sendbuf,"A LwIP client Using DHCP Address: %s\n", \
    ipaddr_ntoa((ip_addr_t *)&(gnetif.ip_addr)));
    
    while(1)
    {
      PRINT_DEBUG("%s",sendbuf);
      ret=netconn_write(conn,sendbuf, strlen, NETCONN_NOCOPY);
      if (ret == ERR_OK)
      {
         PRINT_DEBUG("write success...\n");
      }
      vTaskDelay(1000); 
    }
    
//    printf("Connection failed \n");
//    netconn_close(conn); 						//�ر�����
//    netconn_delete(conn);						//ɾ�����ӽṹ
  }
}


void dhcp_netconn_init()
{
  sys_thread_new("dhcp_thread", dhcp_thread, NULL, 2048, 4);
}

#endif /* LWIP_NETCONN*/
