/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"
led_t led1 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN0,.led_status = LED_OFF};

led_t led2 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN1,.led_status = LED_OFF};

led_t led3 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN2,.led_status = LED_OFF};

led_t led4 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN3,.led_status = LED_OFF};



button_t btn_1 = {
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin  = GPIO_PIN4,
    .button_state = BUTTON_PRESSED
};


uint8 Button_State = 0;
uint8 counter = 0;
int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    
    
    while(1)
    {
        ret = button_read_state(&btn_1, &Button_State);
        
        if(GPIO_HIGH == Button_State)
        {
            counter++;
            __delay_ms(1000);
            switch(counter)
            {
                case 1:
                    ret = led_turn_on(&led1);
                    break;
                case 2:
                    ret = led_turn_on(&led2);
                    break;
                case 3:
                    ret = led_turn_on(&led3);
                    break;
                case 4:
                    ret = led_turn_on(&led4);
                    break;
                case 5:
                    ret = led_turn_off(&led1);
                    ret = led_turn_off(&led2);
                    ret = led_turn_off(&led3);
                    ret = led_turn_off(&led4);
                    counter = 0;
                    break;
                default:;    
            }
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
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    ret = button_initialize(&btn_1);
}

