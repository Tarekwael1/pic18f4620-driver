/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN4,.led_status = LED_OFF};

led_t led2 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN5,.led_status = LED_OFF};

button_t BUTTON_1 = {
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_pin.port   = PORTC_INDEX,
  .button_pin.pin    = GPIO_PIN6,
  .button_state      = BUTTON_ACTIVE_LOW
};

button_t BUTTON_2 = {
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_pin.port   = PORTC_INDEX,
  .button_pin.pin    = GPIO_PIN7,
  .button_state      = BUTTON_ACTIVE_LOW
};

button_t BUTTON_3 = {
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_pin.port   = PORTD_INDEX,
  .button_pin.pin    = GPIO_PIN0,
  .button_state      = BUTTON_ACTIVE_LOW
};

dc_motor_t dc_motor_1 = {
    .dc_motor_pin[0].port      = PORTC_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN0,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .dc_motor_pin[1].port      = PORTC_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN1,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
};

dc_motor_t dc_motor_2 = {
    .dc_motor_pin[0].port      = PORTC_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN2,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .dc_motor_pin[1].port      = PORTC_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN3,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
};

uint8 button_1 = 0;
uint8 button_2 = 0;
uint8 button_3 = 0;
int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    
    
    while(1)
    {
        
        ret = button_read_state(&BUTTON_1, &button_1);
        ret = button_read_state(&BUTTON_2, &button_2);
        ret = button_read_state(&BUTTON_3, &button_3);
        if(GPIO_HIGH == button_1)
        {
            ret = led_turn_on(&led1);
            ret = led_turn_off(&led2);
            ret = dc_motor_move_right(&dc_motor_1);
            ret = dc_motor_move_left(&dc_motor_2);
        }
        else if(GPIO_HIGH == button_2)
        {
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led1);  
            ret = dc_motor_move_right(&dc_motor_2);
            ret = dc_motor_move_left(&dc_motor_1);
        }    
        else if(GPIO_HIGH == button_3)
        {
            ret = led_turn_off(&led2);
            ret = led_turn_off(&led1);  
            ret = dc_motor_stop(&dc_motor_2);
            ret = dc_motor_stop(&dc_motor_1);
        }   
    }
    return ret;
} 
   



void application_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
    ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
    ret = gpio_port_direction_initialize(PORTD_INDEX, 0x00);
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = button_initialize(&BUTTON_1);
    ret = button_initialize(&BUTTON_2);
    ret = button_initialize(&BUTTON_3);
}