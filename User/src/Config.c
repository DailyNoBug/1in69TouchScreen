//
// Created by lsc on 23-7-29.
//
#include "Config.h"
void DEV_SPI_Write(UBYTE _data) {
    HAL_SPI_Transmit(&hspi1,(uint8_t *)&_data,1,500);
}
int DEV_Module_init(void) {
    DEV_Digital_Write(DEV_DC_PIN,1);
    DEV_Digital_Write(DEV_CS_PIN,1);
    DEV_Digital_Write(DEV_RST_PIN,1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    return 0;
}
void DEV_Module_Exit(void){
    DEV_Digital_Write(DEV_DC_PIN,0);
    DEV_Digital_Write(DEV_CS_PIN,0);
    DEV_Digital_Write(DEV_RST_PIN,0);
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
}