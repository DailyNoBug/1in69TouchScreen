//
// Created by lsc on 23-7-29.
//

#ifndef INC_1IN69T_LCD_1IN69_H
#define INC_1IN69T_LCD_1IN69_H
#include "Config.h"
#define LCD_1IN69_HEIGHT 280
#define LCD_1IN69_WIDTH 240
#define HORIZONTAL 0
#define VERTICAL   1

#define LCD_1IN69_CS_0  DEV_Digital_Write(DEV_CS_PIN, 0)
#define LCD_1IN69_CS_1  DEV_Digital_Write(DEV_CS_PIN, 1)

#define LCD_1IN69_RST_0 DEV_Digital_Write(DEV_RST_PIN, 0)
#define LCD_1IN69_RST_1 DEV_Digital_Write(DEV_RST_PIN, 1)

#define LCD_1IN69_DC_0  DEV_Digital_Write(DEV_DC_PIN, 0)
#define LCD_1IN69_DC_1  DEV_Digital_Write(DEV_DC_PIN, 1)

typedef struct{
    UWORD WIDTH;
    UWORD HEIGHT;
    UBYTE SCAN_DIR;
}LCD_1IN69_ATTRIBUTES;
extern LCD_1IN69_ATTRIBUTES LCD_1IN69;

void LCD_1IN69_Init(UBYTE Scan_dir);
void LCD_1IN69_Clear(UWORD Color);
void LCD_1IN69_Display(UWORD *Image);
void LCD_1IN69_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image);
void LCD_1IN69_DrawPoint(UWORD X, UWORD Y, UWORD Color);
void LCD_1IN69_SetBackLight(UWORD Value);

#endif //INC_1IN69T_LCD_1IN69_H
