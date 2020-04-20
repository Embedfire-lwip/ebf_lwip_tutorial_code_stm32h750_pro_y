#include "tcpclient.h"
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include <stdio.h>	
#include <string.h>

  
static struct tcp_pcb *client_pcb = NULL;

static void client_err(void *arg, err_t err)
{
  printf("connect error! closed by core!!\n");
	printf("try to connect to server again!!\n");
  
  //����ʧ�ܵ�ʱ���ͷ�TCP���ƿ���ڴ�
  tcp_close(client_pcb);  
  
  //��������
	TCP_Client_Init();
}


static err_t client_send(void *arg, struct tcp_pcb *tpcb)
{
  uint8_t send_buf[]= "This is a TCP Client test...\n";
  
  //�������ݵ�������
  tcp_write(tpcb, send_buf, sizeof(send_buf), 1); 
  
  return ERR_OK;
}

static err_t client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  if (p != NULL) 
  {        
    /* ��������*/
    tcp_recved(tpcb, p->tot_len);
      
    /* ���ؽ��յ�������*/  
    tcp_write(tpcb, p->payload, p->tot_len, 1);
      
    memset(p->payload, 0 , p->tot_len);
    pbuf_free(p);
  } 
  else if (err == ERR_OK) 
  {
    //�������Ͽ�����
    printf("server has been disconnected!\n");
    tcp_close(tpcb);
    
    //��������
    TCP_Client_Init();
  }
  return ERR_OK;
}

static err_t client_connected(void *arg, struct tcp_pcb *pcb, err_t err)
{
  printf("connected ok!\n");
  
  //ע��һ�������Իص�����
  tcp_poll(pcb,client_send,2);
  
  //ע��һ�����պ���
  tcp_recv(pcb,client_recv);
  
  return ERR_OK;
}


void TCP_Client_Init(void)
{        
  ip4_addr_t server_ip;
  /* ����һ��TCP���ƿ�  */
  client_pcb = tcp_new();	  

  IP4_ADDR(&server_ip, 192,168,0,181);

  printf("client start connect!\n");
  
  //��ʼ����
  tcp_connect(client_pcb, &server_ip, TCP_CLIENT_PORT, client_connected); 
  
  //ע���쳣����
  tcp_err(client_pcb, client_err); 	     
}









