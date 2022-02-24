#include "lcd.h"

lcd_dev lcddev;
uint8_t USE_HORIZONTAL = 0;  //方向设置：0,竖屏模式；1,横屏模式.

/* 写入一个字节
 * 参数：
 * 	regval：要写入的数据
 *	mode：0=命令，1=数据
 * 可能发生错误
**/ 
void LCD_WriteByte(uint8_t data, uint8_t mode)
{
	uint8_t i;
	
	LCD_CS_RESET();
	
	if(mode)
		LCD_RS_SET();
	else
		LCD_RST_RESET();
	
	for(i = 0; i < 8; i++)
	{
		LCD_SCL_RESET();
		if(data & 0x80)
			LCD_SDA_SET();
		else
			LCD_SDA_RESET();
		LCD_SCL_SET();
		data <<= 1;
	}
	
	LCD_CS_SET();
}

// 软复位
void LCD_SoftRest()
{
	LCD_WriteByte(0x01, LCD_CMD); // 复位命令
	HAL_Delay(50);
}

/*设置显示方向
 *参数：
 *	dir=0：竖屏，正
 *  dir=1：竖屏，反
 *  dir=2：横屏，正
 *  dir=3：横屏，反
**/
void LCD_DisplayDir(uint8_t dir)
{
	if(dir == 0)
	{
		lcddev.direction = 0;
		lcddev.width = LCD_XWidth;
		lcddev.height = LCD_YWidth;
		lcddev.wramcmd = 0x2C;
		lcddev.setxcmd = 0x2A;
		lcddev.setycmd = 0x2B;
		
		// 设置扫描方向
		LCD_WriteByte(0x36, LCD_CMD);
		LCD_WriteByte(0xC8, LCD_DATA);
	}
}

void LCD_Init()
{
	LCD_BLK_ON();
	LCD_SoftRest();
	
	// 帧率控制
	LCD_WriteByte(0xB1, LCD_CMD);
	LCD_WriteByte(0x01, LCD_DATA);
	LCD_WriteByte(0x2C, LCD_DATA);
	LCD_WriteByte(0x2D, LCD_DATA);
	
	LCD_WriteByte(0xB2, LCD_CMD);
	LCD_WriteByte(0x01, LCD_DATA);
	LCD_WriteByte(0x2C, LCD_DATA);
	LCD_WriteByte(0x2D, LCD_DATA);
	
	LCD_WriteByte(0xB3, LCD_CMD);
	LCD_WriteByte(0x01, LCD_DATA);
	LCD_WriteByte(0x2C, LCD_DATA);
	LCD_WriteByte(0x2D, LCD_DATA);
	LCD_WriteByte(0x01, LCD_DATA);
	LCD_WriteByte(0x2C, LCD_DATA);
	LCD_WriteByte(0x2D, LCD_DATA);
	
	// 列控制：反转
	LCD_WriteByte(0xB4, LCD_CMD);
	LCD_WriteByte(0x07, LCD_DATA);
	
	// 电源控制
	LCD_WriteByte(0xC0, LCD_CMD);
	LCD_WriteByte(0xA2, LCD_DATA);
	LCD_WriteByte(0x02, LCD_DATA);
	LCD_WriteByte(0x84, LCD_DATA);
	LCD_WriteByte(0xC1, LCD_CMD);
	LCD_WriteByte(0xC5, LCD_DATA);
	
	LCD_WriteByte(0xC2, LCD_CMD);
	LCD_WriteByte(0x0A, LCD_DATA);
	LCD_WriteByte(0x00, LCD_DATA);
	
	LCD_WriteByte(0xC3, LCD_CMD);
	LCD_WriteByte(0x8A, LCD_DATA);
	LCD_WriteByte(0x2A, LCD_DATA);
	LCD_WriteByte(0xC4, LCD_CMD);
	LCD_WriteByte(0x8A, LCD_DATA);
	LCD_WriteByte(0xEE, LCD_DATA);
	
	// 设置VCOM
	LCD_WriteByte(0xC5, LCD_CMD);
	LCD_WriteByte(0x0E, LCD_DATA);
	
	// 设置MX、MY、RGB Mode
	LCD_WriteByte(0x36, LCD_CMD);
	LCD_WriteByte(0xC8, LCD_DATA);
	
	// 设置gamma序列
	LCD_WriteByte(0xe0, LCD_CMD);
    LCD_WriteByte(0x0f, LCD_DATA);
    LCD_WriteByte(0x1a, LCD_DATA);
    LCD_WriteByte(0x0f, LCD_DATA);
    LCD_WriteByte(0x18, LCD_DATA);
    LCD_WriteByte(0x2f, LCD_DATA);
    LCD_WriteByte(0x28, LCD_DATA);
    LCD_WriteByte(0x20, LCD_DATA);
    LCD_WriteByte(0x22, LCD_DATA);
    LCD_WriteByte(0x1f, LCD_DATA);
    LCD_WriteByte(0x1b, LCD_DATA);
    LCD_WriteByte(0x23, LCD_DATA);
    LCD_WriteByte(0x37, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x07, LCD_DATA);
    LCD_WriteByte(0x02, LCD_DATA);
    LCD_WriteByte(0x10, LCD_DATA);
	
	LCD_WriteByte(0xe1, LCD_CMD);
    LCD_WriteByte(0x0f, LCD_DATA);
    LCD_WriteByte(0x1b, LCD_DATA);
    LCD_WriteByte(0x0f, LCD_DATA);
    LCD_WriteByte(0x17, LCD_DATA);
    LCD_WriteByte(0x33, LCD_DATA);
    LCD_WriteByte(0x2c, LCD_DATA);
    LCD_WriteByte(0x29, LCD_DATA);
    LCD_WriteByte(0x2e, LCD_DATA);
    LCD_WriteByte(0x30, LCD_DATA);
    LCD_WriteByte(0x30, LCD_DATA);
    LCD_WriteByte(0x39, LCD_DATA);
    LCD_WriteByte(0x3f, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x07, LCD_DATA);
    LCD_WriteByte(0x03, LCD_DATA);
    LCD_WriteByte(0x10, LCD_DATA);
	
	LCD_WriteByte(0x2A, LCD_CMD);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x7F, LCD_DATA);
	
	LCD_WriteByte(0x2B, LCD_CMD);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x00, LCD_DATA);
    LCD_WriteByte(0x9F, LCD_DATA);
	
	LCD_WriteByte(0xF0, LCD_CMD);
    LCD_WriteByte(0x01, LCD_DATA);
	LCD_WriteByte(0xF6, LCD_CMD);
    LCD_WriteByte(0x00, LCD_DATA);
	
	LCD_WriteByte(0x3A, LCD_CMD);
    LCD_WriteByte(0x05, LCD_DATA);
	
	// 开显示
	LCD_WriteByte(0x29, LCD_CMD);
}
