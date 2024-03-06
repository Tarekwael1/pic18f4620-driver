/* 
 * File:   ecu_dc_motor.c
 * Author: OKTA
 *
 * Created on September 20, 2023, 4:21 PM
 */


#include "ecu_dc_motor.h"




std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {  
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}
 
std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;    
}

std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret;    
}

std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2 ]), GPIO_LOW);
    }
    return ret;    
}

