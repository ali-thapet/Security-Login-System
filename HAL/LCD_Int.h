
#ifndef LCD_INT_H_
#define LCD_INT_H_


#define LED_PORT  PORTB

void LCD_Init(void);
void LCD_WriteString(c8*str);
void WriteData(u8 data);
void LCD_WriteNumber8(u8 num);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteBinary2(s32 num);
void LCD_WriteHex(u8 num);
void LCD_WriteHex2(u16 num);
void LCD_WriteHex3(s32 num);
void LCD_CleanCursor(u8 line ,u8 cell,u8 NofCells);
void LCD_WriteStringCursor(u8 line ,u8 cell,c8*str);
void LCD_CustomChar(u8 addres,u8*pattern);
void LCD_Clear(void);
/* line 0:1 cell 0:15*/
void LCD_SetCursor(u8 line ,u8 cell);


/* move on LCD*/



#endif /* LCD_INT_H_ */