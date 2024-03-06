/* 
 * File:   ecu_seven_segment_cfg.c
 * Author: OKTA
 *
 * Created on September 21, 2023, 4:33 PM
 */

#include "ecu_seven_segment.h"


std_ReturnType seven_segment_initialize(const segment_t *seg)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGEMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGEMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGEMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGEMENT_PIN3]));
    }
    return ret;
}

std_ReturnType seven_segment_wirte_number(const segment_t *seg, uint8 number)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == seg) && (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN0]), number & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN1]), (number >> 1)&0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN2]), (number >> 2)&0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN3]), (number >> 3)&0x01);
    }
    return ret;
}
