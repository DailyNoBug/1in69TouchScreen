//
// Created by lsc on 23-7-29.
//
#include "1in69_test.h"
void test_lcd() {
    printf("LCD_1IN69 Demo\r\n");
    DEV_Module_init();

    printf("LCD_1IN69_ Init and Clear...\r\n");
    LCD_1IN69_SetBackLight(10);
    LCD_1IN69_Init(VERTICAL);
    LCD_1IN69_Clear(WHITE);
    LCD_1IN69_DrawPoint(20,20,RED);
    DEV_Delay_ms(1000);
    printf("quit...\r\n");
    DEV_Module_Exit();
}