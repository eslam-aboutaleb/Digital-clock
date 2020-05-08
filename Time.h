/* ////////////////////////////////////////////////////////////////////////////
/ Author :Eslam Aboutaleb
/
/
/////////////////////////////////////////////////////////////////////////// */

#ifndef __TIME_H__
#define __TIME_H__


typedef struct
{
    tByte seconds;
    tByte minutes;
    tByte hours;
}tTIME_Time;

typedef enum
{
    TIME_NORMAL = 0,
    TIME_SET_HOURS,
    TIME_SET_MINUTES
}tTIME_State;

void TIME_Init(void);
void TIME_Update(void);
void TIME_GetTime(tTIME_Time * time);
tByte TIME_CompareTime(tTIME_Time * first, tTIME_Time * second);
tTIME_State TIME_GetState(void);
void TIME_CopyTime(tTIME_Time * dest, tTIME_Time * src);


#endif
