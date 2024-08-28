

#define  F_CPU   8000000
#include <util/delay.h>
#include "StdTypes.h"

#include "DIO_Int.h"
#include "String.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"



#if LCD_MODE==_8_BIT
void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);
	WriteIns(0x0c);//0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}
#elif LCD_MODE==_4_BIT

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5,GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,GET_BIT(data,7));
	DIO_WritePin(D6,GET_BIT(data,6));
	DIO_WritePin(D5,GET_BIT(data,5));
	DIO_WritePin(D4,GET_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,GET_BIT(data,3));
	DIO_WritePin(D6,GET_BIT(data,2));
	DIO_WritePin(D5,GET_BIT(data,1));
	DIO_WritePin(D4,GET_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c);//0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif



void LCD_WriteString(c8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteNumber(s32 num)
{ 
	c8 str[10]={0},i;
	if(num==0)
	{
		LCD_WriteChar('0');
	}
    NUM_tostring(str,num);
	for (i=0;i<str[i];i++)
	{
		WriteData(str[i]);
	}
}

void LCD_WriteNumber8(u8 num)
{
	c8 str[3]={0},i;
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	NUM_tostring(str,num);
	for (i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}


void LCD_WriteBinary(u8 num)
{ 
  s8 i;
  LCD_WriteString("0b");
  for(i=7;i>=0;i--)
  {
	    WriteData(GET_BIT(num,i)+'0');
  }
}

void LCD_WriteBinary2(s32 num)
{
	s8 i;
	LCD_WriteString("0b");
	for(i=31;i>=0;i--)
	{
		WriteData(GET_BIT(num,i)+'0');
	}	
}


void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	LCD_WriteString("0x");
	if(HN<10)
	{
	    LCD_WriteChar(HN+'0');
	}
	if(HN>10)
	{
		LCD_WriteChar(HN+'A'-10);
	}
	if(LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	if(LN>10)
	{
		LCD_WriteChar(LN+'A'-10);
	}
	
}

void LCD_WriteHex2(u16 num)
{
	u8 FHN=num>>12;
	u8 FLN=(num>>8)&0x0f;
	
	u8 SHN=(num&0x00f0)>>4;
	u8 SLN=num&0x000f;
	
	LCD_WriteString("0x");
	if(FHN<10)
	{
		LCD_WriteChar(FHN+'0');
	}
	if(FHN>10)
	{
		LCD_WriteChar(FHN+'A'-10);
	}
	if(FLN<10)
	{
		LCD_WriteChar(FLN+'0');
	}
	if(FLN>10)
	{
		LCD_WriteChar(FLN+'A'-10);
	}
	if(SHN<10)
	{
		LCD_WriteChar(SHN+'0');
	}
	if(SHN>10)
	{
		LCD_WriteChar(SHN+'A'-10);
	}
	if(SLN<10)
	{
		LCD_WriteChar(SLN+'0');
	}
	if(SLN>10)
	{
		LCD_WriteChar(SLN+'A'-10);
	}
	
}


void LCD_WriteHex3(s32 num)
{
	u8 HN1=num>>28;
	u8 LN1=(num>>24)&0x0f;
	
	u8 HN2=(num>>20)&0x00f;
	u8 LN2=(num>>16)&0x000f;
	
	u8 HN3=(num>>12)&0x0000f;
	u8 LN3=(num>>8)&0x00000f;
	
	u8 HN4=(num>>4)&0x000000f;
	u8 LN4=num&0x0000000f;
	
	LCD_WriteString("0x");
	if(HN1<10)
	{
		LCD_WriteChar(HN1+'0');
	}
	if(HN1>10)
	{
		LCD_WriteChar(HN1+'A'-10);
	}
	if(LN1<10)
	{
		LCD_WriteChar(LN1+'0');
	}
	if(LN1>10)
	{
		LCD_WriteChar(LN1+'A'-10);
	}
	if(HN2<10)
	{
		LCD_WriteChar(HN2+'0');
	}
	if(HN2>10)
	{
		LCD_WriteChar(HN2+'A'-10);
	}
	if(LN2<10)
	{
		LCD_WriteChar(LN2+'0');
	}
	if(LN2>10)
	{
		LCD_WriteChar(LN2+'A'-10);
	}
	if(HN3<10)
	{
		LCD_WriteChar(HN3+'0');
	}
	if(HN3>10)
	{
		LCD_WriteChar(HN3+'A'-10);
	}
	if(LN3<10)
	{
		LCD_WriteChar(LN3+'0');
	}
	if(LN3>10)
	{
		LCD_WriteChar(LN3+'A'-10);
	}
	if(HN4<10)
	{
		LCD_WriteChar(HN4+'0');
	}
	if(HN4>10)
	{
		LCD_WriteChar(HN4+'A'-10);
	}
	if(LN4<10)
	{
		LCD_WriteChar(LN4+'0');
	}
	if(LN4>10)
	{
		LCD_WriteChar(LN4+'A'-10);
	}
	
}





/* line 0:1 cell 0:15*/
void LCD_SetCursor(u8 line ,u8 cell)
{
  if (line==0)
  {
    WriteIns(cell|0x80);
  }
  if(line==1)
  {
	  WriteIns((cell+0x40)|0x80);
  }
	
}

void LCD_WriteStringCursor(u8 line ,u8 cell,c8*str)
{
	
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
	
}

void LCD_CleanCursor(u8 line ,u8 cell,u8 NofCells)
{
	u8 i;
	LCD_SetCursor(line,cell);
	for(i=0;i<NofCells;i++)
	{
		LCD_WriteChar(' ');
	}
}


void LCD_CustomChar(u8 addres,u8*pattern)
{
	u8 i;
	WriteIns(0x40|addres);
	for(i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}

void LCD_Clear(void)
{
	WriteIns(0x01);//clear screen
	_delay_ms(1);
}