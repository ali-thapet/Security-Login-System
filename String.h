

#ifndef STRING_H_
#define STRING_H_

#include "StdTypes.h"

void Remove_string(c8*str);
u8 string_length(c8 *str);
void string_reverse(c8 *str);
u8 string_compare(u8*str1,u8*str2);
void NUM_tostring(c8 *str,s32 num);



#endif /* STRING_H_ */