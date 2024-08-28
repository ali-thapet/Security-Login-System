


#ifndef SECURITY_LOGIN_SYSTEM_H_
#define SECURITY_LOGIN_SYSTEM_H_

#define PASS_Length 5
extern volatile u8 index;
extern volatile u16 address;
extern volatile u8 UnFinished_Pass;
extern const u8 UnFinished_Pass_address;
extern const u8 Emergency_Pass[PASS_Length];
extern u8 TempPass[PASS_Length];
extern u8 pass[PASS_Length];

u8 Compare_pass(u8*Pass1,u8*Pass2);
void Write_PassIn_EEPROM (void);
void Write_NewPassIn_EEPROM (void);
void Read_PassFrom_EEPROM (void);
void First_TimeCheck(void);

#endif /* SECURITY_LOGIN_SYSTEM_H_ */