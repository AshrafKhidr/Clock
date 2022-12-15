#include "ecu_7_segment.h"


Std_ReturnType seven_segment_initialize(segment_t *seg){
     Std_ReturnType ret = E_OK;
 
    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[0]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[1]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[2]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[3]));
    }
    return ret;
}
Std_ReturnType seven_segment_write_number(segment_t *seg , uint8 number){
    Std_ReturnType ret = E_OK;
 
    if( (NULL == seg) || (number > 9) ){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pins[0]) , (number >> 0) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[1]) , (number >> 1) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[2]) , (number >> 2) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[3]) , (number >> 3) & 1);
    }
    return ret;
}