#include "String.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "EEPROM_Int.h"
#include "SECURITY_LOGIN_SYSTEM.h"

#define F_CPU 8000000
#include <util/delay.h>

/*  
PWS_Change          ** it will be set to 1 if you request to change password
Correct_Pass        ** it will be set to 1 if the user enter correct password
WrongPass_Counter   ** Counter to count how many times the password has been entered wrong, if It reached the count of 2 the system will lock for 20 seconds
LockFlag            ** it will be set to 1 if user has entered the password 3 times wrong
VFlag               ** flag to write string on LCD just one time
buzzer_C            ** every time the system lock it increase 1 if It reached the count of 2. this mean he is not the owner so the buzzer will turn on util the owner entered the emergency password
buzzer_Flag         ** this flag will be set to 1 if buzzer_C reaches two
Enter_Flag          ** this flag is 0 until the owner enter the right password then will set to 1
*/

/* Note:
If the password has been entered 3 times wrong then the system will lock for 20 seconds then will ask for the password again,
If the password has been entered 3 times wrong for second time the buzzer is on ,red led is on and system will lock until user enter the emergency password
then the password will be default five zeros
*/
   

int main(void)
{

	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	
	u8 key=NO_KEY, PWS_Change=0,r=0,Correct_Pass=0;
	u8 WrongPass_Counter=0;
	u8 LockFlag=0,VFlag=0,buzzer_C=0,Check_Flag=0,buzzer_Flag=0,Enter_Flag=0;
	 
	 
	 /* check if we still use default password or not */
	 First_TimeCheck();
	 index=0;
	 
	while(1)
	{
	   	if(UnFinished_Pass==1)
	   	{
		   	LCD_SetCursor(0,0);
		   	LCD_WriteString("Your last password didn't save");
		   	_delay_ms(1000);
		   	for(index=0;index<PASS_Length;index++)
		   	{
			   	pass[index]=0;
			   	EEPROM_Write(pass[index],address);
			   	address++;
		   	}
		   	UnFinished_Pass=0;
		   	EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
			index=0;
	   	}
	   while(buzzer_Flag==1)
	   {
		   key=KEYPAD_GetKey();
		   if(key>='0' && key<='9')
		   {
			   TempPass[index]=key-'0';
			   LCD_SetCursor(1,index);
			   LCD_WriteNumber(TempPass[index]);
			   _delay_ms(100);
			   LCD_SetCursor(1,index);
			   LCD_WriteChar('*');
			   index++;
			   if(index==PASS_Length)
			   {
				   index=0;
				   r=Compare_pass(TempPass,Emergency_Pass);
				   if(r==1)
				   {
					   address=0;
					   Write_DefaultPassIn_EEPROM();
					   buzzer_Flag=0;
					   Correct_Pass=1;
					   DIO_WritePin(BUZ,LOW);  // Turn off Buzzer
				   }
			   }
		   }
		   
		   
	   }
	   key=KEYPAD_GetKey();
	   if(Enter_Flag==0)
	   {
		   if(VFlag==0)
		   {
			   LCD_Clear();
			   LCD_SetCursor(0,0);
			   LCD_WriteString("Enter the Password");
			   VFlag=1;
		   }
		   if(key>='0' && key<='9')
		   {
			   TempPass[index]=key-'0';
			   LCD_SetCursor(1,index);
			   LCD_WriteNumber(TempPass[index]);
			   _delay_ms(100);
			   LCD_SetCursor(1,index);
			   LCD_WriteChar('*');
			   index++;
			   if(index==PASS_Length)
			   {
				   index=0;
				   r=Compare_pass(TempPass,pass);
				   if(r==1)
				   {
					   Correct_Pass=1;
					   Enter_Flag=1;
				   }
				   
				   else
				   {
					   
					   LCD_Clear();
					   LCD_SetCursor(0,0);
					   LCD_WriteString("wrong pass");
					   _delay_ms(500);
					   WrongPass_Counter++;
					   index=0;
					   VFlag=0;
					   if(WrongPass_Counter==3)
					   {
						   LCD_Clear();
						   LCD_SetCursor(0,0);
						   LCD_WriteString("System is locked for 20 seconds");
						   LockFlag=1;
						   DIO_WritePin(RED_LED,HIGH);  // Turn on Red led
						   _delay_ms(20000);   // (20 seconds)*1000
						   DIO_WritePin(RED_LED,LOW);     // Turn off Red led
						   LCD_Clear();
						   WrongPass_Counter=0;
						   LockFlag=0;
						   buzzer_C++;
						   if(buzzer_C==2)
						   {
							   buzzer_Flag=1;    // thief alarm
							   Enter_Flag=1;
							   buzzer_C=0;
							   DIO_WritePin(BUZ,HIGH);  // Turn on Buzzer
						   }
					   }
					   
				   }
				   
			   }
			   
		   }
	   }
	   if(Correct_Pass==1)
	   {
		   LCD_Clear();
		   LCD_SetCursor(0,0);
		   LCD_WriteString("WELCOME ALI");
		   DIO_WritePin(GRN_LED,HIGH);     // Turn on Green led
		   Correct_Pass=0;
	   }
	   if(key=='c' && Enter_Flag==1)   // && in condition to be ensure he is the owner to change the password
	   {
		   Check_Flag=1;
		   VFlag=0;
		   while(Check_Flag==1)
		   {
			   key=KEYPAD_GetKey();
			   if(VFlag==0)
			   {
				   LCD_Clear();
				   LCD_SetCursor(0,0);
				   LCD_WriteString("Change password");
				   LCD_SetCursor(1,0);
				   LCD_WriteString("1-YES      2-NO");
				   VFlag=1;
			   }
			   if(key>='0' && key<='9')
			   {
				   if(key=='1')
				   {
					   Check_Flag=0;
					   PWS_Change=1;
					   index=0;
					   VFlag=0;
				   }
				   else if (key=='2')
				   {
					   Check_Flag=0;
					   Correct_Pass=1;
				   }
			   }
			   
		   }
		   
		   while(PWS_Change==1)
		   {
			   if(VFlag==0)
			   {
				   LCD_Clear();
				   LCD_SetCursor(0,0);
				   LCD_WriteString("Enter old Pass");
				   VFlag=1;
			   }
			   key=KEYPAD_GetKey();
			   if(key>='0' && key<='9')
			   {
				   if(Correct_Pass==0)
				   {
					   
					   TempPass[index]=key-'0';
					   LCD_SetCursor(1,index);
					   LCD_WriteNumber(TempPass[index]);
					   _delay_ms(100);
					   LCD_SetCursor(1,index);
					   LCD_WriteChar('*');
					   index++;
					   if(index==PASS_Length)
					   {
						   index=0;
						   r=Compare_pass(TempPass,pass);
						   if(r==1)
						   {
							   Correct_Pass=1;
							   key=NO_KEY;
							   LCD_Clear();
							   LCD_SetCursor(0,0);
							   LCD_WriteString("Enter new Pass");
							   UnFinished_Pass=1;    
							   EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
							   
						   }
						   else
						   {
							   LCD_Clear();
							   LCD_SetCursor(0,0);
							   LCD_WriteString("wrong pass");
							   _delay_ms(500);
							   WrongPass_Counter++;
							   VFlag=0;
							   if(WrongPass_Counter==3)
							   {
								   LCD_Clear();
								   LCD_SetCursor(0,0);
								   LCD_WriteString("System is locked for 20 seconds");
								   LockFlag=1;
								   DIO_WritePin(GRN_LED,LOW);   // Turn off Green led
								   DIO_WritePin(RED_LED,HIGH);  // Turn on Red led
								   _delay_ms(20000);            // (20 seconds)*1000
								   DIO_WritePin(RED_LED,LOW);   // Turn off Red led
								   LCD_Clear();
								   LockFlag=0;
								   WrongPass_Counter=0;
								   PWS_Change=0;
								   Enter_Flag=0;
								   buzzer_C++;
								   if(buzzer_C==2)
								   {
									   buzzer_Flag=1;    // thief alarm
									   Enter_Flag=1;
									   buzzer_C=0;
									   DIO_WritePin(BUZ,HIGH);   // Turn on Buzzer
								   }
							   }
							   
							   
						   }
					   }
				   }
				   
				   else if(Correct_Pass==1)
				   {
					   
					   pass[index]=key-'0';
					   LCD_SetCursor(1,index);
					   LCD_WriteNumber(pass[index]);
					   _delay_ms(100);
					   LCD_SetCursor(1,index);
					   LCD_WriteChar('*');
					   index++;
					   if(index==PASS_Length)
					   {
						   index=0;
						   LCD_Clear();
						   Correct_Pass=0;
						   PWS_Change=0;
						   address=0;
						   Write_NewPassIn_EEPROM();
						   UnFinished_Pass=0;
						   EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
						   LCD_Clear();
						   LCD_SetCursor(0,0);
						   LCD_WriteString("DONE");
						   _delay_ms(300);
						   LCD_SetCursor(0,0);
						   LCD_WriteString("WELCOME ALI");
						   DIO_WritePin(GRN_LED,HIGH);    // Turn on Green led
						   
					   }
					      
				   }
				      
			   }	   
			   
		   }
		   
	   }
	   
   }
   
}