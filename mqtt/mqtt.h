/*
This is Hoom's mqtt library for nrf51822
Developed by Mahdi Moeini
Based on adafruit Fona library for arduino
*/
#include "stdint.h"
#include <stdlib.h>
#include <stdbool.h>
#include "nrf_drv_config.h"
#define MY_TIMER	NRF_TIMER1
#define MY_TIMER_IRQHandler TIMER1_IRQHandler
#define MY_TIMER_IRQn       TIMER1_IRQn
#define GATT_MTU_SIZE_DEFAULT 23
#define BLE_NUS_MAX_DATA_LEN           (GATT_MTU_SIZE_DEFAULT - 3) /**< Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */


static uint32_t my_timer_seconds;
static uint32_t my_timer_10ms=0;


uint8_t getReply(char *send, uint16_t timeout,int mqtt_delay);

uint8_t readline(uint16_t timeout);
void at_com(char * at_com,int delay,int mqtt_delay);
bool at_com_check(char * at_com,char*expected_reply,uint8_t retry,int delay,int mqtt_delay);
bool    sendCheckReply(char*send ,char*reply,int16_t timeout,int mqtt_delay);
void uart_init(void);
uint64_t millis(void);
void my_timer_start(void);
