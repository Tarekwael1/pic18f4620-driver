/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"

pin_config_t GPIO_OBJ = {
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic     = GPIO_HIGH,
    .pin       = GPIO_PIN0,
    .port      = PORTC_INDEX,
};

uint8 var;

int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = gpio_pin_direction_initialize(&GPIO_OBJ);
    
    ret = gpio_pin_get_direction_status(&GPIO_OBJ, &var);
    while(1)
    {
        
    }
    return ret;
} 
   



void application_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
}

