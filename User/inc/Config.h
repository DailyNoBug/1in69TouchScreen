//
// Created by lsc on 23-7-29.
//

#ifndef INC_1IN69T_CONFIG_H
#define INC_1IN69T_CONFIG_H
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_spi.h"
#include "spi.h"
#include "tim.h"
#ifndef uint8_t
#include "stdint.h"
#endif
#define UBYTE uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define DEV_DC_PIN  GPIOA,GPIO_PIN_4
#define DEV_CS_PIN  GPIOA,GPIO_PIN_3
#define DEV_RST_PIN GPIOA,GPIO_PIN_2
#define DEV_BL_PIN  TIM1->CCR1
#define DEV_Digital_Write(_pin, _value) HAL_GPIO_WritePin(_pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) HAL_GPIO_ReadPin(_pin)

#define DEV_Set_PWM(_Value)     DEV_BL_PIN= _Value
#define DEV_Delay_ms(__xms) HAL_Delay(__xms)
/**
 * SPI Write
 * */
void DEV_SPI_Write(UBYTE _data);
/**
 * module init
 * */
int DEV_Module_init(void);
/**
 * module exit
 * */
void DEV_Module_Exit(void);
#endif //INC_1IN69T_CONFIG_H
