/* 
 * File:   ecu_keypad.c
 * Author: OKTA
 *
 * Created on September 23, 2023, 9:33 AM
 */

#include "ecu_keypad.h"


static const uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},   
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                    };

std_ReturnType keypad_initialize(const keypad_t *_keypad_obj)
{
    std_ReturnType ret = E_OK;
    uint8 rows_counetr = ZERO_INIT, columns_counter = ZERO_INIT;
    if(NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counetr = ZERO_INIT; rows_counetr < ECU_KEYPAD_ROW; rows_counetr++)
        {
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counetr]));
        }
        for(columns_counter = ZERO_INIT; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
        {
            ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret ;
}


std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value)
{
    std_ReturnType ret = E_OK;
    uint8 l_rows_counetr = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
    if((NULL == _keypad_obj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(l_rows_counetr = ZERO_INIT; l_rows_counetr < ECU_KEYPAD_ROW; l_rows_counetr++)
        {
            for(l_counter = ZERO_INIT; l_counter < ECU_KEYPAD_ROW; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
            }
            
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counetr]), GPIO_HIGH);
            __delay_ms(10);
            for(l_columns_counter = ZERO_INIT; l_columns_counter < ECU_KEYPAD_COLUMNS; l_columns_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = btn_values[l_rows_counetr][l_columns_counter];
                }
            }
        }
    }
    return ret ;
}

