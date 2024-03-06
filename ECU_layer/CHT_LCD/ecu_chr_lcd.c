/* 
 * File:   ecu_chr_lcd.c
 * Author: OKTA
 *
 * Created on September 25, 2023, 4:06 PM
 */



#include "ecu_chr_lcd.h"

static std_ReturnType lcd_sent_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd);
static std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column); 

static std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd);
static std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);


std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd)
{
    std_ReturnType ret = E_OK;
    uint8 l_data_pins_counetr = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counetr = ZERO_INIT; l_data_pins_counetr < 4; l_data_pins_counetr++)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counetr]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, _LCD_CUSTOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_sent_4bits(lcd, command >> 4);
        ret = lcd_4bits_send_enable_signal(lcd);
        ret = lcd_sent_4bits(lcd, command);
        ret = lcd_4bits_send_enable_signal(lcd); 
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_sent_4bits(lcd, data >> 4);
        ret = lcd_4bits_send_enable_signal(lcd);
        ret = lcd_sent_4bits(lcd, data);
        ret = lcd_4bits_send_enable_signal(lcd); 
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bits_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *string)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*string)
        {
            ret = lcd_4bit_send_char_data(lcd, *string++);
        }
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *string)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bits_set_cursor(lcd, row, column);
        while(*string)
        {
            ret = lcd_4bit_send_char_data(lcd, *string++);
        }
    }
    return ret ;
}

std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, 
                                        uint8 column, const uint8 _ch[], uint8 mem_pos)
{
    std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter <= 8; ++lcd_counter)
        {
            ret = lcd_4bit_send_char_data(lcd, _ch[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret ;
}






std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd)
{
    std_ReturnType ret = E_OK;
    uint8 l_data_pins_counetr = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counetr = ZERO_INIT; l_data_pins_counetr < 8; l_data_pins_counetr++)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counetr]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, _LCD_CUSTOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command)
{
    std_ReturnType ret = E_OK;
    uint8 pin_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(pin_counter = ZERO_INIT; pin_counter < 8; pin_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),
                                        (command >> pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data)
{
    std_ReturnType ret = E_OK;
    uint8 pin_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(pin_counter = ZERO_INIT; pin_counter < 8; pin_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]),
                                        (data >> pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bits_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *string)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*string)
        {
            ret = lcd_8bit_send_char_data(lcd, *string++);
        }
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *string)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bits_set_cursor(lcd, row, column);
        while(*string)
        {
            ret = lcd_8bit_send_char_data(lcd, *string++);
        }
    }
    return ret ;
}

std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, 
                                        uint8 column, const uint8 _ch[], uint8 mem_pos)
{
    std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter <= 7; ++lcd_counter)
        {
            ret = lcd_8bit_send_char_data(lcd, _ch[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret ;
}







std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str)
{
    std_ReturnType ret = E_OK;
    uint8 Temp_String[4] = {0};
    uint8 DataCounter = 0;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 3);
        str[3] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret; 
}

std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
    std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret; 
}

std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str)
{
    std_ReturnType ret = E_OK;
    uint8 Temp_String[11] = {0};
    uint8 DataCounter = 0;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 10 );
        str[10] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret; 
}





static std_ReturnType lcd_sent_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command)
{
    std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret |= gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
        ret |= gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
        ret |= gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
        ret |= gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
    }
    return ret ;
}

static std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    std_ReturnType ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_ms(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret ;
}

static std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column)
{
    std_ReturnType ret = E_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;
        case ROW3: ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_4bit_send_command(lcd, (0xD4 + column)); break;
        default : ;
    }
    
    return ret ;
}




static std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd)
{
    std_ReturnType ret = E_OK;
  
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
     __delay_ms(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret ;
}


static std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column)
{
    std_ReturnType ret = E_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_8bit_send_command(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_8bit_send_command(lcd, (0xC0 + column)); break;
        case ROW3: ret = lcd_8bit_send_command(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_8bit_send_command(lcd, (0xD4 + column)); break;
        default : ;
    }
    
    return ret ;
}

