

#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_Int.h"

#define  F_CPU   8000000
#include <util/delay.h>

void KEYPAD_Init(void)
{
	u8 i;
	for (i=0;i<ROWS;i++)
	{
		DIO_WritePin(FIRST_OUTPUT+i,HIGH);
	}
	
}

u8 KEYPAD_GetKey(void)
{
	u8 i,j,KEY=NO_KEY;
	for(i=0;i<ROWS;i++)
	{
		DIO_WritePin(FIRST_OUTPUT+i,LOW);
		for(j=0;j<COLS;j++)
		{
		   if (DIO_ReadPin(FIRST_INPUT+j)==LOW)
		   {
			   KEY=KeysArr[i][j];
			   _delay_ms(10);
			   while(DIO_ReadPin(FIRST_INPUT+j)==LOW);
			   _delay_ms(10);
		   }
		}
		DIO_WritePin(FIRST_OUTPUT+i,HIGH);
	}
	return KEY;
}
