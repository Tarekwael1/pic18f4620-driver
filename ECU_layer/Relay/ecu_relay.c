/* 
 * File:   ecu_relay.c
 * Author: OKTA
 *
 * Created on September 20, 2023, 12:44 PM
 */


#include "ecu_relay.h"


std_ReturnType relay_initialize(const relay_t *_relay)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->reley_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->reley_status};
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

std_ReturnType relay_turn_on(const relay_t *_relay)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->reley_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->reley_status};
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }   
    return ret;    
}

std_ReturnType relay_turn_off(const relay_t *_relay)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->reley_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->reley_status};
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;    
}




