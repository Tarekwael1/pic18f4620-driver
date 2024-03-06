/* 
 * File:   mcal_interrupt_manager.c
 * Author: OKTA
 *
 * Created on October 1, 2023, 9:47 AM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8  RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCUR == INTCONbits.INT0F))
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCUR == INTCON3bits.INT2F))
    {
        INT2_ISR();
    }
    else{/*NOTHING*/} 
}
   
void __interrupt(low_priority) InterruptManagerLow(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
}
    
#else 
void __interrupt() InterruptManagerHigh(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCUR == INTCONbits.INT0F))
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCUR == INTCON3bits.INT2F))
    {
        INT2_ISR();
    }
    else{/*NOTHING*/} 
/* ================== PortB External interrupt On Change Start ===============*/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB4 == GPIO_HIGH) && (1 == RB4_Flag))
    {
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{/*NOTHING*/} 
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB4 == GPIO_LOW) && (0 == RB4_Flag))
    {
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{/*NOTHING*/} 
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB5 == GPIO_HIGH) && (1 == RB5_Flag))
    {
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{/*NOTHING*/} 
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
       (PORTBbits.RB5 == GPIO_LOW) && (0 == RB5_Flag))
    {
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{/*NOTHING*/} 
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB6 == GPIO_HIGH) && (1 == RB6_Flag))
    {
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{/*NOTHING*/} 
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
       (PORTBbits.RB6 == GPIO_LOW) && (0 == RB6_Flag))
    {
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{/*NOTHING*/} 
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB7 == GPIO_HIGH) && (1 == RB7_Flag))
    {
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{/*NOTHING*/} 
    if((INTERRUPT_ENABLE == INTCONbits.RBIE ) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
       (PORTBbits.RB7 == GPIO_LOW) && (0 == RB7_Flag))
    {
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{/*NOTHING*/} 
/* ==================== PortB External interrupt On Change End ===============*/  
    
/* ========================== ADC interrupt Start ============================*/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
            ADC_ISR();
    }
    else{/*NOTHING*/}
    
    
    
/* ========================== ADC interrupt End ==============================*/  
    
/*=================================== TIMERS start ===========================*/  
    
    /* ==================== Timer0 interrupt Start ===========================*/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
            TIMER0_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== Timer0 interrupt End =============================*/ 
   
    /* ==================== Timer1 interrupt Start ===========================*/
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
            TIMER1_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== Timer1 interrupt End =============================*/ 
    
    /* ==================== Timer2 interrupt Start ===========================*/
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
            TIMER2_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== Timer2 interrupt End =============================*/
    
    /* ==================== Timer3 interrupt Start ===========================*/
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
            TIMER3_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== Timer3 interrupt End =============================*/
    
/*=================================== TIMERS End =============================*/ 
    
/*=================================== CCP start ==============================*/     
    /* ==================== CCP1 interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
            CCP1_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== CCP1 interrupt End ===============================*/
    /* ==================== CCP2 interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
            CCP2_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== CCP2 interrupt End ===============================*/
    
/*=================================== CCP End ================================*/ 
    
    
/*=================================== EUSART start ==============================*/     
    /* ==================== TX interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
            EUSART_TX_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== TX interrupt End ===============================*/
    /* ==================== RX interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
            EUSART_RX_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== RX interrupt End ===============================*/
    
/*=================================== EUSART End ================================*/ 
    
/*=================================== I2C start ==============================*/     
    /* ==================== I2C interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
            MSSP_I2C_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== I2C interrupt End ===============================*/
    /* ==================== BC interrupt Start =============================*/
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
            MSSP_I2C_BC_ISR();
    }
    else{/*NOTHING*/}
    /* ==================== BC interrupt End ===============================*/
    
/*=================================== I2C End ================================*/ 
}
#endif
