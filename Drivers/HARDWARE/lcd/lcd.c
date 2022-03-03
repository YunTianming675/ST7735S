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

/*д�������ֽ�
 *��д���ֽڣ���д���ֽ�
**/
void LCD_Write2Byte(uint16_t data, uint8_t mode)
{
	LCD_WriteByte(data >> 8, mode);
	LCD_WriteByte(data, mode);
}

/*������ʾ���ڴ�С
 *
**/
void LCD_SetWindow(uint8_t sx, uint8_t sy, uint16_t width, uint16_t height)
{
	width = sx + width - 1;
    height = sy + height - 1;
    if(USE_HORIZONTAL == 0)
    {

        LCD_WriteByte(lcddev.setxcmd, LCD_CMD);
        LCD_Write2Byte(sx + 2, LCD_DATA);    //���� X�������
        LCD_Write2Byte(width + 2, LCD_DATA); //���� X�����յ�

        LCD_WriteByte(lcddev.setycmd, LCD_CMD);
        LCD_Write2Byte(sy + 3, LCD_DATA);    //���� Y�������
        LCD_Write2Byte(height + 3, LCD_DATA); //���� Y�����յ�

    }
    else
    {
        LCD_WriteByte(lcddev.setxcmd, LCD_CMD);
        LCD_Write2Byte(sx + 3, LCD_DATA);    //���� X�������
        LCD_Write2Byte(width + 3, LCD_DATA); //���� X�����յ�

        LCD_WriteByte(lcddev.setycmd, LCD_CMD);
        LCD_Write2Byte(sy + 2, LCD_DATA);    //���� Y�������
        LCD_Write2Byte(height + 2, LCD_DATA); //���� Y�����յ�
    }
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
		
		USE_HORIZONTAL = 0;
	}
	else if(dir == 1)
	{
		lcddev.direction = 0;
		lcddev.width = LCD_XWidth;
		lcddev.height = LCD_YWidth;
		lcddev.wramcmd = 0x2C;
		lcddev.setxcmd = 0x2A;
		lcddev.setycmd = 0x2B;
		
		// ����ɨ�跽��
		LCD_WriteByte(0x36, LCD_CMD);
		LCD_WriteByte(0x48, LCD_DATA);
		
		USE_HORIZONTAL = 0;
	}
	else if(dir == 2)
	{
		lcddev.direction = 1;
		lcddev.width = LCD_YWidth;
		lcddev.height = LCD_XWidth;
		lcddev.wramcmd = 0x2C;
		lcddev.setxcmd = 0x2A;
		lcddev.setycmd = 0x2B;
		
		// ����ɨ�跽��
		LCD_WriteByte(0x36, LCD_CMD);
		LCD_WriteByte(0xA8, LCD_DATA);
		
		USE_HORIZONTAL = 1;
	}
	else if(dir == 3)
	{
		lcddev.direction = 1;
		lcddev.width = LCD_YWidth;
		lcddev.height = LCD_XWidth;
		lcddev.wramcmd = 0x2C;
		lcddev.setxcmd = 0x2A;
		lcddev.setycmd = 0x2B;
		
		// ����ɨ�跽��
		LCD_WriteByte(0x36, LCD_CMD);
		LCD_WriteByte(0x68, LCD_DATA);
		
		USE_HORIZONTAL = 1;
	}
	// ����Ĭ�ϴ���
	else
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
		
		USE_HORIZONTAL = 0;
	}
	LCD_SetWindow(0, 0, lcddev.width, lcddev.height);
}

/*ȫ������
 *������
 *	color�����������ɫ
**/
void LCD_Clear(uint16_t color)
{
	
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
	LCD_BLK_ON();
}
