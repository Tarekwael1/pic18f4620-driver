/* 
 * File:   hal_usart.c
 * Author: OKTA
 *
 * Created on January 30, 2024, 6:28 AM
 */

#include "hal_usart.h"
#include "../I2C/hal_i2c.h"


#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler EUSART_TXInterruptHandler = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler EUSART_RXInterruptHandler      = NULL;
static InterruptHandler EUSART_FramingInterruptHandler = NULL;
static InterruptHandler EUSART_OverrunInterruptHandler = NULL;
#endif



static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);  
static void EUSART_ASYNC_TX_INIT(const usart_t *_eusart);
static void EUSART_ASYNC_RX_INIT(const usart_t *_eusart);


/**
 * @brief Function to initialize the  EUSART module
 * @param _eusart pointer to object to access the EUSART
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_Init(const usart_t * _eusart)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _eusart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable EUSART module  */
        EUSART_MODULE_DISABLE();
        /* set TRISC (RC6&RD7) */
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        /* Initialize Baud Rate */
        EUSART_Baud_Rate_Calculation(_eusart);
        /* Initialize Transmitter */
        EUSART_ASYNC_TX_INIT(_eusart);
        /* Initialize Receiver */
        EUSART_ASYNC_RX_INIT(_eusart);
        /* Enable EUSART module  */
        EUSART_MODULE_ENABLE(); 
    }
    return ret;
}

/**
 * @brief  De_initialization the EUSART
 * @param _eusart pointer to object to access the EUSART
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _eusart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable EUSART module  */
        EUSART_MODULE_DISABLE();
    }
    return ret;
}

/**
 * @brief Get value from EUSART registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data pointer to get the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data)
{
    std_ReturnType ret = E_OK;
    while(!PIR1bits.RCIF);
    *_data = RCREG;
    return ret;
}

/**
 * @brief Get value from EUSART receiver registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data pointer to get the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data)
{
    std_ReturnType ret = E_OK;
    if(1 == PIR1bits.RCIF)
    {
        *_data = RCREG;
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    return ret;
}

/**
 * @brief Restart the EUSART REVEIVER to avoid the overrun error
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_RX_RESTART(void)
{
    std_ReturnType ret = E_OK;
    EUSART_RECEIVER_DISABLE();
    EUSART_RECEIVER_ENABLE(); 
    return ret;
}


/**
 * @brief Write value in EUSART registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data)
{
    
    std_ReturnType ret = E_OK;
    
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();    
#endif
    TXREG = _data;
    
    return ret;
}
/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len)
{
    std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    for(char_counter = ZERO_INIT; char_counter < str_len; char_counter++)
    {
        ret = EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
    }
    TXREG = _data;
    
    return ret;
}


/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data)
{
    std_ReturnType ret = E_NOT_OK;
    
    if(1 == TXSTAbits.TRMT)
    {
        #if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();    
        #endif
        TXREG = _data;
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }

    
    return ret;
}

/**
 * @brief Write value in EUSART transmitter registers
 * @param _eusart pointer to object to access the EUSART
 * @param _data The value then needed to write 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 
std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len)
{
    std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    for(char_counter = ZERO_INIT; char_counter < str_len; char_counter++)
    {
        ret = EUSART_ASYNC_WriteByteNonBlocking(_data[char_counter]);
    }
    TXREG = _data;
    
    return ret;
}
*/

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart)
{
    float Baud_Rate_Temp = 0;
    switch(_eusart->baudrate_gen_config)
    {
        case BAUDRATE_ASYN_8BIT_LOW_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;       //0
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_LOW_SPEED;  //0
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUD_RATE_GEN;     //0
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;       //0
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_HIGH_SPEED; //1
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUD_RATE_GEN;     //0
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;       //0
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_LOW_SPEED;  //0
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;     //1
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;       //0
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_HIGH_SPEED; //1
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;     //1
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT: 
            TXSTAbits.SYNC    = EUSART_SYNCHRONOUS_MODE;        //1
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUD_RATE_GEN;     //0
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC    = EUSART_SYNCHRONOUS_MODE;        //1
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;     //1
            Baud_Rate_Temp    = ((_XTAL_FREQ / (float)(_eusart->baudrate)) / 4) - 1;
            break;
        default:    ;
            
    }
   SPBRG  = (uint8)((uint32)Baud_Rate_Temp);
   SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8);
}

static void EUSART_ASYNC_TX_INIT(const usart_t *_eusart)
{
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable)
    {
        /* Enable The Transmit */
        EUSART_ASYNC_TX_ENABLE();
        /* Call back function */
        EUSART_TXInterruptHandler = _eusart->EUSART_TXDefaultInterruptHandler;
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == (_eusart->usart_tx_cfg.usart_tx_interrupt_enable))
        {
            /* Configure the interrupt */
            #if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
                EUSART_TX_InterruptEnable();
                /* Interrupt priority configurations */       
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                        INTERRUPT_PriotrityLevelsEnable();
                        if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority)
                        {
                            INTERRUPT_GlobalInterruptHighEnable();
                            EUSART_TX_SetHighPriority();
                        }
                        else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority)
                        {
                            INTERRUPT_GlobalInterruptLowEnable();
                            EUSART_TX_SetLowPriority();
                        }
                        else{/*NOTHING*/}  
            #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInrerruptEnable();
                #endif
            #endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == (_eusart->usart_tx_cfg.usart_tx_interrupt_enable))
        {
            EUSART_TX_InterruptDisable();
        }
        else{/* NOTHING */}

        /* EUSART 9-Bit Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == (_eusart->usart_tx_cfg.usart_tx_9bit_enable))
        {
            EUSART_ASYNC_9BIT_TX_ENABLE();
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == (_eusart->usart_tx_cfg.usart_tx_9bit_enable))
        {
            EUSART_ASYNC_9BIT_TX_DISABLE();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

static void EUSART_ASYNC_RX_INIT(const usart_t *_eusart)
{
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable)
    {
        /* Enable The Transmit */
        EUSART_ASYNC_RX_ENABLE();
        /* Call back function */
        EUSART_RXInterruptHandler = _eusart->EUSART_RXDefaultInterruptHandler;
        EUSART_FramingInterruptHandler = _eusart->EUSART_FramingrErrorHandler;
        EUSART_OverrunInterruptHandler = _eusart->EUSART_OverrunErrorHandler;
        /* EUSART Receive Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == (_eusart->usart_rx_cfg.usart_rx_interrupt_enable))
        {
            /* Configure the interrupt */
            #if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
                EUSART_RX_InterruptEnable();
                /* Interrupt priority configurations */       
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                        INTERRUPT_PriotrityLevelsEnable();
                        if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority)
                        {
                            INTERRUPT_GlobalInterruptHighEnable();
                            EUSART_RX_SetHighPriority();
                        }
                        else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority) 
                        {
                            INTERRUPT_GlobalInterruptLowEnable();
                            EUSART_RX_SetLowPriority();
                        }
                        else{/*NOTHING*/}  
            #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInrerruptEnable();
                #endif
            #endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == (_eusart->usart_rx_cfg.usart_rx_interrupt_enable))
        {
            EUSART_RX_InterruptDisable();
        }
        else{/* NOTHING */}

        /* EUSART 9-Bit Receive Configuration */
        if(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == (_eusart->usart_rx_cfg.usart_rx_9bit_enable))
        {
            EUSART_ASYNC_9BIT_RX_ENABLE();
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == (_eusart->usart_rx_cfg.usart_rx_9bit_enable))
        {
            EUSART_ASYNC_9BIT_RX_DISABLE();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}


void EUSART_TX_ISR(void)
{
    EUSART_TX_InterruptDisable();
    if(EUSART_TXInterruptHandler)
    {
        EUSART_TXInterruptHandler();
    }
    else{ /* NOTHING */}
}
void EUSART_RX_ISR(void)
{
    if(EUSART_RXInterruptHandler)
    {
        EUSART_RXInterruptHandler();
    }
    else{ /* NOTHING */}
    
    
    if(EUSART_FramingInterruptHandler)
    {
        EUSART_FramingInterruptHandler();
    }
    else{ /* NOTHING */}
    
    
    if(EUSART_OverrunInterruptHandler)
    {
        EUSART_OverrunInterruptHandler();
    }
    else{ /* NOTHING */}
}


