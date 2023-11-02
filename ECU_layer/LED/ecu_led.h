/* 
 * File:   ecu_led.h
 * Author: m7md
 *
 * Created on 16 August 2023, 23:40
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef enum{
    LED_OFF = 0,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port          :3;
    uint8 pin           :3;
    uint8 led_status    :1;
}led_t;

/* Function Declarations */
Std_ReturnType led_intialiaze(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
#endif	/* ECU_LED_H */

