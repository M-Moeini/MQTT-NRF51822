/*
This is Hoom's mqtt library for nrf51822
Developed by Mahdi Moeini
mahdimoeini719@gmail.com
Based on adafruit Fona library for arduino
*/
//NORDIC PRE LIBS START.........................................................................
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ble_nus_c.h"
#include "SEGGER_RTT.h"
#include "app_timer.h"
//NORDIC PRE LIBS END...........................................................................
//HOOM LIBS START...............................................................................
#include "SimplePubSub.h"
#include "mqtt.h"
#include "nrf_delay.h"
#include "nrf_drv_timer.h"
//#include "gpio_init.h"
#include "app_uart.h"
#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define UART_TX_BUF_SIZE        256                             /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE        256                             /**< UART RX buffer size. */
#define GATT_MTU_SIZE_DEFAULT 23
#define BLE_NUS_MAX_DATA_LEN           (GATT_MTU_SIZE_DEFAULT - 3) /**< Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */
//static ble_nus_c_t              m_ble_nus_c;                    /**< Instance of NUS service. Must be passed to all NUS_C API calls. */
bool uart_available=1;
bool client_available_f=0;
bool uart_available2;
bool ciprxgt404_f;
bool ciprxgt405_f;
bool ciprxgt402_f;
bool connectOK_f;
bool on_buf_f=0;
bool off_buf_f=0;
bool  replyidx_f=0;
bool	get_data_f=0;
bool	buf_4023_f=0;
bool	buf_4024_f=0;
static uint8_t index = 0;
char replybuffer[255];  ///< buffer for holding replies from the module
extern bool Arrow_flag;
extern bool a_flag;
extern bool connect_flag;
extern bool connect_ack_f;
extern uint8_t* return_buf;
char* buf_4023="\r\n+CIPRXGET: 4,0,23\r\n";
char* buf_4024="\r\n+CIPRXGET: 4,0,24\r\n";	
uint8_t data_array[70];
uint8_t connecAck_data_array[70];
uint8_t ans_buf[70];
//uint8_t	next_data_array[70];
//static uint8_t data_array[BLE_NUS_MAX_DATA_LEN];i
//static uint8_t data_array[100];
char buf[50];
char buf_D[20];
//char AttBuff[2];
char *BttBuff;
uint16_t replyidx=0;
char* buf3="\r\n+CIPRXGET: 1,0\r\n";
char* buf4="\r\n0, CLOSED\r\n";
char* buf5="\r\n+CIPRXGET: 4,0,4\r\n";
char* buf6="\r\n+CIPRXGET: 4,0,5\r\n";
char* buf7="\r\n+CIPRXGET: 4,0,2\r\n";
char* buf8="\r\n0, CONNECT OK\r\n";
char* buf9="\r\n+CIPRXGET: 2,0";
char* on_buf="\r\n+CIPRXGET: 4,0,23\r\n";
char* off_buf="\r\n+CIPRXGET: 4,0,24\r\n";
char  subAck_buf[5]={144,3,0,2,0};
char on_buf_array[70];


//extern  uint8_t data_array[BLE_NUS_MAX_DATA_LEN];





/**@brief Function for initializing the UART.
 */

void uart_event_handle(app_uart_evt_t * p_event)
{     // SEGGER_RTT_WriteString(0,"residam\r\n");

    switch (p_event->evt_type)
    {
        /**@snippet [Handling data from UART] */
        case APP_UART_DATA_READY:
            //SEGGER_RTT_WriteString(0,"a\r\n");
						UNUSED_VARIABLE(app_uart_get(&data_array[index]));
						//sprintf(buf,"d=%c\r\n",data_array[index]);
						//SEGGER_RTT_WriteString(0,buf);
						index++;
		
						//data_array[index - 1] == '\n')
						//index >= (BLE_NUS_MAX_DATA_LEN))
						if (data_array[index-2] == '>')
						{       
							Arrow_flag=1;
//							SEGGER_RTT_WriteString(0,"a\r\n");
//							sprintf(buf,"res=%c\r\n",data_array[index-1]);
//					    SEGGER_RTT_WriteString(0,buf);
							data_array[index] = 0;
							replyidx = index;
							index=0;
//							nrf_delay_ms(500);
//		 	        sprintf(buf_D,"res=%s\r\n",data_array);
//	            SEGGER_RTT_WriteString(0,buf_D);
						
							SEGGER_RTT_WriteString(0,"result=");
							 for(int i=0;i<strlen(data_array);i++)
							 {
									sprintf(buf_D,"%c",data_array[i]);
									SEGGER_RTT_WriteString(0,buf_D);
									if(i==strlen(data_array))
									{
										sprintf(buf_D,"%c\r\n",data_array[i]);
										SEGGER_RTT_WriteString(0,buf_D);
									}
							 }
							 nrf_delay_ms(1);
							 uart_available=1;	

														
							
						}
				
	
			
						else if ((data_array[index - 1] == '\n')&&((index>2)))
						{      
//            		connect_flag=1;
//								if (data_array[11]=='T')
//								{  
//					 					SEGGER_RTT_WriteString(0,"h\r\n");
//										connect_flag=1;
//					
//					 					data_array[index] = 0;
//										replyidx = index;
//										index=0;
//										nrf_delay_ms(500);
//		 								sprintf(buf_D,"res=%s\r\n",data_array);
//	    							SEGGER_RTT_WriteString(0,buf_D);
//							
//										SEGGER_RTT_WriteString(0,"result=");
//   									for(int i=0;i<strlen(data_array);i++)
//										{
//												sprintf(buf_D,"%c",data_array[i]);
//												SEGGER_RTT_WriteString(0,buf_D);
//		 										if(i==strlen(data_array))
//		 										{
//		 												sprintf(buf_D,"%c\r\n",data_array[i]);
//	    											SEGGER_RTT_WriteString(0,buf_D);
//		 										}
//	 									}
//        						nrf_delay_ms(100);
//										uart_available=1;	
//        						uart_available2=1;					
//								}
						
//								SEGGER_RTT_WriteString(0,"b\r\n");
							 
							
//                SEGGER_RTT_WriteString(0,"2\r\n");
//                sprintf(buf,"index=%d\r\n",index-1);
//                SEGGER_RTT_WriteString(0,buf);
//                while (ble_nus_c_string_send(&m_ble_nus_c, data_array, index) != NRF_SUCCESS)
//                {
//                  repeat until sent.
//                }
//	         else {	

//							    if(data_array=="\r\nOK\r\n")
//									{
//										SEGGER_RTT_WriteString(0,"umadi tu\r\n");
//									}
                  replyidx_f=1;
	                data_array[index] = 0;
	                replyidx = index;
	                index=0;
//									for(int i=0; i<strlen(data_array);i++)
//									{
//										next_data_array[i]=data_array[i];
//									}
									
									if(get_data_f)
									{
										get_data_f=0;
										for(int i=0;i<sizeof(data_array);i++)
                    {
										  connecAck_data_array[i]=data_array[i];
									  }
										
									}		
									
//	              nrf_delay_ms(500);
//		 	          sprintf(buf_D,"res=%s\r\n",data_array);
//	              SEGGER_RTT_WriteString(0,buf_D);
							    if (strcmp(data_array,buf3)==0)
									{   
										
										client_available_f=1;
//										connect_flag=1;
										//readserver();
										
										SEGGER_RTT_WriteString(0,"umadi tu\r\n");
									}
									if(strcmp(data_array,buf_4023)==0)
		              { 
		             	   SEGGER_RTT_WriteString(0,"buf4023\r\n");
										buf_4023_f=1;
		              }
									 if(strcmp(data_array,buf_4024)==0)
		              { 
		             	   SEGGER_RTT_WriteString(0,"buf4024\r\n");
										buf_4024_f=1;
		              }
							    if (strcmp(data_array,buf6)==0)
									{   
										
										ciprxgt405_f=1;
										SEGGER_RTT_WriteString(0,"salam bye\r\n");
									}
							    if (strcmp(data_array,buf5)==0)
									{   
										
										ciprxgt404_f=1;

//										SEGGER_RTT_WriteString(0,"salam bye\r\n");
									}
									if (strcmp(data_array,buf7)==0)
									{   
										
										ciprxgt402_f=1;

//										SEGGER_RTT_WriteString(0,"salam bye\r\n");
									}
                  if (strcmp(data_array,buf8)==0)
									{   
										
										connectOK_f=1;
//										SEGGER_RTT_WriteString(0,"salam bye\r\n");
									} 
																	
//								  if ((data_array[0]=='\r\n')&&(data_array[1]=='+')&&(data_array[2]=='C')&&(data_array[3]=='I')
//										&&(data_array[4]=='P')&&(data_array[5]=='R')&&(data_array[6]=='X')&&(data_array[7]=='G')
//									&&(data_array[8]=='E')&&(data_array[9]=='T')&&(data_array[10]==':')&&(data_array[11]==' ')
//									&&(data_array[12]=='2')&&(data_array[13]==',')&&(data_array[14]=='0'))
									
									if (strncmp(data_array,buf9,16)==0)
									{   
										  get_data_f=1;
//										for(int i=0;i<4;i++)
//                    {
//										  connecAck_data_array[i]=next_data_array[i];
//									  }
										SEGGER_RTT_WriteString(0,"dorost mishe\r\n");
										
									}
								  if (strcmp(data_array,on_buf)==0)
									{   
										
										on_buf_f=1;
                    for(int i=0;i<strlen(data_array);i++)
                    {
											  on_buf_array[i]=data_array[i];
//											sprintf(BttBuff,"h=%d\r\n",data_array[i]);
//											SEGGER_RTT_WriteString(0,BttBuff);
										}											
										
									}
									if (strcmp(data_array,off_buf)==0)
									{   
										
										off_buf_f=1; 
										SEGGER_RTT_WriteString(0,"LED is OFF\r\n");
									}


                  if (strcmp(data_array,buf4)==0)
									{ 
										
										connect_ack_f=0;
										connectOK_f=0;
										
										SEGGER_RTT_WriteString(0,"rafti birun\r\n");
									}
//                  if (strcmp(data_array,connect_buf)==0)
//									{ 
////									connect_flag=1;
////										connect_ack_f=1;
//	
//										SEGGER_RTT_WriteString(0,"connect ack\r\n");
//									}
									
								  if (strcmp(data_array,subAck_buf)==0)
									{ 
										
										SEGGER_RTT_WriteString(0,"suback is done\r\n");
									}
									
									
									
	                SEGGER_RTT_WriteString(0,"result=");
                  for(int i=0;i<strlen(data_array);i++)
	                {
											sprintf(buf_D,"%c",data_array[i]);
											SEGGER_RTT_WriteString(0,buf_D);
	                	  if(i==strlen(data_array))
	                	 {
												sprintf(buf_D,"%c\r\n",data_array[i]);
												SEGGER_RTT_WriteString(0,buf_D);
	                	 }
	                }

                  nrf_delay_ms(1);
	                uart_available=1;


//                  sprintf(buf,"last_data=%s",connecAck_data_array);
//                  SEGGER_RTT_WriteString(0,buf);									
				
	                						
							
							
//               index = 0;
//              }   
  					 }		
//						
//					if(Arrow_flag)
//					{
//				     SEGGER_RTT_WriteString(0,"a\r\n");
//             sprintf(buf_D,"%d\r\n",data_array);
//             SEGGER_RTT_WriteString(0,buf_D);
//					}
						 
						 
						 
						
//					if(Arrow_flag)
//					{
//							data_array[index] = 0;
//	            replyidx = index;
//	            index=0;
//					  	nrf_delay_ms(500);
//		 	        sprintf(buf_D,"res=%d\r\n",data_array);
//	            SEGGER_RTT_WriteString(0,buf_D);
//							nrf_delay_ms(100);
//				      uart_available=1;	
//              uart_available2=1;
//					}
//						 
						 
						 
            break;
        /**@snippet [Handling data from UART] */
        case APP_UART_COMMUNICATION_ERROR:
//          SEGGER_RTT_WriteString(0,"2\r\n");
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
//          SEGGER_RTT_WriteString(0,"3\r\n");
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default: 
//          SEGGER_RTT_WriteString(0,"4\r\n");
            break;
			}
}


void uart_init(void)
{	
    uint32_t err_code;

    const app_uart_comm_params_t comm_params =
      {
        .rx_pin_no    = RX_PIN_NUMBER,
        .tx_pin_no    = TX_PIN_NUMBER,
        .rts_pin_no   = RTS_PIN_NUMBER,
        .cts_pin_no   = CTS_PIN_NUMBER,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity   = false,
        .baud_rate    = UART_BAUDRATE_BAUDRATE_Baud9600
      };

    APP_UART_FIFO_INIT(&comm_params,
                        UART_RX_BUF_SIZE,
                        UART_TX_BUF_SIZE,
                        uart_event_handle,
                        APP_IRQ_PRIORITY_LOWEST,
                        err_code);

    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Send a command and return the reply
 *
 * @param send The char* command to send
 * @param timeout Timeout for reading a  response
 * @return uint8_t The response length
 */
uint8_t getReply(char *send ,uint16_t timeout,int mqtt_delay) 
{	
//  flushInput();
    
			
//		if(Arrow_flag)
//				{ 
//					<16><31><\0><4>MQTT<4><2><\0><15><\0><19>cloud.smarthoom.com 
//					
//					<16><31><\\0><4>MQTT<4><2><\\0>
//					<15><\\0><19>cloud.smarthoom.com
					
//					Arrow_flag=0;
//	        AttBuff[0]=0x0A;
//	        AttBuff[1]=0x0B;
//						char	AttBuff[36]={208,0,0,16,31,0,4,77,81,84,84,4,2,0,15,0,19,99,108,111,117,100,46,115,109,97,114,116,104,111,111,109,46,99,111,109};	
//  			  uint8_t	AttBuff[33]={0x10,0x1F,0x0,0x4,'M','Q','T','T',0x4,0x2,0x0,0xF,0x0,0x13,'c','l','o','u','d',0x2E,'s','m','a','r','t','h','o','o','m',0x2E,'c','o','m'};	

//          char	AttBuff[36]={208,0,0,16,3,0,4,77,81,84,4,4,2,0,15,0,19,99,108,111,17,100,46,15,109,97,154,116,104,11,111,109,46,94,111,109};
//				    uart_available=0;
//            connect(broker);
//	        SEGGER_RTT_WriteString(0,"UMADMA\r\n");
//          DEBUG_PRINT(F("\t---> "));
//          DEBUG_PRINTLN(send);

////          mySerial->println(send);
//	          for (int i = 0; i <36; i++)
//	          { 
//							
//								sprintf(buf,"send_koli=%d\r\n", AttBuff[i]);
//								SEGGER_RTT_WriteString(0,buf);							
//								while (app_uart_put((uint8_t) AttBuff[i]) != NRF_SUCCESS);
////						   SEGGER_RTT_WriteString(0,"f\r\n");
//								nrf_delay_ms(mqtt_delay);
//		
//			        sprintf(buf,"send[i]=%c\r\n",send[i]);
//	            SEGGER_RTT_WriteString(0,buf);
//	          }
	
//			    BttBuff = "<15><\\0><19>cloud.smarthoom.com \r\n";
//	
//	
//	       sprintf(buf,"send_koli=%s\r\n",BttBuff);
//	       SEGGER_RTT_WriteString(0,buf);
//	 
//	
//        DEBUG_PRINT(F("\t---> "));
//        DEBUG_PRINTLN(send);

//	      mySerial->println(send);
//	      for (int i = 0; i < strlen(BttBuff); i++)
//	      {
//	
//		
//						while (app_uart_put((uint8_t) BttBuff[i]) != NRF_SUCCESS);
//						nrf_delay_ms(mqtt_delay);
//		
//			      sprintf(buf,"send[i]=%c\r\n",send[i]);
//	          SEGGER_RTT_WriteString(0,buf);
//	      }
//	
//	
//	
	
	
	
//         }
		
		
		
		
		
		
		
		while(uart_available)
		{
			uart_available=0;

	 
	
//    DEBUG_PRINT(F("\t---> "));
//    DEBUG_PRINTLN(send);

//    mySerial->println(send);
			SEGGER_RTT_WriteString(0,"send_koli=");
	    for (int i = 0; i < strlen(send); i++)
	    {    sprintf(buf,"%c",send[i]);
	         SEGGER_RTT_WriteString(0,buf);
	    	   while (app_uart_put((uint8_t) send[i]) != NRF_SUCCESS);
	    	   //nrf_delay_ms(mqtt_delay);
	    	
//	    		sprintf(buf,"send[i]=%c\r\n",send[i]);
//	        SEGGER_RTT_WriteString(0,buf);
	    }
		} 
			
			
	
   
				
    nrf_delay_ms(mqtt_delay);
		




				

//		AttBuff[0] = 0x41;
//    AttBuff[1] = 0x54;
//   	AttBuff[2] = 0x1A;
//	  AttBuff[3] = 0x0D;
//		AttBuff[4] = 0x0A;

//	uint8_t l = readline(timeout);
//  while( !replyidx_f)
//	{	 
//		 SEGGER_RTT_WriteString(0,"ccc\r\n"); 
//	}
//	replyidx_f=0;
	return  replyidx ;
}
/**
 * @brief Read a single line or up to 254 bytes
 *
 * @param timeout Reply timeout
 * @param multiline true: read the maximum amount. false: read up to the second
 * newline
 * @return uint8_t the number of bytes read
 */
uint8_t readline(uint16_t timeout) {
		
	
//uint16_t replyidx=0;
	
  
  // uint8_t reply[20];
//   while (timeout--) {
//    if (replyidx >= 254) 
//     {
//       DEBUG_PRINTLN(F("SPACE"));
//       break;
//     }
//    if(uart_available2){
//    static uint8_t index = 0
//	  uart_available2=0;

//    sprintf(buf_D,"result=%s\r\n",data_array);
//    SEGGER_RTT_WriteString(0,buf_D);
//   	break;
//    UNUSED_VARIABLE(app_uart_get(&data_array[index]));
//    index++;
//    for(int i=0 ; i < sizeof(data_array) ; i++)
//		{
//    		char c = mySerial->read();
//    }
//    
//    if (c == '\r')
//      continue;
//    if (c == 0xA) 
//    {
//    if (replyidx == 0) // the first 0x0A is ignored
//        continue;
//    
//    
//    }
//      replybuffer[replyidx] = c;
//      DEBUG_PRINT(c, HEX); DEBUG_PRINT("#"); DEBUG_PRINTLN(c);
//      replyidx++;
//  	}
				
//   if (timeout == 0) {
//   DEBUG_PRINTLN(F("TIMEOUT"));
//   break;
//   }
//  nrf_delay_ms(1);

//  }

//  data_array[index] = 0; // null term
//  replyidx = index;


//	for(int i=0 ; i < 6; i++)
//	{
//			sprintf(buf_D,"result=%d\n",data_array[i]);
//			SEGGER_RTT_WriteString(0,buf_D);
//	}
//	sprintf(buf_D,"%s",data_array);
//	if(buf_D=="\r\nOK\r\n")
//	{
//  SEGGER_RTT_WriteString(0,"okie\r\n");
//	}
//	
//	SEGGER_RTT_WriteString(0,"result=");
//  for(int i=0;i<strlen(data_array);i++)
//	{
//	sprintf(buf_D,"%c",data_array[i]);
//	SEGGER_RTT_WriteString(0,buf_D);
//	  if(i==strlen(data_array))
//	  {
//	  sprintf(buf_D,"%c\r\n",data_array[i]);
//	  SEGGER_RTT_WriteString(0,buf_D);
//	  }
//	}

    
//	index = 0;

  return  replyidx ;

}

bool sendCheckReply(char*send ,char*reply,int16_t timeout,int mqtt_delay)
	
{ 
//sprintf(buf,"send1:%s\r\n",send);
//SEGGER_RTT_WriteString(0,buf);
	if(!getReply(send,timeout,mqtt_delay))
	{
		SEGGER_RTT_WriteString(0,"false\r\n");
	return false;
	
	}
	
	char buf1[20];
	
	
		
//	sprintf(buf1,"replybuffer-%s\r\n",data_array);
//	SEGGER_RTT_WriteString(0,buf1);
		
//  sprintf(buf1,"reply-%s\r\n",reply);
//	SEGGER_RTT_WriteString(0,reply);


//	nrf_delay_ms(15000);

  while(uart_available)
	{  
	if (strcmp(data_array,reply)==0)
	{ //SEGGER_RTT_WriteString(0,"bbb\r\n");  
		SEGGER_RTT_WriteString(0,"true\r\n");
		return true;
	// sprintf(buf1,"srtcmpr-%d\r\n",strcmp(data_array,reply));
		
		
	}
	
	else 
	{	
	 SEGGER_RTT_WriteString(0,"ghalat\r\n");
	return false;
	}
}

}

uint64_t millis(void)
{
    // Store the current value of the timer in the CC[1] register, by triggering the capture task
    MY_TIMER->TASKS_CAPTURE[1] = 1;
    unsigned long captured_value = MY_TIMER->CC[1];
		//char buf[20];
		//sprintf(buf, "captureValue: %lu\n", captured_value);
  	//SEGGER_RTT_WriteString(0, buf);
    //		sprintf(buf, "my_sec: %d\n", my_timer_seconds);
    //  	SEGGER_RTT_WriteString(0, buf);
    //		sprintf(buf, "my_10msec: %d\n", my_timer_10ms);
    //  	SEGGER_RTT_WriteString(0, buf);
	  
		uint64_t my_time_us = ( my_timer_seconds * 1000000 ) + (my_timer_10ms * 10000) + (MY_TIMER->CC[1]);
    // Combine the state of the second variable with the current timer state, and return the result
    // return (uint64_t)my_timer_seconds * 1000000 + MY_TIMER->CC[1];
//    sprintf(buf, "my_time_us: %d\n", my_time_us);
//    SEGGER_RTT_WriteString(0, buf);	  
		return (my_time_us/1000);
}



void my_timer_start(void)
{
// Reset the second variable
    my_timer_seconds = 0;
// Ensure the timer uses 24-bit bitmode or higher
    MY_TIMER->BITMODE = TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos;
    
// Set the prescaler to 4, for a timer interval of 1 us (16M / 2^4)
    MY_TIMER->PRESCALER = 4;
//every tick is 1 us
// Set the CC[0] register to hit after 10 mili second
    MY_TIMER->CC[0] = 10000;
//    char buf[20];
//		sprintf(buf, "timer start: %d\n", my_timer_seconds);
//		SEGGER_RTT_WriteString(0, buf);
    // Make sure the timer clears after reaching CC[0]
    MY_TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Msk;
    
// Trigger the interrupt when reaching CC[0]
    MY_TIMER->INTENSET = TIMER_INTENSET_COMPARE0_Msk;
    
// Set a low IRQ priority and enable interrupts for the timer module
    NVIC_SetPriority(MY_TIMER_IRQn, 1);
    NVIC_EnableIRQ(MY_TIMER_IRQn);
    
// Clear and start the timer
    MY_TIMER->TASKS_CLEAR = 1;
    MY_TIMER->TASKS_START = 1;
}



//// Timer interrupt handler



void MY_TIMER_IRQHandler(void)
{
    if(MY_TIMER->EVENTS_COMPARE[0])
    {   //SEGGER_RTT_WriteString(0,"salam\r\n");
        MY_TIMER->EVENTS_COMPARE[0] = 0;
				my_timer_10ms++;
        // Increment the second variable
				if(my_timer_10ms >= 100){
					  //SEGGER_RTT_WriteString(0,"byeeeee\r\n");
						my_timer_seconds++;
						my_timer_10ms = 0;
				}
			//	nrf_gpio_pin_toggle(6);
				//char buf[20];
				//sprintf(buf, "my_seconds: %d\n", my_timer_seconds);
				//SEGGER_RTT_WriteString(0, buf);
    }
}

void at_com(char * at_com,int delay,int mqtt_delay)
{
	//nrf_delay_ms(delay);
	SEGGER_RTT_WriteString(0,"yes\r\n");
	
	getReply(at_com,(uint16_t) 1,mqtt_delay);
}

bool at_com_check(char * at_com,char*expected_reply,uint8_t retry,int delay,int mqtt_delay)
{
//	nrf_delay_ms(delay);

	while(!(sendCheckReply(at_com,expected_reply,(uint16_t) 1,mqtt_delay)) && retry)
	{
		retry --;
		//sendCheckReply(AtBuff,"\r\nOK\r\n",(uint16_t) 500);
	}
	//getReply(AtBuff,(uint16_t) 500);
}


//uint32_t millis(void)
//{
//    // Store the current value of the timer in the CC[1] register, by triggering the capture task
//    MY_TIMER->TASKS_CAPTURE[1] = 1;
//    
//    // Combine the state of the second variable with the current timer state, and return the result
//    return (my_timer_seconds * 1000) + (MY_TIMER->CC[1] / 1000);
//}

//void MY_TIMER_IRQHandler(void)
//{
//    if(MY_TIMER->EVENTS_COMPARE[0])
//    {
//        MY_TIMER->EVENTS_COMPARE[0] = 0;

//        // Increment the second variable
//        my_timer_seconds++;
//    }
//}

