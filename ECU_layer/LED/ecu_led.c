/* 
 * File:   ecu_led.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "ecu_led.h"



std_ReturnType led_initialize(const led_t *led)
{
    std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        
        gpio_pin_initialize(&pin_obj);
    }
    return ret ;
}

std_ReturnType led_turn_on(const led_t *led)
{
    std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret ;
}

std_ReturnType led_turn_off(const led_t *led)
{
   std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);        
    }    
    return ret ;
}

std_ReturnType led_turn_toggle(const led_t *led)
{
    std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_toggle_logic(&pin_obj);        
    }   
    return ret ;    
}