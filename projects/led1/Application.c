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

led_t led5 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN4,.led_status = LED_OFF};

led_t led6 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN5,.led_status = LED_OFF};

led_t led7 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN6,.led_status = LED_OFF};

led_t led8 = {.port_name = PORTC_INDEX,.pin= GPIO_PIN7,.led_status = LED_OFF};

int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    
    
    while(1)
    {
        ret = led_turn_on(&led1);
        __delay_ms(100);
        ret = led_turn_on(&led2);
        __delay_ms(100);
        ret = led_turn_on(&led3);
        __delay_ms(100);
        ret = led_turn_on(&led4);
        __delay_ms(100);
        ret = led_turn_on(&led5);
        __delay_ms(100);
        ret = led_turn_on(&led6);
        __delay_ms(100);
        ret = led_turn_on(&led7);
        __delay_ms(100);
        ret = led_turn_on(&led8);
        __delay_ms(100);
        ret = led_turn_off(&led8);
        __delay_ms(100);
        ret = led_turn_off(&led7);
        __delay_ms(100);
        ret = led_turn_off(&led6);
        __delay_ms(100);
        ret = led_turn_off(&led5);
        __delay_ms(100);
        ret = led_turn_off(&led4);
        __delay_ms(100);
        ret = led_turn_off(&led3);
        __delay_ms(100);
        ret = led_turn_off(&led2);
        __delay_ms(100);
        ret = led_turn_off(&led1);
        __delay_ms(100);
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
    ret = led_initialize(&led5);
    ret = led_initialize(&led6);
    ret = led_initialize(&led7);
    ret = led_initialize(&led8);
}

