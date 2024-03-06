/* 
 * File:   mcal_internal_interrupt.h
 * Author: OKTA
 *
 * Created on October 1, 2023, 9:46 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*section : Includes */
#include "mcal_interrupt_config.h"

/*section : Macro Declarations   */


/*section : Macro Function declarations */
/* ==================== ADC interrupt Start ===============================*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC module */
#define ADC_InterruptDisable()       (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the the ADC module */
#define ADC_InterruptEnable()        (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the the ADC module */
#define ADC_InterruptflagClear()     (PIR1bits.ADIF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set ADIP of the ADC interrupt priority to be High   */
    #define ADC_SetHighPriority()    (IPR1bits.ADIP = 1)
    /* This routine clear ADIP of the ADC interrupt priority to be Low   */
    #define ADC_SetLowPriority()     (IPR1bits.ADIP = 0)
    #endif
#endif
/* ==================== ADC interrupt End ===============================*/ 

/* ==================== Timer0 interrupt Start ===============================*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the TIMER0 module */
#define TIMER0_InterruptDisable()       (INTCONbits.TMR0IE = 0)
/* This routine sets the overflow interrupt enable for the TIMER0 module */
#define TIMER0_InterruptEnable()        (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the the TIMER0 module */
#define TIMER0_InterruptflagClear()     (INTCONbits.TMR0IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set ADIP of the TIMER0 interrupt priority to be High   */
    #define TIMER0_SetHighPriority()    (INTCON2bits.TMR0IP = 1)
    /* This routine clear ADIP of the TIMER0 interrupt priority to be Low   */
    #define TIMER0_SetLowPriority()     (INTCON2bits.TMR0IP = 0)
    #endif
#endif
/* ==================== Timer0 interrupt End ===============================*/ 

/* ==================== Timer1 interrupt Start ===============================*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the TIMER1 module */
#define TIMER1_InterruptDisable()       (PIE1bits.TMR1IE = 0)
/* This routine sets the overflow interrupt enable for the TIMER1 module */
#define TIMER1_InterruptEnable()        (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the the TIMER1 module */
#define TIMER1_InterruptflagClear()     (PIR1bits.TMR1IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set TMR1IP of the TIMER1 interrupt priority to be High   */
    #define TIMER1_SetHighPriority()    (IPR1bits.TMR1IP = 1)
    /* This routine clear TMR1IP of the TIMER1 interrupt priority to be Low   */
    #define TIMER1_SetLowPriority()     (IPR1bits.TMR1IP = 0)
    #endif
#endif
/* ==================== Timer1 interrupt End ===============================*/ 

/* ==================== Timer2 interrupt Start ===============================*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the TIMER2 module */
#define TIMER2_InterruptDisable()       (PIE1bits.TMR2IE = 0)
/* This routine sets the overflow interrupt enable for the TIMER2 module */
#define TIMER2_InterruptEnable()        (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the the TIMER2 module */
#define TIMER2_InterruptflagClear()     (PIR1bits.TMR2IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set TMR2IP of the TIMER2 interrupt priority to be High   */
    #define TIMER2_SetHighPriority()    (IPR1bits.TMR2IP = 1)
    /* This routine clear TMR2IP of the TIMER2 interrupt priority to be Low   */
    #define TIMER2_SetLowPriority()     (IPR1bits.TMR2IP = 0)
    #endif
#endif
/* ==================== Timer2 interrupt End ===============================*/ 

/* ==================== Timer3 interrupt Start ===============================*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the TIMER3 module */
#define TIMER3_InterruptDisable()       (PIE2bits.TMR3IE = 0)
/* This routine sets the overflow interrupt enable for the TIMER3 module */
#define TIMER3_InterruptEnable()        (PIE2bits.TMR3IE = 1)
/* This routine clears the interrupt flag for the the TIMER3 module */
#define TIMER3_InterruptflagClear()     (PIR2bits.TMR3IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set TMR3IP of the TIMER3 interrupt priority to be High   */
    #define TIMER3_SetHighPriority()    (IPR2bits.TMR3IP = 1)
    /* This routine clear TMR3IP of the TIMER3 interrupt priority to be Low   */
    #define TIMER3_SetLowPriority()     (IPR2bits.TMR3IP = 0)
    #endif
#endif
/* ==================== Timer3 interrupt End ===============================*/ 

/* ==================== CCP1 interrupt Start ===============================*/
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the CCP1 module */
#define CCP1_InterruptDisable()       (PIE1bits.CCP1IE = 0)
/* This routine sets the overflow interrupt enable for the CCP1 module */
#define CCP1_InterruptEnable()        (PIE1bits.CCP1IE = 1)
/* This routine clears the interrupt flag for the the CCP1 module */
#define CCP1_InterruptflagClear()     (PIR1bits.CCP1IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set CCP1IP of the CCP1 interrupt priority to be High   */
    #define CCP1_SetHighPriority()    (IPR1bits.CCP1IP = 1)
    /* This routine clear CCP1IP of the CCP1 interrupt priority to be Low   */
    #define CCP1_SetLowPriority()     (IPR1bits.CCP1IP = 0)
    #endif
#endif
/* ==================== CCP1 interrupt End ===============================*/  


/* ==================== CCP2 interrupt Start ===============================*/
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the CCP2 module */
#define CCP2_InterruptDisable()       (PIE2bits.CCP2IE = 0)
/* This routine sets the overflow interrupt enable for the CCP2 module */
#define CCP2_InterruptEnable()        (PIE2bits.CCP2IE = 1)
/* This routine clears the interrupt flag for the the CCP2 module */
#define CCP2_InterruptflagClear()     (PIR2bits.CCP2IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set CCP2IP of the CCP2 interrupt priority to be High   */
    #define CCP2_SetHighPriority()    (IPR2bits.CCP2IP = 1)
    /* This routine clear CCP2IP of the CCP2 interrupt priority to be Low   */
    #define CCP2_SetLowPriority()     (IPR2bits.CCP2IP = 0)
    #endif
#endif
/* ==================== CCP2 interrupt End ===============================*/  


/* ==================== EUSART interrupt Start ===============================*/

/* ================ TX =========================*/

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the EUSART_TX module */
#define EUSART_TX_InterruptDisable()       (PIE1bits.TXIE = 0)
/* This routine sets the overflow interrupt enable for the EUSART_TX module */
#define EUSART_TX_InterruptEnable()        (PIE1bits.TXIE = 1)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set TXIP of the EUSART_TX interrupt priority to be High   */
    #define EUSART_TX_SetHighPriority()    (IPR1bits.TXIP = 1)
    /* This routine clear TXIP of the EUSART_TX interrupt priority to be Low   */
    #define EUSART_TX_SetLowPriority()     (IPR1bits.TXIP = 0)
    #endif
#endif

/* ================ RX =========================*/
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the EUSART_RX module */
#define EUSART_RX_InterruptDisable()       (PIE1bits.RCIE = 0)
/* This routine sets the overflow interrupt enable for the EUSART_RX module */
#define EUSART_RX_InterruptEnable()        (PIE1bits.RCIE = 1)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set RCIP of the EUSART_RX interrupt priority to be High   */
    #define EUSART_RX_SetHighPriority()    (IPR1bits.RCIP = 1)
    /* This routine clear RCIP of the EUSART_RX interrupt priority to be Low   */
    #define EUSART_RX_SetLowPriority()     (IPR1bits.RCIP = 0)
    #endif
#endif
/* ==================== EUSART interrupt End ===============================*/  


/* ==================== MSSP I2C interrupt Start ===============================*/

/* ================ I2C =========================*/

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the MSSP I2C module */
#define MSSP_I2C_InterruptDisable()       (PIE1bits.SSPIE = 0)
/* This routine sets the overflow interrupt enable for the MSSP I2C module */
#define MSSP_I2C_InterruptEnable()        (PIE1bits.SSPIE = 1)
/* This routine clears the interrupt flag for the the MSSP I2C module */
#define MSSP_I2C_InterruptflagClear()     (PIR1bits.SSPIF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set SSPIP of the MSSP I2C interrupt priority to be High   */
    #define MSSP_I2C_SetHighPriority()    (IPR1bits.SSPIP = 1)
    /* This routine clear SSPIP of the MSSP I2C interrupt priority to be Low   */
    #define MSSP_I2C_SetLowPriority()     (IPR1bits.SSPIP = 0)
    #endif
#endif

/* ================ Bus Collision =========================*/
#if MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the overflow interrupt enable for the MSSP I2C Bus Collision module */
#define MSSP_I2C_BUS_COL_InterruptDisable()   (PIE2bits.BCLIE = 0)
/* This routine sets the overflow interrupt enable for the MSSP I2C Bus Collision module */
#define MSSP_I2C_BUS_COL_InterruptEnable()    (PIE2bits.BCLIE = 1)
/* This routine clears the interrupt flag for the the MSSP I2C Bus Collision module */
#define MSSP_I2C_BUS_COL_InterruptflagClear() (PIR2bits.BCLIF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    /* This routine set BCLIP of the MSSP I2C Bus Collision interrupt priority to be High   */
    #define MSSP_I2C_BUS_COL_SetHighPriority()(IPR2bits.BCLIP = 1)
    /* This routine clear BCLIP of the MSSP I2C Bus Collision interrupt priority to be Low   */
    #define MSSP_I2C_BUS_COL_SetLowPriority() (IPR2bits.BCLIP = 0)
    #endif
#endif

/* ==================== EUSART interrupt End ===============================*/  

/*section : Data Type Declarations */
typedef void (*InterruptHandler)(void);

/*section : Function declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

