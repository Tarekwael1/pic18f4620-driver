/* 
 * File:   ecu_button.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */

#include "ecu_button.h"



std_ReturnType button_initialize(const button_t *btn)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }
    return ret ;
}

std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state)
{
    std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic_status = GPIO_LOW;
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED;
            }else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_RELEASED;
            }else
            {
                *btn_state = BUTTON_PRESSED;
            }
        }
        else
        {/*NOTING*/}
        ret = E_OK;
    }
    return ret ;
}