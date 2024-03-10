/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"

dc_motor_t dc_motor_1 = {
    .dc_motor_pin[0].port      = PORTC_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN4,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction =GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port      = PORTC_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN5,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction =GPIO_DIRECTION_OUTPUT,
};

dc_motor_t dc_motor_2 = {
    .dc_motor_pin[0].port      = PORTC_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN6,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction =GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port      = PORTC_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN7,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction =GPIO_DIRECTION_OUTPUT,
};

led_t led1 = {.port_name = PORTD_INDEX,.pin= GPIO_PIN0,.led_status = LED_OFF}; //RED
led_t led2 = {.port_name = PORTD_INDEX,.pin= GPIO_PIN1,.led_status = LED_OFF}; //GREEN


button_t Button_1 = {
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_pin.pin    = GPIO_PIN2,
    .button_pin.port   = PORTD_INDEX,   
    .button_state      = BUTTON_PRESSED       
};

button_t Button_2 = {
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_pin.pin    = GPIO_PIN3,
    .button_pin.port   = PORTD_INDEX,   
    .button_state      = BUTTON_PRESSED       
};
button_t Button_3 = {
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_pin.pin    = GPIO_PIN4,
    .button_pin.port   = PORTD_INDEX,   
    .button_state      = BUTTON_PRESSED       
};

uint8 B1_State = 0, B2_State = 0, B3_State = 0;
uint8 number = 0 , number_bcd = 0;


int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    
    
    while(1)
    {
        number_bcd = ((uint8)number%10) | (((uint8)number/10) << 4);
        ret = button_read_state(&Button_1, &B1_State);
        ret = button_read_state(&Button_2, &B2_State);
        ret = button_read_state(&Button_3, &B3_State);
        if(GPIO_HIGH == B1_State)
        {
            number = 1;
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led1);
            ret = dc_motor_move_right(&dc_motor_1);
            ret = dc_motor_move_right(&dc_motor_2);
        }
        else if(GPIO_HIGH == B2_State)
        {
            number = 2;
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led1);
            ret = dc_motor_move_left(&dc_motor_1);
            ret = dc_motor_move_left(&dc_motor_2);
        }
        else if(GPIO_HIGH == B3_State)
        {
            number = 0;
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            ret = led_turn_off(&led2);
            ret = led_turn_on(&led1);
            ret = dc_motor_stop(&dc_motor_1);
            ret = dc_motor_stop(&dc_motor_2);
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
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
    ret = button_initialize(&Button_1);
    ret = button_initialize(&Button_2);
}