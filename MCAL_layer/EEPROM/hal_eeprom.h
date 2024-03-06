/* 
 * File:   hal_eeprom.h
 * Author: OKTA
 *
 * Created on October 5, 2023, 10:55 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/*---------------------- section : Includes ----------------------*/
#include "../MCAL_STD_types.h"
#include "pic18f4620.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*---------------------- section : Macro Declarations ----------------------   */
/* Flash Program or Data EEPROM Memory Select */
#define ACCESS_FLASH_PROGRAM_MEMORY           1
#define ACCESS_DATA_EEPROM_MEMORY             0
/*  Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIGURATION_REGISTERS        1
#define ACCESS_FLASH_OR_EEPROM_MEMORY         0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_OR_EEPROM    1
#define INHIBITS_WRITE_CYCLES_FLASH_OR_EEPROM 0
/* Write Control */
#define INITIATES_DATA_EEPROM_WRITE_ERASE     1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED     0
/* Read Control */
#define INITIATES_DATA_EEPROM_READ            1
#define DOES_NOT_INITIATES_DATA_EEPROM_READ   0
/*---------------------- section : Macro Function declarations ---------------------- */


/* ---------------------- section : Data Type Declarations ---------------------- */


/*---------------------- section : Function declarations ---------------------- */


/**
 * @brief Write data in EEPROM 
 * @param bAdd The address of write data 
 * @param bData Data that will write 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);

/**
 * @brief Read data from EEPROM 
 * @param bAdd The address of write data 
 * @param bData Return data 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

