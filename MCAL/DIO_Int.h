
#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "MemMap.h"
#include "StdTypes.h"


 
typedef enum{
	OUTPUT,
	INFREE,
	INPULL
    }DIO_Status_t;

typedef enum{
    PA,
	PB,
	PC,
	PD	
	}DIO_Port_t;
	
typedef enum{
	LOW,
	HIGH
	}DIO_Voltage_t;
	
typedef enum{
	PINA0=0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
	}DIO_Pin_t;	

	
#define RED_LED  PINC0
#define GRN_LED  PINC1
#define BLU_LED  PINC2
#define BUZ      PINC5


void DIO_InitPin(DIO_Pin_t pin,DIO_Status_t status);
void DIO_WritePin(DIO_Pin_t pin,DIO_Voltage_t volt);
DIO_Voltage_t DIO_ReadPin(DIO_Pin_t pin);

void DIO_TogglePin(DIO_Pin_t pin);
void DIO_WritePort(DIO_Port_t port,u8 data);
u8 DIO_ReadPort(DIO_Port_t port);
void DIO_Init(void);

#endif /* DIO_INT_H_ */