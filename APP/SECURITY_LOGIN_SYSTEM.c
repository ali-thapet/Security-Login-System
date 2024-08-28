#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "EEPROM_Int.h"
#include "LCD_Int.h"
#include "SECURITY_LOGIN_SYSTEM.h"

#define F_CPU 8000000
#include <util/delay.h>

u8 TempPass[PASS_Length];
u8 pass[PASS_Length];                                 // main password array it will be five zeros as default until the user change it 
const u8 Emergency_Pass[PASS_Length]={1,2,3,4,5};     // Emergency password it must be enter if buzzer is on and the system has been locked 1,can't be change
volatile u8 index;                                    // array index
volatile u16 address;                                 // address of data in EEPROM (0 to 1023)
volatile u8 UnFinished_Pass;                          // Variable normal value is 0 and while changing the password it set to 1 so if the power is turned off while changing a message will appear when the power return again
const u8 UnFinished_Pass_address=6;                   // address of UnFinished_Pass variable in EEPROM
static u8 First_Time;                                 // To now if it is the first time for MCU to work or not
static const u8 FirstTime_address=5;                  // address of First_Time variable in EEPROM



u8 Compare_pass(u8*Pass1,u8*Pass2)
{
	u8 x;
	for(x=0;x<PASS_Length;x++)
	{
		if(Pass1[x]!=Pass2[x])
		{
			return 0;
		}
	}
	return 1;
}



void First_TimeCheck(void)
{
	/* 
		 Password address from 0 -> 4 
		 assign pass as default first time we use micro-controller
	*/
	 First_Time=EEPROM_Read(FirstTime_address);
	 if(First_Time!=0)
	 {
		 Write_DefaultPassIn_EEPROM();
		 First_Time=0;
		 EEPROM_Write(First_Time,FirstTime_address);
		 UnFinished_Pass=0;
		 EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
	 }
	 if(First_Time==0)
	 {
		 Read_PassFrom_EEPROM();
		 UnFinished_Pass=EEPROM_Read(UnFinished_Pass_address);
	 }
}


void Write_DefaultPassIn_EEPROM (void)
{
	/* Password address from 0 -> 4 */
	for(index=0;index<PASS_Length;index++)
	{
		pass[index]=0;
		EEPROM_Write(pass[index],address);
		address++;
	}
}

void Write_NewPassIn_EEPROM (void)
{
	/* Password address from 0 -> 4 */
	for(index=0;index<PASS_Length;index++)
	{
		EEPROM_Write(pass[index],address);
		address++;
	}
}


void Read_PassFrom_EEPROM (void)
{
	/* Password address from 0 -> 4 */
	for(index=0;index<PASS_Length;index++)
	{
		pass[index]=EEPROM_Read(address);
		address++;
	}
	
}




 