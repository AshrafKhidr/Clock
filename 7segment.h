/* 
 * File:   ecu_7_segment.h
 * Author: ashra
 *
 * Created on 18 October 2022, 16:28
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H


/* Section : Includes */
#include "../../mcal/GPIO/hal_gpio.h"

/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Types Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,            
            
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Function Declarations */

Std_ReturnType seven_segment_initialize(segment_t *seg);
Std_ReturnType seven_segment_write_number(segment_t *seg , uint8 number);


#endif	/* ECU_7_SEGMENT_H */

