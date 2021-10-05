/*
 * Copyright (c) 2016 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nordic_common.h"
#include "app_error.h"
#include "ble_db_discovery.h"
#include "app_timer.h"
#include "app_util.h"
#include "bsp.h"
#include "bsp_btn_ble.h"
#include "boards.h"
#include "ble.h"
#include "ble_gap.h"
#include "ble_hci.h"
#include "softdevice_handler.h"
#include "ble_advdata.h"
#include "ble_nus_c.h"
#include "mqtt.h"
#include "nrf_delay.h"
#include "SEGGER_RTT.h"
#include "nrf_gpio.h"
#include	"SimplePubSub.h"
#include "gpio_init.h"
#include "nrf.h"
#define CENTRAL_LINK_COUNT      1                               /**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT   0                               /**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#if (NRF_SD_BLE_API_VERSION == 3)
#define NRF_BLE_MAX_MTU_SIZE    GATT_MTU_SIZE_DEFAULT           /**< MTU size used in the softdevice enabling and to reply to a BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST event. */
#endif

#define UART_TX_BUF_SIZE        256                             /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE        256                             /**< UART RX buffer size. */

#define NUS_SERVICE_UUID_TYPE   BLE_UUID_TYPE_VENDOR_BEGIN      /**< UUID type for the Nordic UART Service (vendor specific). */

#define APP_TIMER_PRESCALER     0                               /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE 2                               /**< Size of timer operation queues. */

#define SCAN_INTERVAL           0x00A0                          /**< Determines scan interval in units of 0.625 millisecond. */
#define SCAN_WINDOW             0x0050                          /**< Determines scan window in units of 0.625 millisecond. */
#define SCAN_ACTIVE             1                               /**< If 1, performe active scanning (scan requests). */
#define SCAN_SELECTIVE          0                               /**< If 1, ignore unknown devices (non whitelisted). */
#define SCAN_TIMEOUT            0x0000                          /**< Timout when scanning. 0x0000 disables timeout. */

#define MIN_CONNECTION_INTERVAL MSEC_TO_UNITS(100, UNIT_1_25_MS) /**< Determines minimum connection interval in millisecond. */
#define MAX_CONNECTION_INTERVAL MSEC_TO_UNITS(200, UNIT_1_25_MS) /**< Determines maximum connection interval in millisecond. */
#define SLAVE_LATENCY           0                               /**< Determines slave latency in counts of connection events. */
#define SUPERVISION_TIMEOUT     MSEC_TO_UNITS(4000, UNIT_10_MS) /**< Determines supervision time-out in units of 10 millisecond. */

#define UUID16_SIZE             2                               /**< Size of 16 bit UUID */
#define UUID32_SIZE             4                               /**< Size of 32 bit UUID */
#define UUID128_SIZE            16                              /**< Size of 128 bit UUID */

static ble_nus_c_t              m_ble_nus_c;                    /**< Instance of NUS service. Must be passed to all NUS_C API calls. */
static ble_db_discovery_t       m_ble_db_discovery;             /**< Instance of database discovery module. Must be passed to all db_discovert API calls */
char  AtBuff[50];
char  BtBuff[50];
bool mqtt_flag = 1;
bool Arrow_flag=0;
bool clinet_connect_f=0;
bool connect_flag=0;
bool true_f=0;
extern bool client_available_f;
extern bool connect_ack_f;
extern bool on_buf_f;
extern bool off_buf_f;
extern bool connectOK_f;
extern bool get_data_f;
extern char on_buf_array[70];
bool a_flag=0;
const char* topicInit = "GsmClientTest/init";
const char* topicLed = "GsmClientTest/led";
const char* broker="cloud.smarthoom.com";
char* payload="system is ready";
uint16_t plength=0;

uint8_t get_readline;
uint8_t retry_default=5;
uint8_t m=0;
uint32_t lastReconnectAttempt = 0;
int delay=0;



void sms(void)
{
//		AtBuff[0] = 0x41;	
//    AtBuff[1] = 0x54;
//   	AtBuff[2] = 0x1A;
//	  AtBuff[3] = 0x0D;
//		AtBuff[4] = 0x0A;
//		at_com("ATE0\r\n",1000,100);
//		at_com("AT\r\n",1000,100);
	at_com("AT+CMGF=1\r\n",1000,100);
	at_com("AT+CMGS=\"+989026473264\"\r\n",1000,100);
	at_com(BtBuff,1000,100);
	SEGGER_RTT_WriteString(0,"residm");
	at_com("AT\r\n",4000,100);
	//	at_com("AT\r\n",1000,100);	
}

void RESET(void)
{
		at_com("AT+CFUN=0\r\n",1000,10);
		nrf_delay_ms(12000);
		at_com("AT+CFUN=1\r\n",1000,10);
		nrf_delay_ms(12000);
 	  at_com_check("AT\r\n","\r\nOK\r\n",retry_default,10,10);
}

void GPRS_CON(void)
{
     //RESET();
		
    at_com("AT\r\n",1000,100);
    at_com("ATE0\r\n",1000,100);
    at_com("ATI\r\n",1000,100);
    at_com("AT+GMM\r\n",1000,100);
	
    //  at_com_check("AT\r\n","\r\nOK\r\n",retry_default);
		at_com_check("AT+CMEE=2\r\n","\r\nOK\r\n",retry_default,10,10);
   //at_com_check("AT+GMM\r\n","\r\nSIMCOM_SIM800L\r\n\r\nOK\r\n",retry_default);
		at_com_check("AT+GMM\r\n","\r\nOK\r\n",retry_default,10,10);
		at_com_check("AT+CLTS=1\r\n","\r\nOK\r\n",retry_default,10,10);			 
	  at_com_check("AT+CBATCHK=1\r\n","\r\nOK\r\n",retry_default,10,10);			 
    //at_com_check("AT+CPIN?\r\n","\r\n+CPIN: READY\r\n\r\nOK\r\n",5);	
	  at_com_check("AT+CPIN?\r\n","\r\nOK\r\n",5,10,10);		
    //at_com("ATI\r\n");
		//SEGGER_RTT_WriteString(0,"Waiting for network...\r\n");			 
		//at_com_check("AT+CREG?\r\n","\r\n+CREG: 0,1\r\n\r\nOK\r\n",retry_default);
		at_com_check("AT+CREG?\r\n","\r\nOK\r\n",retry_default,10,10);
		//SEGGER_RTT_WriteString(0,"Network connected\r\n");
	  at_com_check("AT+CIPSHUT\r\n","\r\nSHUT OK\r\n",retry_default,10,100); 
    //at_com("AT+CIPSHUT\r\n"); 
		at_com_check("AT+CGATT=0\r\n","\r\nOK\r\n",retry_default,500,1000); 
		//at_com("AT+CGATT=0\r\n",10,40); 	
		at_com_check("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n","\r\nOK\r\n",retry_default,500,1000);
		//at_com("AT\r\n");
		//SEGGER_RTT_WriteString(0,"residam\r\n");
		at_com_check("AT+SAPBR=3,1,\"APN\",\"mtnirancell\"\r\n","\r\nOK\r\n",retry_default,500,1000); 
		//at_com("AT\r\n");		
		at_com_check("AT+CGDCONT=1,\"IP\",\"mtnirancell\"\r\n","\r\nOK\r\n",retry_default,500,1000); 	
		//nrf_delay_ms(10000);		
		at_com_check("AT+CGACT=1,1\r\n","\r\nOK\r\n",retry_default,500,1000);
		//nrf_delay_ms(5000);
		//at_com("AT\r\n");		
		at_com_check("AT+SAPBR=1,1\r\n","\r\nOK\r\n",retry_default,1000,1000);	
		//at_com("AT\r\n");		
		at_com("AT+SAPBR=2,1\r\n",10,10);
		at_com_check("AT+CGATT=1\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com_check("AT+CIPMUX=1\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com_check("AT+CIPQSEND=1\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com_check("AT+CIPRXGET=1\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com_check("AT+CSTT=\"mtnirancell\",\"\",\"\"\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com_check("AT+CIICR\r\n","\r\nOK\r\n",retry_default,2000,1000);
		at_com("AT+CIFSR;E0\r\n",1000,1000);
		at_com_check("AT+CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"\r\n","\r\nOK\r\n",retry_default,1000,1000);
		SEGGER_RTT_WriteString(0,"success\r\n");
		//at_com_check("AT+CGATT?\r\n","\r\n+CGATT: 1\r\n\r\nOK\r\n",retry_default);
	  at_com_check("AT+CGATT?\r\n","\r\nOK\r\n",retry_default,1000,10);
		at_com("AT+CIFSR;E0\r\n",1000,10);
		//SEGGER_RTT_WriteString(0,"GPRS connected\r\n\r\n");
		//nrf_delay_ms(500);
}
void MQTT_INIT(void)
{
				 at_com_check("AT+CIPRXGET=4,0\r\n","\r\nOK\r\n",retry_default,100,100);
//  	   at_com_check("AT+CIPSTATUS=0\r\n","\r\nOK\r\n",retry_default,1000,100);
		     at_com_check("AT+CIPSTATUS=0\r\n","\r\nOK\r\n",retry_default,100,100);
		     at_com("AT+CIPCLOSE=0,1\r\n",100,100);
			   
		     at_com_check("AT+CIPSSL=0\r\n","\r\nOK\r\n",retry_default,100,100);
}	

bool MQTT_CON(void)
{        
//		       do
//			 { 
//			   at_com_check("AT+CIPRXGET=4,0\r\n","\r\nOK\r\n",retry_default,100,100);
////  	   at_com_check("AT+CIPSTATUS=0\r\n","\r\nOK\r\n",retry_default,1000,100);
//		     at_com_check("AT+CIPSTATUS=0\r\n","\r\nOK\r\n",retry_default,100,100);
//		     at_com("AT+CIPCLOSE=0,1\r\n",100,100);
//			   
//		     at_com_check("AT+CIPSSL=0\r\n","\r\nOK\r\n",retry_default,100,100);
			   at_com("AT+CIPSTART=0,\"TCP\",\"cloud.smarthoom.com\",1883\r\n",10,1000);
	       while(!connectOK_f)
				 {
					 int z=0;
					 z++;
					 SEGGER_RTT_WriteString(0,"");
				 } 
	       connect(broker);
//				 at_com("AT+CIPSEND=0,33\r\n",5000,100);
////			 SGGER_RTT_WriteString(0,"salam\r\n");
//         at_com("",1000,10);
//         if(connect_ack_f)
//				 { //SEGGER_RTT_WriteString(0,"conncet flag\r\n");
					 nrf_delay_ms(1000);
//					  true_f=1;
				   SEGGER_RTT_WriteString(0,"zzzzzzzzzzzzzzz\r\n");
					 return true;
//				 }
				 
	       //else return false;
         					 
//			 }
//        while((!connect_flag)&&(retry_default)); 
	
	
}	

/**
 * @brief Connection parameters requested for connection.
 */
static const ble_gap_conn_params_t m_connection_param =
{
    (uint16_t)MIN_CONNECTION_INTERVAL,  // Minimum connection
    (uint16_t)MAX_CONNECTION_INTERVAL,  // Maximum connection
    (uint16_t)SLAVE_LATENCY,            // Slave latency
    (uint16_t)SUPERVISION_TIMEOUT       // Supervision time-out
};

/**
 * @brief Parameters used when scanning.
 */
static const ble_gap_scan_params_t m_scan_params =
{
    .active   = 1,
    .interval = SCAN_INTERVAL,
    .window   = SCAN_WINDOW,
    .timeout  = SCAN_TIMEOUT,
    #if (NRF_SD_BLE_API_VERSION == 2)
        .selective   = 0,
        .p_whitelist = NULL,
    #endif
    #if (NRF_SD_BLE_API_VERSION == 3)
        .use_whitelist = 0,
    #endif
};

/**
 * @brief NUS uuid
 */
static const ble_uuid_t m_nus_uuid =
  {
    .uuid = BLE_UUID_NUS_SERVICE,
    .type = NUS_SERVICE_UUID_TYPE
  };

/**@brief Function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num     Line number of the failing ASSERT call.
 * @param[in] p_file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(0xDEADBEEF, line_num, p_file_name);
}


/**@brief Function to start scanning.
 */
static void scan_start(void)
{
    ret_code_t ret;

    ret = sd_ble_gap_scan_start(&m_scan_params);
    APP_ERROR_CHECK(ret);

    ret = bsp_indication_set(BSP_INDICATE_SCANNING);
    APP_ERROR_CHECK(ret);
}


/**@brief Function for handling database discovery events.
 *
 * @details This function is callback function to handle events from the database discovery module.
 *          Depending on the UUIDs that are discovered, this function should forward the events
 *          to their respective services.
 *
 * @param[in] p_event  Pointer to the database discovery event.
 */
static void db_disc_handler(ble_db_discovery_evt_t * p_evt)
{
    ble_nus_c_on_db_disc_evt(&m_ble_nus_c, p_evt);
}


/**@brief   Function for handling app_uart events.
 *
 * @details This function will receive a single character from the app_uart module and append it to
 *          a string. The string will be be sent over BLE when the last character received was a
 *          'new line' i.e '\r\n' (hex 0x0D) or if the string has reached a length of
 *          @ref NUS_MAX_DATA_LENGTH.
 */

//void uart_event_handle(app_uart_evt_t * p_event)
//{
//    static uint8_t data_array[BLE_NUS_MAX_DATA_LEN];
//    static uint8_t index = 0;

//    switch (p_event->evt_type)
//    {
//        /**@snippet [Handling data from UART] */
//        case APP_UART_DATA_READY:
//            UNUSED_VARIABLE(app_uart_get(&data_array[index]));
//            index++;

//            if ((data_array[index - 1] == '\n') || (index >= (BLE_NUS_MAX_DATA_LEN)))
//            {
//                while (ble_nus_c_string_send(&m_ble_nus_c, data_array, index) != NRF_SUCCESS)
//                {
//                    // repeat until sent.
//                }
//                index = 0;
//            }
//            break;
//        /**@snippet [Handling data from UART] */
//        case APP_UART_COMMUNICATION_ERROR:
//            APP_ERROR_HANDLER(p_event->data.error_communication);
//            break;

//        case APP_UART_FIFO_ERROR:
//            APP_ERROR_HANDLER(p_event->data.error_code);
//            break;

//        default:
//            break;
//    }
//}


/**@brief Callback handling NUS Client events.
 *
 * @details This function is called to notify the application of NUS client events.
 *
 * @param[in]   p_ble_nus_c   NUS Client Handle. This identifies the NUS client
 * @param[in]   p_ble_nus_evt Pointer to the NUS Client event.
 */

/**@snippet [Handling events from the ble_nus_c module] */
static void ble_nus_c_evt_handler(ble_nus_c_t * p_ble_nus_c, const ble_nus_c_evt_t * p_ble_nus_evt)
{
    uint32_t err_code;
    switch (p_ble_nus_evt->evt_type)
    {
        case BLE_NUS_C_EVT_DISCOVERY_COMPLETE:
            err_code = ble_nus_c_handles_assign(p_ble_nus_c, p_ble_nus_evt->conn_handle, &p_ble_nus_evt->handles);
            APP_ERROR_CHECK(err_code);

            err_code = ble_nus_c_rx_notif_enable(p_ble_nus_c);
            APP_ERROR_CHECK(err_code);
            printf("The device is compatible\r\n");
            break;

        case BLE_NUS_C_EVT_NUS_RX_EVT:
            for (uint32_t i = 0; i < p_ble_nus_evt->data_len; i++)
            {
              //  while (app_uart_put( p_ble_nus_evt->p_data[i]) != NRF_SUCCESS);
            }
            break;

        case BLE_NUS_C_EVT_DISCONNECTED:
            printf("Disconnected\r\n");

            scan_start();
            break;
    }
}
/**@snippet [Handling events from the ble_nus_c module] */

/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
static void sleep_mode_enter(void)
{
    uint32_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    err_code = bsp_btn_ble_sleep_mode_prepare();
    APP_ERROR_CHECK(err_code);

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}

/**@brief Reads an advertising report and checks if a uuid is present in the service list.
 *
 * @details The function is able to search for 16-bit, 32-bit and 128-bit service uuids.
 *          To see the format of a advertisement packet, see
 *          https://www.bluetooth.org/Technical/AssignedNumbers/generic_access_profile.htm
 *
 * @param[in]   p_target_uuid The uuid to search fir
 * @param[in]   p_adv_report  Pointer to the advertisement report.
 *
 * @retval      true if the UUID is present in the advertisement report. Otherwise false
 */
static bool is_uuid_present(const ble_uuid_t *p_target_uuid,
                            const ble_gap_evt_adv_report_t *p_adv_report)
{
    uint32_t err_code;
    uint32_t index = 0;
    uint8_t *p_data = (uint8_t *)p_adv_report->data;
    ble_uuid_t extracted_uuid;

    while (index < p_adv_report->dlen)
    {
        uint8_t field_length = p_data[index];
        uint8_t field_type   = p_data[index + 1];

        if ( (field_type == BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE)
           || (field_type == BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE)
           )
        {
            for (uint32_t u_index = 0; u_index < (field_length / UUID16_SIZE); u_index++)
            {
							
                err_code = sd_ble_uuid_decode(  UUID16_SIZE,
                                                &p_data[u_index * UUID16_SIZE + index + 2],
                                                &extracted_uuid);
                if (err_code == NRF_SUCCESS)
                {
                   

//									if ((extracted_uuid.uuid == p_target_uuid->uuid)
//                        && (extracted_uuid.type == p_target_uuid->type))
                          // printf("extracted=%x , p_target=%x\r\n",extracted_uuid.uuid,p_target_uuid->uuid);
                          if ((extracted_uuid.uuid == 0x180A)&&(p_target_uuid->uuid==0x1523))
      
									{
                        return true;
                    }
                }
            }
        }

        else if ( (field_type == BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE)
                || (field_type == BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE)
                )
        {
            for (uint32_t u_index = 0; u_index < (field_length / UUID32_SIZE); u_index++)
            {
                err_code = sd_ble_uuid_decode(UUID16_SIZE,
                &p_data[u_index * UUID32_SIZE + index + 2],
                &extracted_uuid);
                if (err_code == NRF_SUCCESS)
                {
                    if ((extracted_uuid.uuid == p_target_uuid->uuid)
                        && (extracted_uuid.type == p_target_uuid->type))
                    {
                        return true;
                    }
                }
            }
        }

        else if ( (field_type == BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE)
                || (field_type == BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE)
                )
        {
            err_code = sd_ble_uuid_decode(UUID128_SIZE,
                                          &p_data[index + 2],
                                          &extracted_uuid);
            if (err_code == NRF_SUCCESS)
            {
                if ((extracted_uuid.uuid == p_target_uuid->uuid)
                    && (extracted_uuid.type == p_target_uuid->type))
                {
                    return true;
                }
            }
        }
        index += field_length + 1;
    }
    return false;
}








/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
				 
    uint32_t              err_code;
    const ble_gap_evt_t * p_gap_evt = &p_ble_evt->evt.gap_evt;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_ADV_REPORT:
        {
            const ble_gap_evt_adv_report_t * p_adv_report = &p_gap_evt->params.adv_report;

           
				//mac check
           
          if (is_uuid_present(&m_nus_uuid, p_adv_report))
					{
					 if((p_adv_report->peer_addr.addr[5]==0xDD)&&
						 (p_adv_report->peer_addr.addr[4]==0x08)&&
					 (p_adv_report->peer_addr.addr[3]==0x55)&&
					 (p_adv_report->peer_addr.addr[2]==0x27)&&
					 (p_adv_report->peer_addr.addr[1]==0xE7)&&
					 (p_adv_report->peer_addr.addr[0]==0x88))

					{

                err_code = sd_ble_gap_connect(&p_adv_report->peer_addr,
                                              &m_scan_params,
                                              &m_connection_param);

                if (err_code == NRF_SUCCESS)
                {
                    // scan is automatically stopped by the connect
                    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
                    APP_ERROR_CHECK(err_code);
                    printf("Connecting to target %02x%02x%02x%02x%02x%02x\r\n",
                             p_adv_report->peer_addr.addr[5],
                             p_adv_report->peer_addr.addr[4],
                             p_adv_report->peer_addr.addr[3],
                             p_adv_report->peer_addr.addr[2],
                             p_adv_report->peer_addr.addr[1],
                             p_adv_report->peer_addr.addr[0]
                             );
									
                }
							}
            }
        }break; // BLE_GAP_EVT_ADV_REPORT

        case BLE_GAP_EVT_CONNECTED:
            //NRF_LOG_DEBUG("Connected to target\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
            APP_ERROR_CHECK(err_code);

            // start discovery of services. The NUS Client waits for a discovery result
            err_code = ble_db_discovery_start(&m_ble_db_discovery, p_ble_evt->evt.gap_evt.conn_handle);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_CONNECTED

        case BLE_GAP_EVT_TIMEOUT:
            if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_SCAN)
            {
                //NRF_LOG_DEBUG("Scan timed out.\r\n");
                scan_start();
            }
            else if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_CONN)
            {
                printf("Connection Request timed out.\r\n");
            }
            break; // BLE_GAP_EVT_TIMEOUT

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            // Pairing not supported
            err_code = sd_ble_gap_sec_params_reply(p_ble_evt->evt.gap_evt.conn_handle, BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP, NULL, NULL);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_SEC_PARAMS_REQUEST

        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
            // Accepting parameters requested by peer.
            err_code = sd_ble_gap_conn_param_update(p_gap_evt->conn_handle,
                                                    &p_gap_evt->params.conn_param_update_request.conn_params);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
            //NRF_LOG_DEBUG("GATT Client Timeout.\r\n");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTC_EVT_TIMEOUT

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
            //NRF_LOG_DEBUG("GATT Server Timeout.\r\n");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_TIMEOUT

#if (NRF_SD_BLE_API_VERSION == 3)
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            err_code = sd_ble_gatts_exchange_mtu_reply(p_ble_evt->evt.gatts_evt.conn_handle,
                                                       NRF_BLE_MAX_MTU_SIZE);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST
#endif

        default:
            break;
    }
}

/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the scheduler in the main loop after a BLE stack event has
 *          been received.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    on_ble_evt(p_ble_evt);
    bsp_btn_ble_on_ble_evt(p_ble_evt);
    ble_db_discovery_on_ble_evt(&m_ble_db_discovery, p_ble_evt);
    ble_nus_c_on_ble_evt(&m_ble_nus_c,p_ble_evt);
}

/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    uint32_t err_code;

    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

    ble_enable_params_t ble_enable_params;
    err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT,
                                                    PERIPHERAL_LINK_COUNT,
                                                    &ble_enable_params);
    APP_ERROR_CHECK(err_code);

    //Check the ram settings against the used number of links
    CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);

    // Enable BLE stack.
#if (NRF_SD_BLE_API_VERSION == 3)
    ble_enable_params.gatt_enable_params.att_mtu = NRF_BLE_MAX_MTU_SIZE;
#endif
    err_code = softdevice_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for handling events from the BSP module.
 *
 * @param[in] event  Event generated by button press.
 */
void bsp_event_handler(bsp_event_t event)
{
    uint32_t err_code;
    switch (event)
    {
        case BSP_EVENT_SLEEP:
            sleep_mode_enter();
            break;

        case BSP_EVENT_DISCONNECT:
            err_code = sd_ble_gap_disconnect(m_ble_nus_c.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            if (err_code != NRF_ERROR_INVALID_STATE)
            {
                APP_ERROR_CHECK(err_code);
            }
            break;

        default:
            break;
    }
}

///**@brief Function for initializing the UART.
// */
//static void uart_init(void)
//{
//    uint32_t err_code;

//    const app_uart_comm_params_t comm_params =
//      {
//        .rx_pin_no    = RX_PIN_NUMBER,
//        .tx_pin_no    = TX_PIN_NUMBER,
//        .rts_pin_no   = RTS_PIN_NUMBER,
//        .cts_pin_no   = CTS_PIN_NUMBER,
//        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
//        .use_parity   = false,
//        .baud_rate    = UART_BAUDRATE_BAUDRATE_Baud115200
//      };

//    APP_UART_FIFO_INIT(&comm_params,
//                        UART_RX_BUF_SIZE,
//                        UART_TX_BUF_SIZE,
//                        uart_event_handle,
//                        APP_IRQ_PRIORITY_LOWEST,
//                        err_code);

//    APP_ERROR_CHECK(err_code);
//}

/**@brief Function for initializing the NUS Client.
 */
static void nus_c_init(void)
{
    uint32_t         err_code;
    ble_nus_c_init_t nus_c_init_t;

    nus_c_init_t.evt_handler = ble_nus_c_evt_handler;

    err_code = ble_nus_c_init(&m_ble_nus_c, &nus_c_init_t);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing buttons and leds.
 */
static void buttons_leds_init(void)
{
    bsp_event_t startup_event;

    uint32_t err_code = bsp_init(BSP_INIT_LED,
                                 APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                                 bsp_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_btn_ble_init(NULL, &startup_event);
    APP_ERROR_CHECK(err_code);
}


/** @brief Function for initializing the Database Discovery Module.
 */
static void db_discovery_init(void)
{
    uint32_t err_code = ble_db_discovery_init(db_disc_handler);
    APP_ERROR_CHECK(err_code);
}

/** @brief Function for the Power manager.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

void mqttCallback(char* topic, char*payload ,uint16_t len) {
//  SerialMon.print("Message arrived [");
//  SerialMon.print(topic);
//  SerialMon.print("]: ");
//  SerialMon.write(payload,len);
//  SerialMon.println();


//    String input = b2s(payload, len);
//    if (input == "on" || input=="ON")
//  {
//   digitalWrite(LED_PIN,HIGH);
//  mqtt.publish(topicLedStatus, "LED IS ON");
//  }
//   if (input == "off"|| input == "OFF") {
//  digitalWrite(LED_PIN,0);
//  mqtt.publish(topicLedStatus, "LED IS OFF");
//  }
   
}




int main(void)
{	

//		SEGGER_RTT_WriteString(0,"1\r\n");
//		char AtBuff[20];
//		sprintf(AtBuff,"AT\r\n");
//		getReply(AtBuff,1000);
//	  nrf_drv_gpiote_init();
//	  nrf_gpio_pin_dir_set(23, NRF_GPIO_PIN_DIR_OUTPUT);
	  //gpio_init();

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, NULL);
	  my_timer_start();
		uart_init();		
		buttons_leds_init();
	  nrf_gpio_cfg_output(23);
	  nrf_gpio_pin_dir_set(23, NRF_GPIO_PIN_DIR_OUTPUT);
		nrf_gpio_pin_clear(23);
	  nrf_delay_ms(1000);
	  nrf_gpio_pin_set(23);
		db_discovery_init();
		ble_stack_init();
		nus_c_init();

	  //gpio_init();
	  GPRS_CON();
//	  MQTT_CALLBACK_SIGNATURE(*mqttCallback);

//	  if(connectOK_f)
//		{
//			SEGGER_RTT_WriteString(0,"connect is ok\r\n");
//		}
		MQTT_INIT();
		
		
//char buf10[20]="AT+CFUN=";
//int i=0;	
//int c=1;	
//char d;	
//char buf11[50]="ali";
//sprintf(BtBuff,"%d",c);	
//char*buf12="mmd";
////char buf13[20]=	
//	for(i;i<strlen(buf10);i++)
//	{
//		buf11[i]=buf10[i];
//	}
//	buf11[i]=BtBuff[0];
//	buf11[i+1]='\r\n';
//	
//	sprintf(BtBuff,"s=%s",buf11);
//	SEGGER_RTT_WriteString(0,BtBuff);
//	at_com(buf11,1,100);
	
		//SEGGER_RTT_WriteString(0,"2\r\n");
    // Start scanning for peripherals and initiate connection
    // with devices that advertise NUS UUID.
		//printf("Uart_c Scan started\r\n");

		// scan_start();

//	AtBuff = "AT\r\n" ;
//	sprintf(AtBuff,"AT+CMGS=\"+989026473264\"\r\n");
//  	
	
// 	AT+CMGF=1	
	
//	AtBuff[0] = 0x41;
//	AtBuff[1] = 0x54;
//	AtBuff[2] = 0x2B;
//	AtBuff[3] = 0x43;
//	AtBuff[4] = 0x4D;
//	AtBuff[5] = 0x47;
//	AtBuff[6] = 0x46;
//	AtBuff[2] = 0x3D;
//	AtBuff[2] = 0x31;
//	AtBuff[2] = 0x0D;
//	AtBuff[3] = 0x0A;
//	//AtBuff[4] = 0x;
		
//	ATE0		
		
//	AtBuff[0] = 0x41;
//	AtBuff[1] = 0x54;
//	AtBuff[2] = 0x45;
//	AtBuff[3] = 0x30;
//	AtBuff[4] = 0x0D;
//	AtBuff[5] = 0x0A;

//	CTRL+Z
//	AtBuff[0] = 0x41;
//	AtBuff[1] = 0x42;
//	AtBuff[2] = 0x43;
//	AtBuff[3] = 0x1A;
//	AtBuff[4] = 0x0D;
//	AtBuff[5] = 0x0A;


//	AtBuff[3] = 0x1A;
//	AtBuff[4] = 0x0D;
//	AtBuff[5] = 0x0A;


//	getReply(AtBuff,NULL, (uint16_t) 10);
//  nrf_delay_ms(100);
	
	
//  sprintf(AtBuff,"AT+CMGF=1\r\n");
//	getReply(AtBuff,NULL, (uint16_t) 10);
		
//	at_com("AT+CMGF=1\r\n");
//  at_com("AT+CMGS=\"+989026473264\"\r\n");
//  at_com("0x1A\r\n");

		
		
		
		
		
		
		
		
	
		
		
		
		
		
		
		
//		

//		
//	at_com("AT+CFUN=0\r\n");
//	at_com("AT+CFUN=1\r\n");
//	nrf_delay_ms(1000);
//	at_com_check("AT\r\n","\r\nOK\r\n");
		


    for (;;)
    { 
//		    if(connectOK_f)
//		    {
//		    	SEGGER_RTT_WriteString(0,"connect is ok\r\n");
//		    }
      
			//SEGGER_RTT_WriteString(0,"for\r\n");
 		  if(!connect_ack_f)
			 { //SEGGER_RTT_WriteString(0,"tu if\r\n");
		     uint32_t t = millis();
         if (t - lastReconnectAttempt > 20000L) 
					 { //readserver();
           lastReconnectAttempt = t;
           if (MQTT_CON())
						 {   SEGGER_RTT_WriteString(0,"mqttcon\r\n");
						      subscribe(topicLed);
							   //readserver();
//							 GF("+CIPSEND="), 0, ',', 33);
             lastReconnectAttempt = 0;
             }
						 
           }
			    nrf_delay_ms(100);
         
			}	
			    
//        if(client_available_f&&get_data_f)
//				{ SEGGER_RTT_WriteString(0,"hastammmmmmmmmmmmmmmmmm\r\n");
//				  readserver2();
//				}
				loop();
			  //SEGGER_RTT_WriteString(0,"hastammmmmmmmmmmmmmmmmm\r\n");
			 
//		if(connect_ack_f)
//		{
//      if(client_available_f)
// 			{    
////				at_com("AT+CIPRXGET=4,0\r\n",100,10);
//				  SEGGER_RTT_WriteString(0,"request\r\n");
//				  at_com("AT+CIPRXGET=4,0\r\n",100,10);
//				  nrf_delay_ms(100);
//				  if(on_buf_f)
//					{ on_buf_f=0;
//						SEGGER_RTT_WriteString(0,"LED is ON\r\n");
//						at_com("AT+CIPRXGET=2,0,23\r\n",100,10);
//					}
//					else if(off_buf_f)
//					{ 
//						off_buf_f=0;
//						SEGGER_RTT_WriteString(0,"LED is OFF\r\n");
//						at_com("AT+CIPRXGET=2,0,24\r\n",100,10);
//					}
//				
//				  client_available_f=0;
//			}	
//		}			
      
			while(mqtt_flag)
			{       
				
//				       {
//								    for(int i=0;i<strlen(on_buf_array);i++)
//                    {
//											//on_buf_array[i]=data_array[i];
//											sprintf(BtBuff,"h=%d\r\n",on_buf_array[i]);
//											SEGGER_RTT_WriteString(0,BtBuff);
//										}	
//							 }

//		          plength=strlen(payload);
//				      publish(topicInit,payload,plength);
//				      nrf_delay_ms(1000);
				        
//						char data_array1[4]={32,2,10,13};
//				    char data_array2[6]={32,2,0,0,10,13};
//				    SEGGER_RTT_WriteString(0,"result=");
//            for(int i=0;i<strlen(data_array1);i++)
//	          {
//				    sprintf(BtBuff,"%c",data_array1[i]);
//				    SEGGER_RTT_WriteString(0,BtBuff);
////	          	  if(i==strlen(data_array1))
////	          	 {
////				    sprintf(BtBuff,"%c\r\n",data_array1[i]);
////				    SEGGER_RTT_WriteString(0,BtBuff);
////	          	 }
//	          }
//						if(strcmp(data_array1,data_array2)==0)
//						{
//							SEGGER_RTT_WriteString(0,"mosavi\r\n");
//						}
				
//				
//					at_com("AT\r\n",1000,100);
//		 			at_com("ATE0\r\n",1000,100);
//		 		 	at_com("ATI\r\n",1000,100);
//					at_com("AT+GMM\r\n",1000,100);
				
//			 at_com("AT\r\n");
//	     at_com_check("AT\r\n","\r\n0K\r\n",2);
		     
//		   at_com("AT+CFUN=0\r\n");
//		   at_com("AT+CFUN=1\r\n");
//			 nrf_delay_ms(1000);
//		   at_com_check("AT\r\n","\r\nOK\r\n",retry_default);
//			 at_com_check("ATE\r\n","\r\nOK\r\n",retry_default);
//       connecting to irancell service	 
//				 GPRS_CON();
//			 millis();
//			 uint32_t nalis=millis();
		     
//         sprintf(BtBuff,"timer=%d\r\n",millis());
//	       SEGGER_RTT_WriteString(0,BtBuff);	
//	       nrf_delay_ms(16000);
//         sprintf(BtBuff,"timer=%d\r\n",millis());
//	       SEGGER_RTT_WriteString(0,BtBuff);
//				 nrf_delay_ms(8000);
//       at_com("fgijhogrhjgigigg\r\n");
//       at_com("\r\n");
		
	
	
//			SEGGER_RTT_WriteString(0,"Connecting to cloud.smarthoom.com\r\n");
	
//		  do
//			{
//		  	at_com_check("AT+CIPRXGET=4,0\r\n","\r\n+CIPRXGET: 4,0,0\r\n\r\nOK\r\n",retry_default);
//		  	at_com_check("AT+CIPSTATUS=0\r\n","\r\n+CIPSTATUS: 0,,\"\",\"\",\"\",\"INITIAL\"\r\n\r\nOK\r\n",retry_default);
//		  	at_com("AT+CIPCLOSE=0,1\r\n");
//		  	at_com_check("AT+CIPSSL=0\r\n","\r\nOK\r\n",retry_default);
//			}
//	    while(!at_com_check("AT+CIPSTART=0,\"TCP\",\"cloud.smarthoom.com\",1883\r\n","\r\n0, CONNECT OK\r\n\r\nOK\r\n",0));
			
//			at_com_check("AT+CIPRXGET=4,0\r\n","\r\nOK\r\n",retry_default);

//		 	sms();

       				
			
			
//			at_com("A",100,100);
//			a_flag=1;
//			at_com("T\r\n",100,100);
//			
			
			
//			nrf_delay_ms(1000);
//		  readline((ui nt16_t) 500);

//	    at_com_check(NULL,"\r\n0, CONNECT OK\r\n\r\nOK\r\n",1);
//	    at_com_check("AT\r\n","\r\nOK\r\n\r\n0, CONNECT OK\r\n",retry_default);
//	    at_com_check("AT\r\n","\r\nOK\r\n",retry_default);
			
			
//			 				 
//      nrf_delay_ms(1000);
//      at_com_check("AT\r\n","\r\nOK\r\n",retry_default);	
//      Arrow_flag=1;
	

//      nrf_delay_ms(4000);
//      sprintf(BtBuff,"connect_flag=%d\r\n",connect_flag);
//      SEGGER_RTT_WriteString(0,BtBuff);


//			if(connect_flag)
//				{



//							nrf_delay_ms(30000);
//							at_com("AT\r\n",4000,10);
//					    at_com("AT\r\n",1000,100);
//		 			    at_com("ATE0\r\n",1000,100);
//		 		 	    at_com("ATI\r\n",1000,100);
//					    at_com("AT+GMM\r\n",1000,100);
//						at_com(BtBuff,20,20);
//							do{
//									at_com_che6ck("AT+CIPRXGET=4,0\r\n","\r\nOK\r\n",retry_default,20,20);
//									at_com("AT+CIPSTATUS=0\r\n",20,20);
//								at_com("AT\r\n",20,20);
//								m++;
//								}
//							while(m<100);
 					
		
//		nrf_delay_ms(1000);
//		at_com("AT\r\n");
//		SEGGER_RTT_WriteString(0,"RESIDAM\r\n");

//		at_com("dsdsadasdsddsdsa\r\n");
// 		at_com("<16><31><\\0><4>MQTT<4><2><\\0>\r\n",10000,10);

//		at_com("  		\r\n",10,10);
//	  SEGGER_RTT_WriteString(0,"RESIDAM\r\n");
//		nrf_delay_ms(10000);
//		at_com("<15><\\0><19>cloud.smarthoom.com\r\n");
//  	at_com("AT+CIPRXGET=4,0\r\n");
//		Arrow_flag=0;
//		at_com("AT+CIPSTATUS=0\r\n");
//		at_com("AT+CIPRXGET=4,0\r\n");
			 
//		at_com_check("AT+CIPRXGET=2,0,4\r\n","\r\n+CIPRXGET: 2,0,4,0\r\n");
				 
			mqtt_flag=0; 
  	 }

		 
		 
		 
		 
		 
		 
		 
		 
        power_manage();
    }
}