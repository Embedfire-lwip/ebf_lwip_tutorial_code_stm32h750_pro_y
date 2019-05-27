#ifndef __BSP_ETH_H__
#define __BSP_ETH_H__

#include "stm32h7xx_hal.h"

/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"

/**ETH GPIO Configuration    
PC1     ------> ETH_MDC
PA1     ------> ETH_REF_CLK
PA2     ------> ETH_MDIO
PA7     ------> ETH_CRS_DV
PC4     ------> ETH_RXD0
PC5     ------> ETH_RXD1
PB11     ------> ETH_TX_EN
PG13     ------> ETH_TXD0
PG12     ------> ETH_TXD1 
*/

/* Private defines --------------------------------------*/
#define ETH_MDC_Pin                 GPIO_PIN_1        //C1
#define ETH_MDC_GPIO_Port           GPIOC
#define ETH_REF_CLK_Pin             GPIO_PIN_1        //A1
#define ETH_REF_CLK_GPIO_Port       GPIOA
#define ETH_MDIO_Pin                GPIO_PIN_2        //A2
#define ETH_MDIO_GPIO_Port          GPIOA
#define ETH_CRS_DV_Pin              GPIO_PIN_7        //A7
#define ETH_CRS_DV_GPIO_Port        GPIOA
#define ETH_RXD0_Pin                GPIO_PIN_4        //C4
#define ETH_RXD0_GPIO_Port          GPIOC
#define ETH_RXD1_Pin                GPIO_PIN_5        //C5
#define ETH_RXD1_GPIO_Port          GPIOC
#define ETH_TX_EN_Pin               GPIO_PIN_11       //B11
#define ETH_TX_EN_GPIO_Port         GPIOB
#define ETH_TXD0_Pin                GPIO_PIN_13       //G13
#define ETH_TXD0_GPIO_Port          GPIOG
#define ETH_TXD1_Pin                GPIO_PIN_14       //G14
#define ETH_TXD1_GPIO_Port          GPIOG 

/*
	ETH_MDIO -------------------------> PA2
	ETH_MDC --------------------------> PC1
	ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
	ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PA7
	ETH_MII_RXD0/ETH_RMII_RXD0 -------> PC4
	ETH_MII_RXD1/ETH_RMII_RXD1 -------> PC5
	ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PB11
	ETH_MII_TXD0/ETH_RMII_TXD0 -------> PG13
	ETH_MII_TXD1/ETH_RMII_TXD1 -------> PG14
																						*/
/* ETH_MDIO */
#define ETH_MDIO_GPIO_CLK_ENABLE()          __GPIOA_CLK_ENABLE()
#define ETH_MDIO_PORT                       GPIOA
#define ETH_MDIO_PIN                        GPIO_PIN_2
#define ETH_MDIO_AF                         GPIO_AF11_ETH

/* ETH_MDC */
#define ETH_MDC_GPIO_CLK_ENABLE()           __GPIOC_CLK_ENABLE();
#define ETH_MDC_PORT                        GPIOC
#define ETH_MDC_PIN                         GPIO_PIN_1
#define ETH_MDC_AF                          GPIO_AF11_ETH

/* ETH_RMII_REF_CLK */
#define ETH_RMII_REF_CLK_GPIO_CLK_ENABLE()  __GPIOA_CLK_ENABLE();
#define ETH_RMII_REF_CLK_PORT               GPIOA
#define ETH_RMII_REF_CLK_PIN                GPIO_PIN_1
#define ETH_RMII_REF_CLK_AF                 GPIO_AF11_ETH

/* ETH_RMII_CRS_DV */
#define ETH_RMII_CRS_DV_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE();
#define ETH_RMII_CRS_DV_PORT                GPIOA
#define ETH_RMII_CRS_DV_PIN                 GPIO_PIN_7
#define ETH_RMII_CRS_DV_AF                  GPIO_AF11_ETH

/* ETH_RMII_RXD0 */
#define ETH_RMII_RXD0_GPIO_CLK_ENABLE()     __GPIOC_CLK_ENABLE();
#define ETH_RMII_RXD0_PORT                  GPIOC
#define ETH_RMII_RXD0_PIN                   GPIO_PIN_4
#define ETH_RMII_RXD0_AF                    GPIO_AF11_ETH

/* ETH_RMII_RXD1 */
#define ETH_RMII_RXD1_GPIO_CLK_ENABLE()     __GPIOC_CLK_ENABLE();
#define ETH_RMII_RXD1_PORT                  GPIOC
#define ETH_RMII_RXD1_PIN                   GPIO_PIN_5
#define ETH_RMII_RXD1_AF                    GPIO_AF11_ETH

/* ETH_RMII_TX_EN */
#define ETH_RMII_TX_EN_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE();
#define ETH_RMII_TX_EN_PORT                 GPIOB
#define ETH_RMII_TX_EN_PIN                  GPIO_PIN_11
#define ETH_RMII_TX_EN_AF                   GPIO_AF11_ETH

/* ETH_RMII_TXD0 */
#define ETH_RMII_TXD0_GPIO_CLK_ENABLE()     __GPIOG_CLK_ENABLE();
#define ETH_RMII_TXD0_PORT                  GPIOG
#define ETH_RMII_TXD0_PIN                   GPIO_PIN_13
#define ETH_RMII_TXD0_AF                    GPIO_AF11_ETH

/* ETH_RMII_TXD1 */
#define ETH_RMII_TXD1_GPIO_CLK_ENABLE()     __GPIOG_CLK_ENABLE();
#define ETH_RMII_TXD1_PORT                  GPIOG
#define ETH_RMII_TXD1_PIN                   GPIO_PIN_14
#define ETH_RMII_TXD1_AF                    GPIO_AF11_ETH

//MAC��ַ
#define MAC_ADDR0   0x02U
#define MAC_ADDR1   0x00U
#define MAC_ADDR2   0x00U
#define MAC_ADDR3   0x00U
#define MAC_ADDR4   0x00U
#define MAC_ADDR5   0x00U

#define ETH_RX_BUF_SIZE                ETH_MAX_PACKET_SIZE //�������ݵĳ���
#define ETH_TX_BUF_SIZE                ETH_MAX_PACKET_SIZE //�������ݵĳ���
#define ETH_RXBUFNB                    ((uint32_t)4)       //Ҫ�������ݵĸ���
#define ETH_TXBUFNB                    ((uint32_t)4)       //Ҫ�������ݵĸ���

//LAN8720A�ļĴ����궨�� 
//PHY�������ַ
#define LAN8720A_PHY_ADDRESS            0x00
//PHY��ʱʱ��
#define PHY_RESET_DELAY                 ((uint32_t)0x00000FFF)
#define PHY_CONFIG_DELAY                ((uint32_t)0x00000FFF)
//��дPHY�ĵȴ�ʱ��
#define PHY_READ_TO                     ((uint32_t)0x0000FFFF)
#define PHY_WRITE_TO                    ((uint32_t)0x0000FFFF)

//PHY�����Ĵ���
#define PHY_BCR                         ((uint16_t)0x00)   //R0--�������ƼĴ���
#define PHY_BSR                         ((uint16_t)0x01)   //R1--����״̬�Ĵ���
//PHY�������ƼĴ���������
#define PHY_RESET                       ((uint16_t)0x8000)  /*!< PHY Reset */
#define PHY_LOOPBACK                    ((uint16_t)0x4000)  /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)  /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)  /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)  /*!< Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)  /*!< Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION             ((uint16_t)0x1000)  /*!< Enable auto-negotiation function     */
#define PHY_RESTART_AUTONEGOTIATION     ((uint16_t)0x0200)  /*!< Restart auto-negotiation function    */
#define PHY_POWERDOWN                   ((uint16_t)0x0800)  /*!< Select the power down mode           */
#define PHY_ISOLATE                     ((uint16_t)0x0400)  /*!< Isolate PHY from MII                 */

#define PHY_AUTONEGO_COMPLETE           ((uint16_t)0x0020)  /*!< Auto-Negotiation process completed   */
#define PHY_LINKED_STATUS               ((uint16_t)0x0004)  /*!< Valid link established               */
#define PHY_JABBER_DETECTION            ((uint16_t)0x0002)  /*!< Jabber condition detected            */

#define PHY_SPEED_Indication            ((uint16_t)0x001C)

#define LAN8740_10MBITS_HALFDUPLEX      ((uint16_t)0x0004)
#define LAN8740_10MBITS_FULLDUPLEX      ((uint16_t)0x0014)
#define LAN8740_100MBITS_HALFDUPLEX     ((uint16_t)0x0008)
#define LAN8740_100MBITS_FULLDUPLEX     ((uint16_t)0x0018)



//PHY�������/״̬�Ĵ���
#define PHY_SR                          ((uint16_t)0x1F)    /*!< PHY special control/ status register Offset     */

#define PHY_SPEED_STATUS                ((uint16_t)0x0004)  /*!< PHY Speed mask                                  */
#define PHY_DUPLEX_STATUS               ((uint16_t)0x0010)  /*!< PHY Duplex mask                                 */

#define PHY_ISFR                        ((uint16_t)0x1D)    /*!< PHY Interrupt Source Flag register Offset       */
#define PHY_ISFR_INT4                   ((uint16_t)0x0010)  /*!< PHY Link down inturrupt */



#define ETH_RX_BUFFER_SIZE                     (1536UL)


HAL_StatusTypeDef Bsp_Eth_Init(void);


#endif
