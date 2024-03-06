/* 
 * File:   hal_usart.h
 * Author: OKTA
 *
 * Created on January 30, 2024, 6:28 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*---------- section : Includes --------------------*/
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"


/*---------- section : Macro Declarations --------------------*/

/*  EUSART Mode Select  */
#define EUSART_SYNCHRONOUS_MODE                     1
#define EUSART_ASYNCHRONOUS_MODE                    0


/*==============Baud Rate====================*/
/* EUSART Baud Rate Select */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED              1
#define EUSART_ASYNCHRONOUS_LOW_SPEED               0

/* EUSART 16-Bit Baud Rate  */
#define EUSART_16BIT_BAUD_RATE_GEN                  1
#define EUSART_08BIT_BAUD_RATE_GEN                  0


/*==============TX====================*/
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE               1
#define EUSART_ASYNCHRONOUS_TX_DISABLE              0

/* EUSART 9-Bit Transmit */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE         0

/* EUSART Transmit Interrupt */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE    0


/*==============RX====================*/
/* EUSART Receive Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE               1
#define EUSART_ASYNCHRONOUS_RX_DISABLE              0

/* EUSART 9-Bit Receive */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE         0

/* EUSART Receive Interrupt */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE    0


/*==============Error====================*/
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED               1
#define EUSART_FRAMING_ERROR_CLEARED                0


/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED               1
#define EUSART_OVERRUN_ERROR_CLEARED                0

/*---------- section : Macro Function declarations --------------------*/

/* Enable & Disable EUSART */
#define EUSART_MODULE_ENABLE()                 (RCSTAbits.SPEN = 1)
#define EUSART_MODULE_DISABLE()                (RCSTAbits.SPEN = 0)


/*==============TX====================*/
/* EUSART Transmit Enable & Disable */
#define EUSART_ASYNC_TX_ENABLE()               (TXSTAbits.TXEN = 1)
#define EUSART_ASYNC_TX_DISABLE()              (TXSTAbits.TXEN = 0)

/* EUSART 9-Bit Transmit */
#define EUSART_ASYNC_9BIT_TX_ENABLE()          (TXSTAbits.TX9 = 1)
#define EUSART_ASYNC_9BIT_TX_DISABLE()         (TXSTAbits.TX9 = 0)


/*==============RX====================*/
/* EUSART Receiver Enable & Disable */
#define EUSART_ASYNC_RX_ENABLE()               (RCSTAbits.CREN = 1)
#define EUSART_ASYNC_RX_DISABLE()              (RCSTAbits.CREN = 0)

/* EUSART 9-Bit Receiver */
#define EUSART_ASYNC_9BIT_RX_ENABLE()          (RCSTAbits.RX9 = 1)
#define EUSART_ASYNC_9BIT_RX_DISABLE()         (RCSTAbits.RX9 = 0)


/* To avoid the Error */
#define EUSART_RECEIVER_DISABLE()              (RCSTAbits.CREN = 0)
#define EUSART_RECEIVER_ENABLE()               (RCSTAbits.CREN = 1)
/*---------- section : Data Type Declarations --------------------*/
typedef enum
{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,       
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT        
}baudrate_gen_t;

typedef struct
{
    uint8 usart_tx_reserved                   : 5;
    uint8 usart_tx_enable                     : 1;
    uint8 usart_tx_interrupt_enable           : 1;
    uint8 usart_tx_9bit_enable                : 1;
    interrupt_priority_cfg  usart_tx_priority ;
}usart_tx_cfg_t;

typedef struct
{
    uint8 usart_rx_reserved                   : 5;
    uint8 usart_rx_enable                     : 1;
    uint8 usart_rx_interrupt_enable           : 1;
    uint8 usart_rx_9bit_enable                : 1;
    interrupt_priority_cfg  usart_rx_priority ;
}usart_rx_cfg_t;

typedef union
{
    struct
    {
        uint8 usart_tx_reserved : 6;
        uint8 usart_ferr        : 1;
        uint8 usart_oerr        : 1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;

    void (* EUSART_TXDefaultInterruptHandler)(void); /* Call back of Transmit */
    void (* EUSART_RXDefaultInterruptHandler)(void); /* Call back of receive */
    void (* EUSART_FramingrErrorHandler)(void);      /* Call back of framing error */
    void (* EUSART_OverrunErrorHandler)(void);       /* Call back of overrun error */

  
}usart_t;
/*---------- section : Function declarations --------------------*/

/**
 * @brief Function to initialize the  EUSART module
 * @param _eusart pointer to object to access the EUSART
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);

/**
 * @brief  De_initialization the EUSART
 * @param _eusart pointer to object to access the EUSART
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);









/**
 * @brief Get value from EUSART receiver registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data pointer to get the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data);

/**
 * @brief Get value from EUSART receiver registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data pointer to get the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);

/**
 * @brief Restart the EUSART REVEIVER to avoid the overrun error
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_RX_RESTART(void);





/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data);

/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);

/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);






#endif	/* HAL_USART_H */

