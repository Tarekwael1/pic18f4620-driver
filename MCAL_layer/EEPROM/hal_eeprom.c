/* 
 * File:   hal_eeprom.c
 * Author: OKTA
 *
 * Created on October 5, 2023, 10:55 AM
 */

#include "hal_eeprom.h"



/**
 * @brief Write data in EEPROM 
 * @param bAdd The address of write data 
 * @param bData Data that will write 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData)
{
    std_ReturnType ret = E_OK;
    /* Read The interrupt Status "Enable or Disable" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE; 
    /* Update the address Registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR  = (uint8)(bAdd & 0xFF);
    /* Update the data registers */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
    EECON1bits.CFGS  = ACCESS_FLASH_OR_EEPROM_MEMORY;
    /* Allows write cycles to flash program/data EEPROM */
    EECON1bits.WREN  = ALLOW_WRITE_CYCLES_FLASH_OR_EEPROM;  
    /* Disable all interrupts " General interrupts" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence : 0X55 -> 0XAA */
    EECON2 = 0x55;
    EECON2 = 0xAA; 
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATES_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to flash program / data EEPROM */
    EECON1bits.WREN  = INHIBITS_WRITE_CYCLES_FLASH_OR_EEPROM; 
    /* Restore the interrupt status "Enable or Disable" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

/**
 * @brief Read data from EEPROM 
 * @param bAdd The address of write data 
 * @param bData Return data 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
    std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Update the address Registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR  = (uint8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
        EECON1bits.CFGS  = ACCESS_FLASH_OR_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD    = INITIATES_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
        ret = E_OK;
    }
    return ret;
}



