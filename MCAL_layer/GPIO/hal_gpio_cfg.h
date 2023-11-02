/* 
 * File:   hal_gpio_cfg.c
 * Author: m7md
 *
 * Created on 16 August 2023, 20:05
 */

#ifndef DEVICE_CONFIG_H
#define	DEVICE_CONFIG_H

/* Includes */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro Declarations */
#define _XTAL_FREQ  4000000 

/* Macro Function Declarations */
#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00

/* Data Types Declarations */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;

typedef uint8   Std_ReturnType;

#endif	/* DEVICE_CONFIG_H */