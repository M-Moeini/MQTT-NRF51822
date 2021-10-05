//NORDIC PRE LIBS START.........................................................................
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "boards.h"
#include "nrf_delay.h"
//NORDIC PRE LIBS END...........................................................................
//HOOM LIBS START...............................................................................
#include "gpio_init.h"

//HOOM LIBS END.................................................................................
//NORDIC PRE GLOBAL CONS AND VARS START.........................................................
//NORDIC PRE GLOBAL CONS AND VARS END...........................................................
//HOOM CONS AND VARS START......................................................................
//HOOM CONS AND VARS END........................................................................
//NORDIC PRE FUNCTIONS START....................................................................
//NORDIC PRE FUNCTIONS END......................................................................
//HOOM FUNCTIONS START..........................................................................
void gpio_init(void)
{
		nrf_drv_gpiote_init();
    nrf_gpio_pin_dir_set(relay_pin_1, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(led_1, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(adv_pin, NRF_GPIO_PIN_DIR_OUTPUT);
		nrf_gpio_pin_dir_set(rc_send, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_clear(relay_pin_1);
    nrf_gpio_pin_clear(led_1);
    nrf_gpio_pin_clear(adv_pin);
    nrf_gpio_pin_clear(rc_send);
		nrf_gpio_pin_dir_set(rc_recieve, NRF_GPIO_PIN_DIR_INPUT);
		nrf_drv_gpiote_in_config_t in_config_1=GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
		in_config_1.pull= NRF_GPIO_PIN_NOPULL;
		nrf_drv_gpiote_in_event_enable(rc_recieve,true);

}

//HOOM EDDITION END GPIO INIT
//HOOM FUNCTIONS END............................................................................
