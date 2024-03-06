/* 
 * File:   ecu_chr_lcd.h
 * Author: OKTA
 *
 * Created on September 25, 2023, 4:06 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

 /*section : Includes */
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*section : Macro Declarations   */
#define _LCD_CLEAR                  0X01
#define _LCD_RETURN_HOME            0X02
#define _LCD_ENTRY_MODE             0X06
#define _LCD_CUSTOR_OFF_DISPLAY_ON  0X0C
#define _LCD_CUSTOR_OFF_DISPLAY_OFF 0X08
#define _LCD_CUSTOR_ON_BLINK_ON     0X0F
#define _LCD_CUSTOR_ON_BLINK_OFF    0X0E
#define _LCD_DISPLAY_SHIFT_RIGHT    0X1C
#define _LCD_DISPLAY_SHIFT_LEFT     0X18
#define _LCD_8BIT_MODE_2_LINE       0X38
#define _LCD_4BIT_MODE_2_LINE       0X28
#define _LCD_CGRAM_START            0X40
#define _LCD_DDRAM_START            0X80


#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
/*section : Macro Function declarations */


/*section : Data Type Declarations */
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/*section : Function declarations */
/**
 * @brief Initialize 4bit lcd bins
 * @param lcd Pointer to the lcd_4bit module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);

/**
 * @brief Send an order to lcd to do (clear , shift, etc....)
 * @param lcd ointer to the lcd_4bit module configurations
 * @param command is an order that sent to lcd to do
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);

/**
 * @brief Send the data to lcd that will printed 
 * @param lcd Pointer to the lcd_4bit module configurations
 * @param data the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);

/**
 * @brief Send the data to lcd that will printed at any position
 * @param lcd Pointer to the lcd_4bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param data the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);

/**
 * @brief Send the string to lcd to print it 
 * @param lcd Pointer to the lcd_4bit module configurations
 * @param string the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *string);

/**
 * @brief Send the string to lcd to print it at any position
 * @param lcd Pointer to the lcd_4bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param string the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *string);

/**
 * @brief Used to display user define character 
 * @param lcd Pointer to the lcd_4bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param _ch Value by hex of the every row of the pixels in arr[8] -> ex arr[7,6,12,.....]
 * @param mem_pos Start of write custom character 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, 
                                        uint8 column, const uint8 _ch[], uint8 mem_pos);

/**
 * @brief Initialize the lcd pins (8)
 * @param lcd Pointer to the lcd_4bit module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);

/**
 * @brief Send an order to lcd to do (clear , shift, etc....)
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param command is an order that sent to lcd to do
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);

/**
 * @brief Send the data to lcd that will printed 
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param data the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);

/**
 * @brief Send the data to lcd that will printed at any position
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param data the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);

/**
 * @brief Send the string to lcd to print it 
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param string the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *string);

/**
 * @brief Send the string to lcd to print it at any position
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param string the data that will print
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *string);

/**
 * @brief
 * @param lcd Pointer to the lcd_8bit module configurations
 * @param row the row you want
 * @param column the column you want 
 * @param _ch
 * @param mem_pos
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, 
                                        uint8 column, const uint8 _ch[], uint8 mem_pos);

/**
 * @brief convert byte to string
 * @param value value the byte value
 * @param str return the string
 */
std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);

/**
 * @brief convert short to string
 * @param value value the short value
 * @param str return the string
 */
std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);

/**
 * @brief convert integer to string
 * @param value the integer value
 * @param str return the string
 */
std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);
#endif	/* ECU_CHR_LCD_H */

