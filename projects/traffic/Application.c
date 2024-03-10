/* 
 * File:   Application.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "application.h"

uint8 number = 0 , number_bcd = 0  ;

int main()
{
    std_ReturnType ret = E_NOT_OK;
    application_initialize(); 
    while(1)
    {
        ret = led_turn_on(&led2);
        for(number = 10; number > 0; number--)
        {
            number_bcd = ((uint8)number%10) | (((uint8)number/10) << 4);
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            __delay_ms(500);
        }
        ret = led_turn_off(&led2);
        ret = led_turn_on(&led1);
        for(number = 30; number > 0; number--)
        {
            number_bcd = ((uint8)number%10) | (((uint8)number/10) << 4);
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            __delay_ms(500);
        }
        ret = led_turn_off(&led1);
        ret = led_turn_on(&led2);
        for(number = 10; number > 0; number--)
        {
            number_bcd = ((uint8)number%10) | (((uint8)number/10) << 4);
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            __delay_ms(500);
        }
        ret = led_turn_off(&led2);
        ret = led_turn_on(&led3);
        for(number = 30; number >= 0; number--)
        {
            number_bcd = ((uint8)number%10) | (((uint8)number/10) << 4);
            ret = gpio_port_write_logic(PORTC_INDEX, number_bcd);
            __delay_ms(500);
        }
        ret = led_turn_off(&led3); 
    }      
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
}