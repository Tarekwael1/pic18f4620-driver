/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN2,.led_status = LED_OFF};

led_t led2 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN3,.led_status = LED_OFF};


relay_t relay_1 = {
  .relay_port   = PORTC_INDEX,
  .reley_pin    = GPIO_PIN0,
  .reley_status = RELAY_OFF_STATUS
};
relay_t relay_2 = {
  .relay_port   = PORTC_INDEX,
  .reley_pin    = GPIO_PIN1,
  .reley_status = RELAY_OFF_STATUS
};


button_t BUTTON_1 = {
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_pin.port   = PORTC_INDEX,
  .button_pin.pin    = GPIO_PIN5,
  .button_state      = BUTTON_ACTIVE_LOW
};

button_t BUTTON_2 = {
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_pin.port   = PORTC_INDEX,
  .button_pin.pin    = GPIO_PIN6,
  .button_state      = BUTTON_ACTIVE_LOW
};

uint8 button_1 = 0;
uint8 button_2 = 0;

int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    
    
    while(1)
    {
        
        ret = button_read_state(&BUTTON_1, &button_1);
        ret = button_read_state(&BUTTON_2, &button_2);
        
        if(GPIO_HIGH == button_1)
        {
            ret = relay_turn_on(&relay_1);
            ret = relay_turn_off(&relay_2);
            ret = led_turn_on(&led1);
            ret = led_turn_off(&led2);  
        }
        else if(GPIO_HIGH == button_2)
        {
            ret = relay_turn_on(&relay_2);
            ret = relay_turn_off(&relay_1);
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led1);          
        }    
    }
    return ret;
} 
   



void application_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
    ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = button_initialize(&BUTTON_1);
    ret = button_initialize(&BUTTON_2);
    ret = relay_initialize(&relay_1);
    ret = relay_initialize(&relay_2);

}