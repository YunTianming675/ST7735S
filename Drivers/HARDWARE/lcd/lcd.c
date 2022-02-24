#include "lcd.h"

lcd_dev lcddev;
uint8_t USE_HORIZONTAL = 0;  //�������ã�0,����ģʽ��1,����ģʽ.

/* д��һ���ֽ�
 * ������
 * 	regval��Ҫд�������
 *	mode��0=���1=����
 * ���ܷ�������
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

// ��λ
void LCD_SoftRest()
{
	LCD_WriteByte(0x01, LCD_CMD); // ��λ����
	HAL_Delay(50);
}

/*������ʾ����
 *������
 *	dir=0����������
 *  dir=1����������
 *  dir=2����������
 *  dir=3����������
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
		
		// ����ɨ�跽��
		LCD_WriteByte(0x36, LCD_CMD);
		LCD_WriteByte(0xC8, LCD_DATA);
	}
}

void LCD_Init()
{
	LCD_BLK_ON();
	LCD_SoftRest();
	
	// ֡�ʿ���
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
	
	// �п��ƣ���ת
	LCD_WriteByte(0xB4, LCD_CMD);
	LCD_WriteByte(0x07, LCD_DATA);
	
	// ��Դ����
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
	
	// ����VCOM
	LCD_WriteByte(0xC5, LCD_CMD);
	LCD_WriteByte(0x0E, LCD_DATA);
	
	// ����MX��MY��RGB Mode
	LCD_WriteByte(0x36, LCD_CMD);
	LCD_WriteByte(0xC8, LCD_DATA);
	
	// ����gamma����
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
	
	// ����ʾ
	LCD_WriteByte(0x29, LCD_CMD);
}
