/*
 * KEYPAD_Cfg.h
 *
 * Created: 4/28/2024 2:19:14 PM
 *  Author: Administrator
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_



#define  ROWS  4
#define  COLS  4

#define  FIRST_OUTPUT    PINB4
#define  FIRST_INPUT     PIND2

const  u8 KeysArr[ROWS][COLS];

#endif /* KEYPAD_CFG_H_ */