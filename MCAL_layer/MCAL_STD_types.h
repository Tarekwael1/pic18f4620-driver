/* 
 * File:   MCAL_STD_types.h
 * Author: OKTA
 *
 * Created on September 14, 2023, 9:08 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*section : Includes */
#include "std_libraries.h"
#include "compiler.h"

/*section : Macro Function declarations */

/*section : Data Type Declarations */
typedef unsigned char   uint8;  
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;  
typedef signed short    sint16;
typedef signed long     sint32;

typedef uint8 std_ReturnType;

/*section : Macro Declarations   */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (std_ReturnType)0x00
#define E_NOT_OK        (std_ReturnType)0x01

#define ZERO_INIT       0 

/*section : Function declarations */



#endif	/* MCAL_STD_TYPES_H */

