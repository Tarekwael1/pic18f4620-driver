/* 
 * File:   mcal_external_interrupt.h
 * Author: OKTA
 *
 * Created on October 1, 2023, 9:46 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*---------------------- section : Includes ----------------------*/
#include "mcal_interrupt_config.h"

/*---------------------- section : Macro Declarations ----------------------   */

/*---------------------- section : Macro Function declarations ---------------------- */

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt , INT0 */
#define EXT_INT0_InterruptDisable()    (INTCONbits.INT0IE = 0)
/* This routine sets the interrupt enable for the external interrupt , INT0 */
#define EXT_INT0_InterruptEnable()     (INTCONbits.INT0IE = 1)
/* This routine clears the interrupt flag for the external interrupt , INT0 */
#define EXT_INT0_InterruptflagClear()  (INTCONbits.INT0IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdgeSet()       (INTCON2bits.INTEDG0 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT0_FallingEdgeSet()      (INTCON2bits.INTEDG0 = 0)

/* This routine clears the interrupt enable for the external interrupt , INT1 */
#define EXT_INT1_InterruptDisable()    (INTCON3bits.INT1IE = 0)
/* This routine sets the interrupt enable for the external interrupt , INT1 */
#define EXT_INT1_InterruptEnable()     (INTCON3bits.INT1IE = 1)
/* This routine clears the interrupt flag for the external interrupt , INT1 */
#define EXT_INT1_InterruptflagClear()  (INTCON3bits.INT1IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdgeSet()       (INTCON2bits.INTEDG1 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdgeSet()      (INTCON2bits.INTEDG1 = 0)

/* This routine clears the interrupt enable for the external interrupt , INT2 */
#define EXT_INT2_InterruptDisable()    (INTCON3bits.INT2IE = 0)
/* This routine sets the interrupt enable for the external interrupt , INT2 */
#define EXT_INT2_InterruptEnable()     (INTCON3bits.INT2IE = 1)
/* This routine clears the interrupt flag for the external interrupt , INT2 */
#define EXT_INT2_InterruptflagClear()  (INTCON3bits.INT2IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT2_RisingEdgeSet()       (INTCON2bits.INTEDG2 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT2_FallingEdgeSet()      (INTCON2bits.INTEDG2 = 0)

    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set INT1 the external interrupt priority to be High   */
    #define EXT_INT1_SetHighPriority()     (INTCON3bits.INT1IP = 1)
    /* This routine set INT1 the external interrupt priority to be Low   */
    #define EXT_INT1_SetLowPriority()      (INTCON3bits.INT1IP = 0)
    /* This routine set INT2 the external interrupt priority to be High   */
    #define EXT_INT2_SetHighPriority()     (INTCON3bits.INT2IP = 1)
    /* This routine set INT2 the external interrupt priority to be Low   */
    #define EXT_INT2_SetLowPriority()      (INTCON3bits.INT2IP = 0)
    #endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for external interrupt , RBx */
#define EXT_RBx_InterruptDisable()     (INTCONbits.RBIE = 0)
/* This routine sets the interrupt enable for external interrupt , RBx */
#define EXT_RBx_InterruptEnable()      (INTCONbits.RBIE = 1)
/* This routine clears the interrupt flag for external interrupt , RBx */
#define EXT_RBx_InterruptFlagClear()   (INTCONbits.RBIF = 0)



    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set RBx the external interrupt priority to be High   */
    #define EXT_RBx_Priority_High()     (INTCON2bits.RBIP = 1)
    /* This routine set RBx the external interrupt priority to be Low   */
    #define EXT_RBx_Priority_Low()      (INTCON2bits.RBIP = 0)
    #endif

#endif
/* ---------------------- section : Data Type Declarations ---------------------- */

typedef void (*InterruptHandler)(void);

typedef enum
{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;

typedef enum
{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;


typedef struct 
{
    void (*EXT_InterruptHandler) (void);  
    pin_config_t            mcu_pin;
    interrupt_INTx_edge     edge;
    interrupt_INTx_src      source;
    interrupt_priority_cfg  priority;
}interrupt_INTx_t;

typedef struct 
{
    void (*EXT_InterruptHandler_HIGH) (void);
    void (*EXT_InterruptHandler_LOW) (void);
    pin_config_t            mcu_pin;
    interrupt_priority_cfg  priority;
}interrupt_RBx_t;

/*---------------------- section : Function declarations ---------------------- */
/**
 * @brief Initialization the INTx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);

/**
 * @brief DeInitialization the INTx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);

/**
 * @brief Initialization the RBx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);

/**
 * @brief DeInitialization the RBx interrupt
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

