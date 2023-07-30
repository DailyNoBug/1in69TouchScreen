//
// Created by lsc on 23-7-29.
//
#include "usb_vcom.h"
#include "stdio.h"
#include "usbd_cdc_if.h"
int _write(int fd, char *ptr, int len) {
    CDC_Transmit_FS((uint8_t*)ptr,len);
//    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}