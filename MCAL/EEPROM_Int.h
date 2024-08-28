


#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

#include "StdTypes.h"


void EEPROM_Write(u8 data,u16 address);
u8 EEPROM_Read(u16 address);
void EEPROM_InterruptEnable(void);
void EEPROM_InterruptDisable(void);
void EEPROM_SetCallback(void (*localFptr)(void));


#endif /* EEPROM_INT_H_ */