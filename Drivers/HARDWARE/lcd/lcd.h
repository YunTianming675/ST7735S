#ifndef __ST7735S_H
#define __ST7735S_H

#include "stm32f1xx_hal.h"

// RS=0:命令模式
#define LCD_SDA_SET()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET)
#define LCD_SDA_RESET()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET)

#define LCD_SCL_SET()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
#define LCD_SCL_RESET()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)

#define LCD_CS_SET()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define LCD_CS_RESET()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)

#define LCD_RST_SET()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)
#define LCD_RST_RESET()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)

#define LCD_RS_SET()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define LCD_RS_RESET()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

// 背光控制
#define LCD_BLK_ON()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define LCD_BLK_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)

#define LCD_CMD  0
#define LCD_DATA 1

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint16_t id;
	uint8_t  direction;
	uint16_t wramcmd;    // 写gram指令
	uint16_t setxcmd;    // 设置x坐标指令
	uint16_t setycmd;    // 设置y坐标指令
}lcd_dev;

#define LCD_DirModeVertical 0

#define LCD_XWidth          128 // X方向长度
#define LCD_YWidth          128 // Y方向长度

extern lcd_dev lcddev;

#endif
