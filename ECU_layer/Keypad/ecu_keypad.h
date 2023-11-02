/* 
 * File:   ecu_keypad.h
 * Author: m7md
 *
 * Created on 18 August 2023, 23:03
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/************************ Includes ************************/
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/************************  Macro Declaration ************************/
#define KEYPAD_ROW 4
#define KEYPAD_COLUMNS 4

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/
typedef struct{
    pin_config_t keypad_row_pins[KEYPAD_ROW];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
}keypad_t;

/************************  Software interface Declaration ************************/
Std_ReturnType keypad_intialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);
 
#endif	/* ECU_KEYPAD_H */

