
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "DIO_Private.h"


 void DIO_InitPin(DIO_Pin_t pin,DIO_Status_t status)
{
	u8 pin_num=pin%8;
  	if(status==OUTPUT)
	  {
		   if(pin>=0 && pin<=7)
		   {
			   SET_BIT(DDRA,pin_num);
			   CLR_BIT(PORTA,pin_num);
		   }
		   if(pin>=8 && pin<=15)
		   {
			 
			   SET_BIT(DDRB,pin_num);
			   CLR_BIT(PORTB,pin_num);
		   }
		   if(pin>=16 && pin<=23)
		   {
			
			   SET_BIT(DDRC,pin_num);
			   CLR_BIT(PORTC,pin_num);
		   }
		   if(pin>=24 && pin<=31)
		   {
			 
			   SET_BIT(DDRD,pin_num);
			   CLR_BIT(PORTD,pin_num);
		   }
	  }
	  if(status==INFREE)
	  {
		   if(pin>=0 && pin<=7)
		   {
			   CLR_BIT(DDRA,pin_num);
			   CLR_BIT(PORTA,pin_num);
		   }
		   if(pin>=8 && pin<=15)
		   {
			   
			   CLR_BIT(DDRB,pin_num);
			   CLR_BIT(PORTB,pin_num);
		   }
		   if(pin>=16 && pin<=23)
		   {
			 
			   CLR_BIT(DDRC,pin_num);
			   CLR_BIT(PORTC,pin_num);
		   }
		   if(pin>=24 && pin<=31)
		   {
			 
			   CLR_BIT(DDRD,pin_num);
			   CLR_BIT(PORTD,pin_num);
		   }
	  }
	if(status==INPULL)
	  {   
		   if(pin>=0 && pin<=7)
		   {
			   CLR_BIT(DDRA,pin_num);
			   SET_BIT(PORTA,pin_num);
		   }
		   if(pin>=8 && pin<=15)
		   {
			   CLR_BIT(DDRB,pin_num);
			   SET_BIT(PORTB,pin_num);
		   }
		   if(pin>=16 && pin<=23)
		   {
			   CLR_BIT(DDRC,pin_num);
			   SET_BIT(PORTC,pin_num);
		   }
		   if(pin>=24 && pin<=31)
		   {  
			   CLR_BIT(DDRD,pin_num);
			   SET_BIT(PORTD,pin_num);
		   }
	 }
}

void DIO_WritePin(DIO_Pin_t pin,DIO_Voltage_t volt)
{
   u8 pin_num=pin%8;
	if(volt==LOW)
	{
		 if(pin>=0 && pin<=7)
		 {
		   CLR_BIT(PORTA,pin_num);	 
		 }
		 if(pin>=8 && pin<=15)
		 {
			 CLR_BIT(PORTB,pin_num);
		 }
		 if(pin>=16 && pin<=23)
		 {
			 CLR_BIT(PORTC,pin_num);
		 }
		 if(pin>=24 && pin<=31)
		 {
			 CLR_BIT(PORTD,pin_num);
		 }
	}
	if(volt==HIGH)
	{
		 if(pin>=0 && pin<=7)
		 {
			 SET_BIT(PORTA,pin_num);
		 }
		 if(pin>=8 && pin<=15)
		 {
			 SET_BIT(PORTB,pin_num);
		 }
		 if(pin>=16 && pin<=23)
		 {
			 SET_BIT(PORTC,pin_num);
		 }
		 if(pin>=24 && pin<=31)
		 {
			 SET_BIT(PORTD,pin_num);
		 }
	}
}


DIO_Voltage_t DIO_ReadPin(DIO_Pin_t pin)
{
	DIO_Voltage_t volt=LOW;
	u8 pin_num=pin%8;
	 if(pin>=0 && pin<=7)
	 {
		volt=GET_BIT(PINA,pin_num);
	 }
	 if(pin>=8 && pin<=15)
	 {
		volt=GET_BIT(PINB,pin_num);
	 }
	 if(pin>=16 && pin<=23)
	 {
		volt=GET_BIT(PINC,pin_num);
	 }
	 if(pin>=24 && pin<=31)
	 {
		volt=GET_BIT(PIND,pin_num);
	 }
	 return volt;
}

void DIO_TogglePin(DIO_Pin_t pin)
{
	    u8 pin_num=pin%8;
		if(pin>=0 && pin<=7)
		{
			TOG_BIT(PORTA,pin_num);
		}
		if(pin>=8 && pin<=15)
		{
			TOG_BIT(PORTB,pin_num);
		}
		if(pin>=16 && pin<=23)
		{
			TOG_BIT(PORTC,pin_num);
		}
		if(pin>=24 && pin<=31)
		{
			TOG_BIT(PORTD,pin_num);
		}
}

void DIO_WritePort(DIO_Port_t port,u8 data)
{
	if(port==PA)
	{
		PORTA=data;
	}
	if(port==PB)
	{
		PORTB=data;
	}
	if(port==PC)
	{
		PORTC=data;
	}
	if(port==PD)
	{
		PORTD=data;
	}
}
u8 DIO_ReadPort(DIO_Port_t port)
{
	u8 data=LOW;
	if(port==PA)
	{
		data=PORTA;
	}
	if(port==PB)
	{
		data=PORTB;
	}
	if(port==PC)
	{
		data=PORTC;
	}
	if(port==PD)
	{
		data=PORTD;
	}
	return data;
}


void DIO_Init(void)
{
	DIO_Pin_t i;
	for (i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinStatusArr[i]);
	}
}