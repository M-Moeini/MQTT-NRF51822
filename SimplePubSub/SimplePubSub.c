/*

Simple publish and subscribe library
developed by Mahdi Moeini
mahdimoeini719@gmail.com
*/

#include "SimplePubSub.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "SEGGER_RTT.h"
#include "mqtt.h"
#include "nrf_gpio.h"


//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include "nordic_common.h"
//#include "app_error.h"
//#include "ble_db_discovery.h"
//#include "app_timer.h"
//#include "app_util.h"
//#include "bsp.h"
//#include "bsp_btn_ble.h"
//#include "boards.h"
//#include "ble.h"
//#include "ble_gap.h"
//#include "ble_hci.h"
//#include "softdevice_handler.h"
//#include "ble_advdata.h"
//#include "ble_nus_c.h"
//#include "SEGGER_RTT.h"

uint16_t socketTimeout=MQTT_SOCKET_TIMEOUT;
//remember//
char buf2[50];
uint8_t buffer[100];
uint16_t bufferSize;
uint16_t keepAlive= MQTT_KEEPALIVE;
uint16_t nextMsgId;
unsigned long lastOutActivity;
unsigned long lastInActivity;
bool pingOutstanding;
bool connect_ack_f=0;
bool sub_f=0;
bool flag=0;
const char* domain;
int _state;
uint16_t port;
uint8_t* return_buf;
static uint8_t data_a[30];
char buf_D1[20];
static uint8_t indx = 0;
extern bool clinet_connect_f;
extern bool client_available_f;
extern bool connect_ack_f;
extern bool ciprxgt404_f;
extern bool ciprxgt405_f;
extern bool ciprxgt402_f;
extern bool on_buf_f;
extern bool	buf_4023_f;
extern bool	buf_4024_f;
extern char on_buf_array[70];
extern uint8_t data_array[70];
extern uint8_t connecAck_data_array[70];
extern uint8_t ans_buf[70];
char  connect_buf[4]={32,2,0,0};
char *on_buffer="on";
char* off_buffer="off";
int t1=0;
int t2=0;


MQTT_CALLBACK_SIGNATURE;











    /* Configure SysTick to generate an interrupt every millisecond */
  
 
//uint8_t setCallback(MQTT_CALLBACK_SIGNATURE) {
//    
//    return callback;
//}


//PubSubClient() {
//    _state = MQTT_DISCONNECTED;
//    this->_client = NULL;
//    this->stream = NULL;
//    setCallback(NULL);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//
//PubSubClient(Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//
//PubSubClient(IPAddress addr, uint16_t port, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(addr, port);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(IPAddress addr, uint16_t port, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(addr,port);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(addr, port);
//    setCallback(callback);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(addr,port);
//    setCallback(callback);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//
//PubSubClient(uint8_t *ip, uint16_t port, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(ip, port);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(uint8_t *ip, uint16_t port, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(ip,port);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(ip, port);
//    setCallback(callback);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(ip,port);
//    setCallback(callback);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//
//PubSubClient(const char* domain, uint16_t port, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(domain,port);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(const char* domain, uint16_t port, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(domain,port);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
//    _state = MQTT_DISCONNECTED;
//    setServer(domain,port);
//    setCallback(callback);
//    setClient(client);
//    this->stream = NULL;
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//PubSubClient(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
//    _state = MQTT_DISCONNECTED;
//    setServer(domain,port);
//    setCallback(callback);
//    setClient(client);
//    setStream(stream);
//    bufferSize = 0;
//    setBufferSize(MQTT_MAX_PACKET_SIZE);
//    setKeepAlive(MQTT_KEEPALIVE);
//    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
//}
//
//~PubSubClient() {
//  free(buffer);
//}

bool connect(const char *id) {

    return connect5(id,NULL,NULL,0,0,0,0,1);
	
}

bool connect2(const char *id, const char *user, const char *pass) {

	 return connect5(id,user,pass,0,0,0,0,1);
	
}

bool connect3(const char *id, const char* willTopic, uint8_t willQos, bool willRetain, const char* willMessage) {
	
   return connect5(id,NULL,NULL,willTopic,willQos,willRetain,willMessage,1);
	
}

bool connect4(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, bool willRetain, const char* willMessage) {

	return connect5(id,user,pass,willTopic,willQos,willRetain,willMessage,1);

}

bool connect5(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, bool willRetain, const char* willMessage, bool cleanSession) {
    if (!connected()) {
			SEGGER_RTT_WriteString(0,"residam\r\n");  
        int result = 0;

		// TODO: check TCP connection here
        //if(_client->connected()) {
        //    result = 1;
        //} else {
        //    if (domain != NULL) {
        //        result = _client->connect(this->domain, this->port);
        //    } else {
        //        result = _client->connect(this->ip, this->port);
        //    }
        //}
		result = 1;
        if (result == 1) {
            nextMsgId = 1;
            // Leave room in the buffer for header and variable length field
            uint16_t length = MQTT_MAX_HEADER_SIZE;
            unsigned int j;
            
#if MQTT_VERSION == MQTT_VERSION_3_1
            uint8_t d[9] = {0x00,0x06,'M','Q','I','s','d','p', MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 9
#elif MQTT_VERSION == MQTT_VERSION_3_1_1
            uint8_t d[7] = {0x00,0x04,'M','Q','T','T',MQTT_VERSION};
            
#define MQTT_HEADER_VERSION_LENGTH 7
#endif
            for (j = 0;j<MQTT_HEADER_VERSION_LENGTH;j++) {
							  SEGGER_RTT_WriteString(0,"residam2\r\n");
                   buffer[length++] = d[j];
							    //d[j]=j;
							  
            }
						//SEGGER_RTT_WriteString(0,"residam2\r\n");
            
            uint8_t v;
            if (willTopic) {
                v = 0x04|(willQos<<3)|(willRetain<<5);
            } else {
                v = 0x00;
            }
            if (cleanSession) {
                v = v|0x02;
            }

            if(user != NULL) {
                v = v|0x80;

                if(pass != NULL) {
                    v = v|(0x80>>1);
                }
            }
						
            buffer[length++] = v;

            buffer[length++] = ((keepAlive) >> 8);
            buffer[length++] = ((keepAlive) & 0xFF);

//            CHECK_STRING_LENGTH(length,id)
            length = writeString(id,buffer,length);
            if (willTopic) {
//                CHECK_STRING_LENGTH(length,willTopic)
                length = writeString(willTopic,buffer,length);
//                CHECK_STRING_LENGTH(length,willMessage)
                length = writeString(willMessage,buffer,length);
            }

            if(user != NULL) {
//                CHECK_STRING_LENGTH(length,user)
                length = writeString(user,buffer,length);
                if(pass != NULL) {
//                    CHECK_STRING_LENGTH(length,pass)
                    length = writeString(pass,buffer,length);
                }
            }
            at_com("AT+CIPSEND=0,33\r\n",5000,1000);
						at_com("",1000,1000);
            write(MQTTCONNECT,buffer,length-MQTT_MAX_HEADER_SIZE);
						
						for(int i=0;i<(length-MQTT_MAX_HEADER_SIZE);i++)
						{  char buf[20];
							sprintf(buf,"i=%d\r\n",buffer[i]);
							SEGGER_RTT_WriteString(0,buf);
						}	
			//TODO time in mili sec
//            lastInActivity = lastOutActivity = millis();
			
            //while (!client_available_f) {
            //    unsigned long t = millis();
            //    if (t-lastInActivity >= ((int32_t) this->socketTimeout*1000UL)) {
            //        _state = MQTT_CONNECTION_TIMEOUT;
            //        _client->stop();
            //        return false;
            //    }
            //}
						//nrf_delay_ms(5000);


						while(!client_available_f)
						{
							int z=0;
							z++;
							SEGGER_RTT_WriteString(0,"");
						}
						sprintf(buf2,"client_f=%d\r\n",client_available_f);
						SEGGER_RTT_WriteString(0,buf2);
            uint8_t llen;
            // uint32_t len = readPacket(&llen);
					  //	SEGGER_RTT_WriteString(0,"hasan1");
						//if(client_available_f)
						//{  SEGGER_RTT_WriteString(0,"salam salam \r\n");
							//client_available_f=0;
							readserver();
						//}	

          
							  
            if (connecAck_data_array[3] == 0)
						{
					  SEGGER_RTT_WriteString(0,"MQTT CONNECTED\r\n");
                lastInActivity = millis();
                pingOutstanding = false;
                _state = MQTT_CONNECTED;
                return true;
            } 
			else 
						{
              _state = buffer[3];
            }
            
			// TODO
          //  _client->stop();
        } else {
            _state = MQTT_CONNECT_FAILED;
        }
        return false;
    }
    return true;
}


bool publish(const char* topic, const char* payload,uint16_t plength) {
	return publish4(topic,payload, plength,false);
}

//bool publish2(const char* topic, const char* payload, bool  retained) {
//	return publish4(topic,(const uint8_t*)payload, payload ? strnlen(payload, bufferSize) : 0,retained);
//}

//bool publish3(const char* topic, const uint8_t* payload, unsigned int plength) {
//    return publish4(topic, payload, plength, false);
//}

bool publish4(const char* topic, const uint8_t* payload, unsigned int plength, bool retained) {
    if (connect_ack_f)
			{
//        if (bufferSize < MQTT_MAX_HEADER_SIZE + 2+strnlen(topic, this->bufferSize) + plength) {
//            // Too long
//            return false;
//        }
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,buffer,length);

        // Add payload
        uint16_t i;
        for (i=0;i<plength;i++) {
            buffer[length++] = payload[i];
        }

        // Write the header
        uint8_t header = MQTTPUBLISH;
				
//        if (retained) {
//            header |= 1;
//        } 
				at_com("AT+CIPSEND=0,37\r\n",1000,100);
				at_com("",1000,10);
        return write(header,buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}


bool subscribe(const char* topic) {
    return subscribe2(topic, 0);
}

bool subscribe2(const char* topic, uint8_t qos) {
	   SEGGER_RTT_WriteString(0,"sub1\r\n");
    size_t topicLength = strlen(topic);
    if (topic == 0) {
        return false;
			  SEGGER_RTT_WriteString(0,"sub2\r\n");
    }
    if (qos > 1) {
			SEGGER_RTT_WriteString(0,"sub3\r\n");
        return false;
    }
//    if (bufferSize < 9 + topicLength) {
//			  SEGGER_RTT_WriteString(0,"sub4\r\n");
//        // Too long
//        return false;
//    } 
		 SEGGER_RTT_WriteString(0,"sub5\r\n");
    if (connect_ack_f) {
			  SEGGER_RTT_WriteString(0,"sub6\r\n");
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) {
            nextMsgId = 1;
        }
        buffer[length++] = (nextMsgId >> 8);
        buffer[length++] = (nextMsgId & 0xFF);
        length = writeString((char*)topic, buffer,length);
        buffer[length++] = qos;
				SEGGER_RTT_WriteString(0,"sub\r\n");
				at_com("AT+CIPSEND=0,24\r\n",1000,100);
				at_com("",1000,100);
        write(MQTTSUBSCRIBE|MQTTQOS1,buffer,length-MQTT_MAX_HEADER_SIZE);
				while(!clinet_connect_f)
				{ int z=0;
					z++;
					SEGGER_RTT_WriteString(0,"");
				}
				//nrf_delay_ms(4000);
				readserver();
				//sub_f=1;
//				if(client_available_f)
//				{ SEGGER_RTT_WriteString(0,"Bbbbbbbbbbbbbbbbb/r/n");
//					client_available_f=0;
//					readPacket2();
//				}
				


				return true;
    }
    return false;
}






//// reads a byte into result

uint32_t readserver3(void)
{
	at_com("AT+CIPRXGET=4,0\r\n",100,1000);
	at_com("AT+CIPRXGET=2,0,2\r\n",100,1000);
	nrf_delay_ms(1000);
	
}	


uint32_t readserver2(void)
{ SEGGER_RTT_WriteString(0,"readserver2\r\n");
	int i[3]={0,0,0};
	int c=0;
	int index=strlen(data_array);
	
 while(client_available_f)
 {   
	   client_available_f=0;
	   buf_4023_f=0;
	   buf_4024_f=0;
   	 at_com("AT+CIPRXGET=4,0\r\n",100,75);
	   //nrf_delay_ms(100);
	   
//	   for(int i=0;i<strlen(data_array);i++)
//	   {
//			 sprintf(buffer,"k=%d\r\n",data_array[i]);
//			 SEGGER_RTT_WriteString(0,buffer);
//		 }
		 //nrf_delay_ms(1000);
     for(c=0;c<10;c++)
     {
//			     sprintf(buffer,"ic=%d\r\n",data_array[index-c]);
//					 SEGGER_RTT_WriteString(0,buffer);
//       if(sub_f)
//       {	sub_f=0;			 
//			   if(data_array[index-c]!=44)
//			   {  SEGGER_RTT_WriteString(0,"ddd\r\n");
//				   i[c]=data_array[index-c]-48;
//				   sprintf(buffer,"i[%d]=%d",c,i[c]);
//		       SEGGER_RTT_WriteString(0,buffer);
//			   }
//		   }
			
			 sprintf(buffer,"x=%d\r\n",data_array[index-c]);
			 SEGGER_RTT_WriteString(0,buffer);
			 
			 
			 if(data_array[index-c]!=44)
			 {  SEGGER_RTT_WriteString(0,"ddd\r\n");
				 i[c]=data_array[index-c]-48;
				 sprintf(buffer,"i[%d]=%d",c,i[c]);
		     SEGGER_RTT_WriteString(0,buffer);
			 }
			 else break;
		 }	
		 
	
	
 }
    int k=(i[0]*1)+(i[1]*10)+(i[2]*100);
 
 		sprintf(buffer,"k=%d\r\n",k);
		SEGGER_RTT_WriteString(0,buffer);
    char buf10[50]="AT+CIPRXGET=2,0,";
    char buf11[50]; 
    char buf12[10];
    char buf13[70]; 
    sprintf(buf12,"%d",k);	
//char buf13[20]=	
	  for(c=0;c<strlen(buf10);c++)
	  {
	  	buf11[c]=buf10[c];
	  }
	  
	  buf11[c]=buf12[0];
		buf11[c+1]=buf12[1];		
	  buf11[c+2]='\r\n';
 
	  //SEGGER_RTT_WriteString(0,"xxxxxxxxxxxxxxxxx\r\n");
		//nrf_delay_ms(2000);
	  at_com(buf11,1000,75);
//    nrf_delay_ms(5000);
//    int b=strlen(data_array);	
//    int d=0;
//for(int i=0;i<18;i++)
//{
//	sprintf(buffer,"c=%c",buf11[0]);
//	SEGGER_RTT_WriteString(0,buffer);
//}	

//	for(int c=0;c<b;c++)
//	{
//		buf13[c]=data_array[b-c];
//		//d++;
//	}	
  for(int i=0;i<sizeof(connecAck_data_array);i++)
  {
		sprintf(buffer,"buf13=%d\r\n",connecAck_data_array[i]);
		SEGGER_RTT_WriteString(0,buffer);
	}		
 if(strncmp(connecAck_data_array,connect_buf,2)==0)
 {
	 connect_ack_f=1;
	 SEGGER_RTT_WriteString(0,"connect_ack_f=1\r\n");
 }
   int z=0;
// int d=21;	

 for(int i=21;connecAck_data_array[i]!=13;i++)	
	
// while(connecAck_data_array[d]!=NULL) 
 {
// SEGGER_RTT_WriteString(0,"hasan\r\n");
  ans_buf[z]=connecAck_data_array[i];	
	sprintf(buf2,"ans_buf=%d\r\n",connecAck_data_array[i]);
	//SEGGER_RTT_WriteString(0,buf2);	 
 //d++;	 
 z++;
 }
  ans_buf[z]=0;
  z=0;
//  sprintf(buffer,"siz of ans =%d\r\n",strlen(ans_buf));
// 	SEGGER_RTT_WriteString(0,buffer);
  for(int i=0;i<strlen(ans_buf);i++)
 {
	 //SEGGER_RTT_WriteString(0,"ahmad\r\n");
	sprintf(buf2,"ans1_buf=%c\r\n",ans_buf[i]);
	SEGGER_RTT_WriteString(0,buf2);
	//ans_buf[i]=0;
 }

 if(strcmp(on_buffer,ans_buf)==0)
 {
	 SEGGER_RTT_WriteString(0,"the led is on\r\n");
	 nrf_gpio_pin_set(23);
 }	
 if(strcmp(off_buffer,ans_buf)==0)
 {
	 SEGGER_RTT_WriteString(0,"the led is off\r\n");
	 nrf_gpio_pin_clear(23);
 }	  
 
 
 
}


uint32_t readserver(void)
{    if(on_buf_f)
    {
	    for(int i=0;i<strlen(on_buf_array);i++)
             {
				//on_buf_array[i]=data_array[i];
				sprintf(buffer,"h=%d\r\n",on_buf_array[i]);
				SEGGER_RTT_WriteString(0,buffer);
			}	
    }
	  SEGGER_RTT_WriteString(0,"hi baby\r\n"); 
    int i[3]={0,0,0};
	  int c=0;
	  int index=strlen(data_array);
 while(client_available_f)
 {   client_available_f=0;
   	 at_com("AT+CIPRXGET=4,0\r\n",100,50);
	   //nrf_delay_ms(100);
	   
	   for(int i=0;i<strlen(data_array);i++)
	   {
			 sprintf(buffer,"kkk=%d\r\n",data_array[i]);
			 SEGGER_RTT_WriteString(0,buffer);
		 }
//		 if(buf_4023_f)
//		 {  //buf_4023_f=0;
//			 SEGGER_RTT_WriteString(0,"buf4023\r\n");
//			 readserver2();
//		 }
//			else if (buf_4024_f)
//			{ //buf_4024_f=0;
//				SEGGER_RTT_WriteString(0,"buf4024\r\n");
//				readserver2();
//			}
//			else
//			{
		 //nrf_delay_ms(4000);
		    index--;
		    if(flag)
				{
					//flag=0;
					index++;
				}
        for(c=0;c<10;c++)
        {
//	    	     sprintf(buffer,"ic=%d\r\n",data_array[index-c]);
//	    			 SEGGER_RTT_WriteString(0,buffer);
//          if(sub_f)
//          {	sub_f=0;			 
//	    	   if(data_array[index-c]!=44)
//	    	   {  SEGGER_RTT_WriteString(0,"ddd\r\n");
//	    		   i[c]=data_array[index-c]-48;
//	    		   sprintf(buffer,"i[%d]=%d",c,i[c]);
//	           SEGGER_RTT_WriteString(0,buffer);
//	    	   }
//	       }
		     
		     sprintf(buffer,"x=%d\r\n",data_array[index-c]);
		     SEGGER_RTT_WriteString(0,buffer);
		     if(data_array[index-c]!=44)
		     {  SEGGER_RTT_WriteString(0,"ddd\r\n");
		    	 i[c]=data_array[index-c]-48;
		    	
		    	 sprintf(buffer,"i[%d]=%d",c,i[c]);
		        SEGGER_RTT_WriteString(0,buffer);
		     }
		     else break;
		    }			 
        
      
// at_com("AT\r\n",1000,1000);
 int k=(i[0]*1)+(i[1]*10)+(i[2]*100);
 
 		sprintf(buffer,"k=%d\r\n",k);
		SEGGER_RTT_WriteString(0,buffer);
 
    char buf10[50]="AT+CIPRXGET=2,0,";
    char buf11[50]; 
    char buf12[10];
    char buf13[70]; 
    sprintf(buf12,"%d",k);	
//char buf13[20]=	
	  for(c=0;c<strlen(buf10);c++)
	  {
	  	buf11[c]=buf10[c];
	  }
	  //buf11[c]=44;
	  buf11[c]=buf12[0];
	  buf11[c+1]='\r\n';
		if(flag)
		{
		buf11[c]=buf12[0];
		buf11[c+1]=buf12[1];		
	  buf11[c+2]='\r\n';
		}
 
	  //SEGGER_RTT_WriteString(0,"xxxxxxxxxxxxxxxxx\r\n");
		//nrf_delay_ms(2000);
	  at_com(buf11,1000,50);
//    nrf_delay_ms(5000);
//    int b=strlen(data_array);	
//    int d=0;
//for(int i=0;i<18;i++)
//{
//	sprintf(buffer,"c=%c",buf11[0]);
//	SEGGER_RTT_WriteString(0,buffer);
//}	

//	for(int c=0;c<b;c++)
//	{
//		buf13[c]=data_array[b-c];
//		//d++;
//	}	

 if(flag)
 {
	flag=0;
  for(int i=0;i<sizeof(connecAck_data_array);i++)
  {
		sprintf(buffer,"buf13=%d\r\n",connecAck_data_array[i]);
		SEGGER_RTT_WriteString(0,buffer);
	}		
 if(strncmp(connecAck_data_array,connect_buf,2)==0)
 {
	 connect_ack_f=1;
	 SEGGER_RTT_WriteString(0,"connect_ack_f=1\r\n");
 }
   int z=0;
// int d=21;	

 for(int i=21;connecAck_data_array[i]!=13;i++)	
	
// while(connecAck_data_array[d]!=NULL) 
 {
// SEGGER_RTT_WriteString(0,"hasan\r\n");
  ans_buf[z]=connecAck_data_array[i];	
	sprintf(buf2,"ans_buf=%d\r\n",connecAck_data_array[i]);
	//SEGGER_RTT_WriteString(0,buf2);	 
 //d++;	 
 z++;
 }
  ans_buf[z]=0;
  z=0;
//  sprintf(buffer,"siz of ans =%d\r\n",strlen(ans_buf));
// 	SEGGER_RTT_WriteString(0,buffer);
  for(int i=0;i<strlen(ans_buf);i++)
 {
	 //SEGGER_RTT_WriteString(0,"ahmad\r\n");
	sprintf(buf2,"ans1_buf=%c\r\n",ans_buf[i]);
	SEGGER_RTT_WriteString(0,buf2);
	//ans_buf[i]=0;
 }
 
 if(strcmp(on_buffer,ans_buf)==0)
 {
	 SEGGER_RTT_WriteString(0,"the led is on\r\n");
	 nrf_gpio_pin_set(23);
 }	
 if(strcmp(off_buffer,ans_buf)==0)
 {
	 SEGGER_RTT_WriteString(0,"the led is off\r\n");
	 nrf_gpio_pin_clear(23);
 }	  
 }



		
//		
//  for(int i=0;i<sizeof(connecAck_data_array);i++)
//  {
//		sprintf(buffer,"buf13=%d\r\n",connecAck_data_array[i]);
//		SEGGER_RTT_WriteString(0,buffer);
//	}		
// if(strncmp(connecAck_data_array,connect_buf,2)==0)
// {
//	 connect_ack_f=1;
//	 SEGGER_RTT_WriteString(0,"connect_ack_f=1\r\n");
// }

//  }
  }

 }

uint32_t readPacket2(void)
{     
	
		 //client_available_f=0;
		 SEGGER_RTT_WriteString(0,"alollllllllllllllllllllllllllll\r\n");
	   at_com("AT+CIPRXGET=4,0\r\n",100,100);
	   nrf_delay_ms(100);
	   if(ciprxgt404_f)
		 {
			ciprxgt404_f=0;
			SEGGER_RTT_WriteString(0,"salam mehdi\r\n"); 
			at_com("AT+CIPRXGET=2,0,4\r\n",1000,100);
	  	nrf_delay_ms(100); 
		 }
		else if(ciprxgt405_f)
		 {
			ciprxgt405_f=0;
			SEGGER_RTT_WriteString(0,"salam mehdi jan\r\n"); 
			at_com("AT+CIPRXGET=2,0,5\r\n",100,100);
			nrf_delay_ms(100); 
		 }
		 		else if(ciprxgt402_f)
		 {
			ciprxgt402_f=0;
			SEGGER_RTT_WriteString(0,"salam mehdi jan\r\n"); 
			at_com("AT+CIPRXGET=2,0,2\r\n",100,100);
			nrf_delay_ms(100); 
		 }
     		 
//	   SEGGER_RTT_WriteString(0,"hasan");
	   nrf_delay_ms(100);
     


	
//		 for(int i=0;i<strlen(data_array);i++)
//	 {
//			sprintf(buf_D1,"res=%d",data_array[i]);
//			SEGGER_RTT_WriteString(0,buf_D1);
//			if(i==strlen(data_array))
//			{
//				sprintf(buf_D1,"res=%d\r\n",data_array[i]);
//				SEGGER_RTT_WriteString(0,buf_D1);
//			}
//	 }
//	 return strlen(data_array);
	
}


bool readByte(uint8_t  *result) {
	 SEGGER_RTT_WriteString(0,"client_flag1\r\n");	
   uint32_t previousMillis = millis();
	 SEGGER_RTT_WriteString(0,"client_flag2\r\n");
   while(!client_available_f) {
		 
		 //SEGGER_RTT_WriteString(0,"client_flag_not\r\n");
     //yield();
     uint32_t currentMillis = millis();
     if(currentMillis - previousMillis >= ((int32_t) socketTimeout * 1000)){
       return false;
     }
   }
/*remember	 
   *result = _client->read();
*/	 
	  client_available_f=0;
		SEGGER_RTT_WriteString(0,"client_flag_set\r\n");
	  at_com("AT+CIPRXGET=4,0\r\n",100,10);
	  at_com("AT+CIPRXGET=2,0,2\r\n",100,10);
	 
	  
//   	app_uart_get(&data_a[indx]);
//    *result = data_a[indx];
   return true;
}

// reads a byte into result[*index] and increments index
bool  readByte2(uint8_t * result, uint16_t * index){
  uint16_t current_index = *index;
  uint8_t * write_address = &(result[current_index]);
  if(readByte(write_address)){
    *index = current_index + 1;
    return true;
  }
  return false;
}

uint32_t readPacket(uint8_t* lengthLength) {
    uint16_t len = 0;
	
    if(!readByte2(buffer, &len)) return 0;
	
    bool isPublish = (buffer[0]&0xF0) == MQTTPUBLISH;
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint16_t skip = 0;
    uint32_t start = 0;

    do {
        if (len == 5) {
            // Invalid remaining length encoding - kill the connection
            _state = MQTT_DISCONNECTED;
			// TODO kill the connection
            //_client->stop();
            return 0;
        }
        if(!readByte(&digit)) return 0;
        buffer[len++] = digit;
        length += (digit & 127) * multiplier;
        multiplier <<=7; //multiplier *= 128
    } while ((digit & 128) != 0);
    *lengthLength = len-1;

    if (isPublish) {
        // Read in topic length to calculate bytes to skip over for Stream writing
/*remember			
        if(!readByte(buffer, &len)) return 0;
        if(!readByte(buffer, &len)) return 0;
*/			
        skip = (buffer[*lengthLength+1]<<8)+buffer[*lengthLength+2];
        start = 2;
        if (buffer[0]&MQTTQOS1) {
            // skip message id
            skip += 2;
        }
    }
    uint32_t idx = len;

    for (uint32_t i = start;i<length;i++) {
        if(!readByte(&digit)) return 0;
		// TODO below code seems to be important
        //if (this->stream) {
        //    if (isPublish && idx-*lengthLength-2>skip) {
        //        this->stream->write(digit);
        //    }
        //}

        if (len < bufferSize) {
            buffer[len] = digit;
            len++;
        }
        idx++;
    }
	//TODO
    //if (!this->stream && idx > bufferSize) {
    //    len = 0; // This will cause the packet to be ignored.
    //}
    return len;
}
void ping_handle(void)
{
	  buffer[0] = MQTTPINGREQ;
    buffer[1] = 0;
	at_com("AT+CIPSEND=0,2\r\n",1000,100);
  for(int i=0;i<2;i++)
 { sprintf(buf2,"d1=%d\r\n",buffer[i]);
	SEGGER_RTT_WriteString(0,buf2);
	while (app_uart_put( (uint8_t) buffer[i]) != NRF_SUCCESS);
	//nrf_delay_ms(10);
 }
    // t1=millis();
// nrf_delay_ms(4000);
  while(!client_available_f)
	{
		int z=0;
		z++;
		SEGGER_RTT_WriteString(0,"");
		// t2=millis();
	}
	SEGGER_RTT_WriteString(0,"residam1\r\n");
	readserver();
	SEGGER_RTT_WriteString(0,"residam2\r\n");
 
}	


bool loop() {
	    //SEGGER_RTT_WriteString(0,"loop\r\n");
//	  	if(client_available_f)
//			{ //SEGGER_RTT_WriteString(0,"caf\r\n");
//				readserver2();
//			}
    if (connect_ack_f) {
			 // SEGGER_RTT_WriteString(0,"xxx\r\n");

			unsigned long t = millis();
        if ((t - lastInActivity > keepAlive*1000UL) || (t - lastOutActivity > keepAlive*1000UL)) {
			 // SEGGER_RTT_WriteString(0,"yyy\r\n");
        
//					if (pingOutstanding) {
//						    SEGGER_RTT_WriteString(0,"zzz\r\n");
//                _state = MQTT_CONNECTION_TIMEOUT;
///*remember							
//                _client->stop();
//*/							
//                return false;
//            } 
//					    else {
//                buffer[0] = MQTTPINGREQ;
//                buffer[1] = 0;
///*remember							
//                _client->write(buffer,2);
//*/		
//				        at_com("AT+CIPSEND=0,2\r\n",1000,2000);
//				        at_com("",1000,100);							
//							  for(int i=0;i<2;i++)
//							  { sprintf(buf2,"d=%d\r\n",buffer[i]);
//									SEGGER_RTT_WriteString(0,buf2);
//									while (app_uart_put( (uint8_t) buffer[i]) != NRF_SUCCESS);
//									nrf_delay_ms(10);
//								}
//								SEGGER_RTT_WriteString(0,"residi_inja\r\n");
//								nrf_delay_ms(3000);
//								readPacket2();
							  ping_handle();
                lastOutActivity = t;
                lastInActivity = t;
                pingOutstanding = true;
//            }
        }
				
				
				
			if(client_available_f)
			{ //SEGGER_RTT_WriteString(0,"caf\r\n");
				flag=1;
				readserver();
				
			}
//        if (client_available_f) {
//            uint8_t llen;
//            uint16_t len = readPacket(&llen);
//            uint16_t msgId = 0;
//            uint8_t *payload;
//            if (len > 0) {
//                lastInActivity = t;
//                uint8_t type = buffer[0]&0xF0;
//                if (type == MQTTPUBLISH) {
//                    if (callback) {
//                        uint16_t tl = (buffer[llen+1]<<8)+buffer[llen+2]; /* topic length in bytes */
//                        memmove(buffer+llen+2,buffer+llen+3,tl); /* move topic inside buffer 1 byte to front */
//                        buffer[llen+2+tl] = 0; /* end the topic as a 'C' string with \x00 */
//                        char *topic = (char*) buffer+llen+2;
//                        // msgId only present for QOS>0
//                        if ((buffer[0]&0x06) == MQTTQOS1) {
//                            msgId = (buffer[llen+3+tl]<<8)+buffer[llen+3+tl+1];
//                            payload = buffer+llen+3+tl+2;
//                            callback(topic,payload,len-llen-3-tl-2);

//                            buffer[0] = MQTTPUBACK;
//                            buffer[1] = 2;
//                            buffer[2] = (msgId >> 8);
//                            buffer[3] = (msgId & 0xFF);
///*remember													
//                            _client->write(buffer,4);
//*/													
//                            lastOutActivity = t;

//                        } else {
//                            payload = buffer+llen+3+tl;
//                            callback(topic,payload,len-llen-3-tl);
//                        }
//                    }
//                } else if (type == MQTTPINGREQ) {
//                    buffer[0] = MQTTPINGRESP;
//                    buffer[1] = 0;
///*remember									
//                    _client->write(buffer,2);
//*/									
//                } else if (type == MQTTPINGRESP) {
//                    pingOutstanding = false;
//                }
//            } else if (!connected()) {
//                // readPacket has closed the connection
//                return false;
//            }
//        }
        return true;
    }
    return false;
}

//bool publish(const char* topic, const char* payload) {
//    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, bufferSize) : 0,false);
//}
//
//bool publish(const char* topic, const char* payload, bool retained) {
//    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, bufferSize) : 0,retained);
//}
//
//bool publish(const char* topic, const uint8_t* payload, unsigned int plength) {
//    return publish(topic, payload, plength, false);
//}
//
//bool publish(const char* topic, const uint8_t* payload, unsigned int plength, bool retained) {
//    if (connected()) {
//        if (bufferSize < MQTT_MAX_HEADER_SIZE + 2+strnlen(topic, bufferSize) + plength) {
//            // Too long
//            return false;
//        }
//        // Leave room in the buffer for header and variable length field
//        uint16_t length = MQTT_MAX_HEADER_SIZE;
//        length = writeString(topic,buffer,length);
//
//        // Add payload
//        uint16_t i;
//        for (i=0;i<plength;i++) {
//            buffer[length++] = payload[i];
//        }
//
//        // Write the header
//        uint8_t header = MQTTPUBLISH;
//        if (retained) {
//            header |= 1;
//        }
//        return write(header,buffer,length-MQTT_MAX_HEADER_SIZE);
//    }
//    return false;
//}
//
//bool publish_P(const char* topic, const char* payload, bool retained) {
//    return publish_P(topic, (const uint8_t*)payload, payload ? strnlen(payload, bufferSize) : 0, retained);
//}
//
//bool publish_P(const char* topic, const uint8_t* payload, unsigned int plength, bool retained) {
//    uint8_t llen = 0;
//    uint8_t digit;
//    unsigned int rc = 0;
//    uint16_t tlen;
//    unsigned int pos = 0;
//    unsigned int i;
//    uint8_t header;
//    unsigned int len;
//    int expectedLength;
//
//    if (!connected()) {
//        return false;
//    }
//
//    tlen = strnlen(topic, bufferSize);
//
//    header = MQTTPUBLISH;
//    if (retained) {
//        header |= 1;
//    }
//    buffer[pos++] = header;
//    len = plength + 2 + tlen;
//    do {
//        digit = len  & 127; //digit = len %128
//        len >>= 7; //len = len / 128
//        if (len > 0) {
//            digit |= 0x80;
//        }
//        buffer[pos++] = digit;
//        llen++;
//    } while(len>0);
//
//    pos = writeString(topic,buffer,pos);
//
//    rc += _client->write(buffer,pos);
//
//    for (i=0;i<plength;i++) {
//        rc += _client->write((char)pgm_read_byte_near(payload + i));
//    }
//
//    lastOutActivity = millis();
//
//    expectedLength = 1 + llen + 2 + tlen + plength;
//
//    return (rc == expectedLength);
//}
//
//bool beginPublish(const char* topic, unsigned int plength, bool retained) {
//    if (connected()) {
//        // Send the header and variable length field
//        uint16_t length = MQTT_MAX_HEADER_SIZE;
//        length = writeString(topic,buffer,length);
//        uint8_t header = MQTTPUBLISH;
//        if (retained) {
//            header |= 1;
//        }
//        size_t hlen = buildHeader(header, buffer, plength+length-MQTT_MAX_HEADER_SIZE);
//        uint16_t rc = _client->write(buffer+(MQTT_MAX_HEADER_SIZE-hlen),length-(MQTT_MAX_HEADER_SIZE-hlen));
//        lastOutActivity = millis();
//        return (rc == (length-(MQTT_MAX_HEADER_SIZE-hlen)));
//    }
//    return false;
//}
//
//int endPublish() {
// return 1;
//}
//
size_t write2(uint8_t data) {
	//TODO timer in mili sec
    lastOutActivity = millis();
	//TODO uart_put
/*remember	
    return _client->write(data);
/*	
}

size_t write3(const uint8_t *buffer, size_t size) {
    lastOutActivity = millis();
/*remember	
    return _client->write(buffer,size);
*/	
}

size_t buildHeader(uint8_t header, uint8_t* buf, uint16_t length) {
    uint8_t lenBuf[4];
    uint8_t llen = 0;
    uint8_t digit;
    uint8_t pos = 0;
    uint16_t len = length;
    do {

        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        lenBuf[pos++] = digit;
        llen++;
    } while(len>0);

    buf[4-llen] = header;
    for (int i=0;i<llen;i++) {
        buf[MQTT_MAX_HEADER_SIZE-llen+i] = lenBuf[i];
    }
    return llen+1; // Full header size is variable length bit plus the 1-byte fixed header
}

bool write(uint8_t header, uint8_t* buf, uint16_t length) {
    uint16_t rc;
    uint8_t hlen = buildHeader(header, buf, length);

    
#ifdef MQTT_MAX_TRANSFER_SIZE
    uint8_t* writeBuf = buf+(MQTT_MAX_HEADER_SIZE-hlen);
    uint16_t bytesRemaining = length+hlen;  //Match the length type
    uint8_t bytesToWrite;
    bool result = true;
    while((bytesRemaining > 0) && result) {
        bytesToWrite = (bytesRemaining > MQTT_MAX_TRANSFER_SIZE)?MQTT_MAX_TRANSFER_SIZE:bytesRemaining;
//      rc = _client->write(writeBuf,bytesToWrite);
	      for (int i = 0; i <= bytesToWrite; i++)
	      {   	
	      	   while (app_uart_put((uint8_t) writeBuf[i]) != NRF_SUCCESS);
	      	   nrf_delay_ms(10);
	      	
	      }			
        result = (rc == bytesToWrite);
        bytesRemaining -= rc;
        writeBuf += rc;
    }
    return result;
#else

//  		char	AttBuff[36]={208,0,0,16,31,0,4,77,81,84,84,4,2,0,15,0,19,99,108,111,117,100,46,115,109,97,114,116,104,111,111,109,46,99,111,109};	
//	          for (int i = 0; i <36; i++)
//	          { 
//							
//								sprintf(buf,"send_koli=%d\r\n", AttBuff[i]);
//								SEGGER_RTT_WriteString(0,buf);							
//								while (app_uart_put((uint8_t) AttBuff[i]) != NRF_SUCCESS);
////						   SEGGER_RTT_WriteString(0,"f\r\n");
//								nrf_delay_ms(10);
//		
////			        sprintf(buf,"send[i]=%c\r\n",send[i]);
////	            SEGGER_RTT_WriteString(0,buf);
//	          }


//		      char*send2="ATI\r\n";
//			    for (int i = 0; i < strlen(send2); i++)
//	       {   	
//	    	   while (app_uart_put((uint8_t) send2[i]) != NRF_SUCCESS);
//	    	   nrf_delay_ms(10);
//	    	
////	    		sprintf(buf,"send[i]=%c\r\n",send[i]);
////	        SEGGER_RTT_WriteString(0,buf);
//	       }


	    for (int i = (MQTT_MAX_HEADER_SIZE-hlen); i < (length+MQTT_MAX_HEADER_SIZE); i++)
			 // for (int i = 0; i <36; i++)
	    {   	
	    	   while (app_uart_put( (uint8_t) buf[i]) != NRF_SUCCESS);
				   sprintf(buf2,"buf[%d]=%d\r\n",i,buf[i]);
				   SEGGER_RTT_WriteString(0,buf2);
				   SEGGER_RTT_WriteString(0,"f\r\n");
	    	   nrf_delay_ms(10);
	    	
	    }    		
//    rc = _client->write(buf+(MQTT_MAX_HEADER_SIZE-hlen),length+hlen);
//		  SEGGER_RTT_WriteString(0,"END\r\n");
//			for(int i=0;i<10;i++)
//			{ 
//					 sprintf(buf2,"buf[%d]=%d\r\n",i,buf[i]);
//				   SEGGER_RTT_WriteString(0,buf2);
//				
//			}
//      lastOutActivity = millis();
//    return (rc == hlen+length);
			return true;
#endif
}
uint16_t writeString(const char* string, uint8_t* buf, uint16_t pos) {
    const char* idp = string;
    uint16_t i = 0;
    pos += 2;
    while (*idp) {
        buf[pos++] = *idp++;
        i++;
    }
    buf[pos-i-2] = (i >> 8);
    buf[pos-i-1] = (i & 0xFF);
    return pos;
}


//bool subscribe(const char* topic) {
//    return subscribe(topic, 0);
//}
//
//bool subscribe(const char* topic, uint8_t qos) {
//    size_t topicLength = strnlen(topic, bufferSize);
//    if (topic == 0) {
//        return false;
//    }
//    if (qos > 1) {
//        return false;
//    }
//    if (bufferSize < 9 + topicLength) {
//        // Too long
//        return false;
//    }
//    if (connected()) {
//        // Leave room in the buffer for header and variable length field
//        uint16_t length = MQTT_MAX_HEADER_SIZE;
//        nextMsgId++;
//        if (nextMsgId == 0) {
//            nextMsgId = 1;
//        }
//        buffer[length++] = (nextMsgId >> 8);
//        buffer[length++] = (nextMsgId & 0xFF);
//        length = writeString((char*)topic, buffer,length);
//        buffer[length++] = qos;
//        return write(MQTTSUBSCRIBE|MQTTQOS1,buffer,length-MQTT_MAX_HEADER_SIZE);
//    }
//    return false;
//}

//bool unsubscribe(const char* topic) {
//	size_t topicLength = strnlen(topic, bufferSize);
//    if (topic == 0) {
//        return false;
//    }
//    if (bufferSize < 9 + topicLength) {
//        // Too long
//        return false;
//    }
//    if (connected()) {
//        uint16_t length = MQTT_MAX_HEADER_SIZE;
//        nextMsgId++;
//        if (nextMsgId == 0) {
//            nextMsgId = 1;
//        }
//        buffer[length++] = (nextMsgId >> 8);
//        buffer[length++] = (nextMsgId & 0xFF);
//        length = writeString(topic, buffer,length);
//        return write(MQTTUNSUBSCRIBE|MQTTQOS1,buffer,length-MQTT_MAX_HEADER_SIZE);
//    }
//    return false;
//}

void disconnect() {
    buffer[0] = MQTTDISCONNECT;
    buffer[1] = 0;
	// TODO: app_uart_put	
//    _client->write(buffer,2);
    _state = MQTT_DISCONNECTED;
//    _client->flush();
	//TODO:at commands for tcp stop
//    _client->stop();
    lastInActivity = lastOutActivity = millis();
}




bool connected() {
	
	
	
    bool rc;
//    if (_client == NULL ) {
//        rc = false;
//    } 
//		else {
        rc = clinet_connect_f;
        if (!rc) {
            if (_state == MQTT_CONNECTED) {
                _state = MQTT_CONNECTION_LOST;
//                _client->flush();
//                _client->stop();
            }
        } else {
            return _state == MQTT_CONNECTED;
        }
//    }
    return rc;
}





//PubSubClient& setServer(uint8_t * ip, uint16_t port) {
//    IPAddress addr(ip[0],ip[1],ip[2],ip[3]);
//    return setServer(addr,port);
//}
//
//PubSubClient& setServer(IPAddress ip, uint16_t port) {
//    this->ip = ip;
//    this->port = port;
//    this->domain = NULL;
//    return *this;
//}
//
//PubSubClient& setServer(const char * domain, uint16_t port) {
//    this->domain = domain;
//    this->port = port;
//    return *this;
//}
//
//PubSubClient& setCallback(MQTT_CALLBACK_SIGNATURE) {
//    this->callback = callback;
//    return *this;
//}
//
//PubSubClient& setClient(Client& client){
//    this->_client = &client;
//    return *this;
//}
//
//PubSubClient& setStream(Stream& stream){
//    this->stream = &stream;
//    return *this;
//}
//
//int state() {
//    return _state;
//}
//
//bool setBufferSize(uint16_t size) {
//    if (size == 0) {
//        // Cannot set it back to 0
//        return false;
//    }
//    if (bufferSize == 0) {
//        buffer = (uint8_t*)malloc(size);
//    } else {
//        uint8_t* newBuffer = (uint8_t*)realloc(buffer, size);
//        if (newBuffer != NULL) {
//            buffer = newBuffer;
//        } else {
//            return false;
//        }
//    }
//    bufferSize = size;
//    return (buffer != NULL);
//}
//
//uint16_t getBufferSize() {
//    return bufferSize;
//}
//PubSubClient& setKeepAlive(uint16_t keepAlive) {
//    this->keepAlive = keepAlive;
//    return *this;
//}
//PubSubClient& setSocketTimeout(uint16_t timeout) {
//    this->socketTimeout = timeout;
//    return *this;
//}

