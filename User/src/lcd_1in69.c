//
// Created by lsc on 23-7-29.
//
#include "lcd_1in69.h"
LCD_1IN69_ATTRIBUTES LCD_1IN69;
static void LCD_1IN69_Reset(void)
{
    LCD_1IN69_RST_1;
    DEV_Delay_ms(100);
    LCD_1IN69_RST_0;
    DEV_Delay_ms(100);
    LCD_1IN69_RST_1;
    DEV_Delay_ms(100);
}
static void LCD_1IN69_SendCommand(UBYTE Reg)
{
    LCD_1IN69_DC_0;
    LCD_1IN69_CS_0;
    DEV_SPI_Write(Reg);
    //LCD_1IN69_CS_1;
}
static void LCD_1IN69_SendData_8Bit(UBYTE Data)
{
    LCD_1IN69_DC_1;
    //LCD_1IN69_CS_0;
    DEV_SPI_Write(Data);
    //LCD_1IN69_CS_1;
}
static void LCD_1IN69_SendData_16Bit(UWORD Data)
{
    LCD_1IN69_DC_1;
    LCD_1IN69_CS_0;
    DEV_SPI_Write((Data >> 8) & 0xFF);
    DEV_SPI_Write(Data & 0xFF);
    LCD_1IN69_CS_1;
}

static void LCD_1IN69_InitReg(void)
{
    LCD_1IN69_SendCommand(0x36);
    LCD_1IN69_SendData_8Bit(0x00);

    LCD_1IN69_SendCommand(0x3A);
    LCD_1IN69_SendData_8Bit(0x05);

    LCD_1IN69_SendCommand(0xB2);
    LCD_1IN69_SendData_8Bit(0x0B);
    LCD_1IN69_SendData_8Bit(0x0B);
    LCD_1IN69_SendData_8Bit(0x00);
    LCD_1IN69_SendData_8Bit(0x33);
    LCD_1IN69_SendData_8Bit(0x35);

    LCD_1IN69_SendCommand(0xB7);
    LCD_1IN69_SendData_8Bit(0x11);

    LCD_1IN69_SendCommand(0xBB);
    LCD_1IN69_SendData_8Bit(0x35);

    LCD_1IN69_SendCommand(0xC0);
    LCD_1IN69_SendData_8Bit(0x2C);

    LCD_1IN69_SendCommand(0xC2);
    LCD_1IN69_SendData_8Bit(0x01);

    LCD_1IN69_SendCommand(0xC3);
    LCD_1IN69_SendData_8Bit(0x0D);

    LCD_1IN69_SendCommand(0xC4);
    LCD_1IN69_SendData_8Bit(0x20);

    LCD_1IN69_SendCommand(0xC6);
    LCD_1IN69_SendData_8Bit(0x13);

    LCD_1IN69_SendCommand(0xD0);
    LCD_1IN69_SendData_8Bit(0xA4);
    LCD_1IN69_SendData_8Bit(0xA1);

    LCD_1IN69_SendCommand(0xD6);
    LCD_1IN69_SendData_8Bit(0xA1);

    LCD_1IN69_SendCommand(0xE0);
    LCD_1IN69_SendData_8Bit(0xF0);
    LCD_1IN69_SendData_8Bit(0x06);
    LCD_1IN69_SendData_8Bit(0x0B);
    LCD_1IN69_SendData_8Bit(0x0A);
    LCD_1IN69_SendData_8Bit(0x09);
    LCD_1IN69_SendData_8Bit(0x26);
    LCD_1IN69_SendData_8Bit(0x29);
    LCD_1IN69_SendData_8Bit(0x33);
    LCD_1IN69_SendData_8Bit(0x41);
    LCD_1IN69_SendData_8Bit(0x18);
    LCD_1IN69_SendData_8Bit(0x16);
    LCD_1IN69_SendData_8Bit(0x15);
    LCD_1IN69_SendData_8Bit(0x29);
    LCD_1IN69_SendData_8Bit(0x2D);

    LCD_1IN69_SendCommand(0xE1);
    LCD_1IN69_SendData_8Bit(0xF0);
    LCD_1IN69_SendData_8Bit(0x04);
    LCD_1IN69_SendData_8Bit(0x08);
    LCD_1IN69_SendData_8Bit(0x08);
    LCD_1IN69_SendData_8Bit(0x07);
    LCD_1IN69_SendData_8Bit(0x03);
    LCD_1IN69_SendData_8Bit(0x28);
    LCD_1IN69_SendData_8Bit(0x32);
    LCD_1IN69_SendData_8Bit(0x40);
    LCD_1IN69_SendData_8Bit(0x3B);
    LCD_1IN69_SendData_8Bit(0x19);
    LCD_1IN69_SendData_8Bit(0x18);
    LCD_1IN69_SendData_8Bit(0x2A);
    LCD_1IN69_SendData_8Bit(0x2E);

    LCD_1IN69_SendCommand(0xE4);
    LCD_1IN69_SendData_8Bit(0x25);
    LCD_1IN69_SendData_8Bit(0x00);
    LCD_1IN69_SendData_8Bit(0x00);

    LCD_1IN69_SendCommand(0x21);

    LCD_1IN69_SendCommand(0x11);
    DEV_Delay_ms(120);
    LCD_1IN69_SendCommand(0x29);
}
static void LCD_1IN69_SetAttributes(UBYTE Scan_dir)
{
    // Get the screen scan direction
    LCD_1IN69.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    // Get GRAM and LCD width and height
    if (Scan_dir == HORIZONTAL) {
        LCD_1IN69.HEIGHT = LCD_1IN69_WIDTH;
        LCD_1IN69.WIDTH = LCD_1IN69_HEIGHT;
        MemoryAccessReg = 0X70;
    }
    else {
        LCD_1IN69.HEIGHT = LCD_1IN69_HEIGHT;
        LCD_1IN69.WIDTH = LCD_1IN69_WIDTH;
        MemoryAccessReg = 0X00;
    }

    // Set the read / write scan direction of the frame memory
    LCD_1IN69_SendCommand(0x36); // MX, MY, RGB mode
    LCD_1IN69_SendData_8Bit(MemoryAccessReg); // 0x08 set RGB
}
void LCD_1IN69_Init(UBYTE Scan_dir)
{
    // Hardware reset
    LCD_1IN69_Reset();

    // Set the resolution and scanning method of the screen
    LCD_1IN69_SetAttributes(Scan_dir);

    // Set the initialization register
    LCD_1IN69_InitReg();
}
void LCD_1IN69_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    if (LCD_1IN69.SCAN_DIR == VERTICAL) {
        // set the X coordinates
        LCD_1IN69_SendCommand(0x2A);
        LCD_1IN69_SendData_8Bit(Xstart >> 8);
        LCD_1IN69_SendData_8Bit(Xstart);
        LCD_1IN69_SendData_8Bit((Xend-1) >> 8);
        LCD_1IN69_SendData_8Bit(Xend-1);

        // set the Y coordinates
        LCD_1IN69_SendCommand(0x2B);
        LCD_1IN69_SendData_8Bit((Ystart+20) >> 8);
        LCD_1IN69_SendData_8Bit(Ystart+20);
        LCD_1IN69_SendData_8Bit((Yend+20-1) >> 8);
        LCD_1IN69_SendData_8Bit(Yend+20-1);

    }
    else {
        // set the X coordinates
        LCD_1IN69_SendCommand(0x2A);
        LCD_1IN69_SendData_8Bit((Xstart+20) >> 8);
        LCD_1IN69_SendData_8Bit(Xstart+20);
        LCD_1IN69_SendData_8Bit((Xend+20-1) >> 8);
        LCD_1IN69_SendData_8Bit(Xend+20-1);

        // set the Y coordinates
        LCD_1IN69_SendCommand(0x2B);
        LCD_1IN69_SendData_8Bit(Ystart >> 8);
        LCD_1IN69_SendData_8Bit(Ystart);
        LCD_1IN69_SendData_8Bit((Yend-1) >> 8);
        LCD_1IN69_SendData_8Bit(Yend-1);
    }

    LCD_1IN69_SendCommand(0X2C);
}
void LCD_1IN69_Clear(UWORD Color)
{
    UWORD i,j;

    LCD_1IN69_SetWindows(0, 0, LCD_1IN69.WIDTH, LCD_1IN69.HEIGHT);
    DEV_Digital_Write(DEV_DC_PIN, 1);

    for(i = 0; i < LCD_1IN69_WIDTH; i++) {
        for(j = 0; j < LCD_1IN69_HEIGHT; j++) {
            DEV_SPI_Write((Color>>8)&0xff);
            DEV_SPI_Write(Color);
        }
    }
}
void LCD_1IN69_Display(UWORD *Image)
{
    UWORD i,j;

    LCD_1IN69_SetWindows(0, 0, LCD_1IN69.WIDTH, LCD_1IN69.HEIGHT);
    DEV_Digital_Write(DEV_DC_PIN, 1);

    for(i = 0; i < LCD_1IN69_WIDTH; i++) {
        for(j = 0; j < LCD_1IN69_HEIGHT; j++) {
            DEV_SPI_Write((*(Image+i*LCD_1IN69_HEIGHT+j)>>8)&0xff);
            DEV_SPI_Write(*(Image+i*LCD_1IN69_WIDTH+j));
        }
    }

}
void LCD_1IN69_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image)
{
    // display
    UDOUBLE Addr = 0;
    UWORD i,j;

    LCD_1IN69_SetWindows(Xstart, Ystart, Xend , Yend);
    LCD_1IN69_DC_1;

    for (i = Ystart; i < Yend - 1; i++) {
        Addr = Xstart + i * LCD_1IN69_WIDTH ;
        for(j=Xstart;j<Xend-1;j++) {
            DEV_SPI_Write((*(Image+Addr+j)>>8)&0xff);
            DEV_SPI_Write(*(Image+Addr+j));
        }
    }
}

void LCD_1IN69_DrawPoint(UWORD X, UWORD Y, UWORD Color)
{
    LCD_1IN69_SetWindows(X, Y, X, Y);
    LCD_1IN69_SendData_16Bit(Color);
}

void LCD_1IN69_SetBackLight(UWORD Value)
{
    DEV_Set_PWM(Value);
}