/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: Time.c
//////////////////////////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_interface.h"
#include "SW.h"
#include "Time.h"

#define TIME_PERIOD_MS   (20)
#define TIME_SECOND_MS (1000)

static void TIME_UpdateTime(void);

static tTIME_Time TIME_CurrentTime = {0, 0, 0};

static tTIME_State TIME_State = TIME_NORMAL;

void TIME_Init(void)
{
    TIME_CurrentTime.seconds = 0;
    TIME_CurrentTime.minutes = 0;
    TIME_CurrentTime.hours = 0;

}
void TIME_Update(void)
{
    static tWord TIME_counter = 0;
    static tWord TIME_seconds_counter = 0;


    /* Check if it is time for the DISP_Update to run */
    TIME_counter += TMR_TICK_MS;

    if (TIME_counter != TIME_PERIOD_MS){
        return;
    }
    TIME_counter = 0;

    switch (TIME_State)
    {
        case TIME_NORMAL:

            if (SW_GetState(SW_SET) == SW_PRE_PRESSED)
            {
                TIME_State = TIME_SET_HOURS;
                TIME_seconds_counter = 0;
            }
            else
            {
                TIME_seconds_counter += TIME_PERIOD_MS;
                if (TIME_seconds_counter == TIME_SECOND_MS)
                {
                    TIME_seconds_counter = 0;
                    TIME_UpdateTime();
                }

            }

            break;
        case TIME_SET_HOURS:
            if (SW_GetState(SW_SET) == SW_PRE_PRESSED)
            {
                TIME_State = TIME_SET_MINUTES;
                TIME_seconds_counter = 0;
            } else if (SW_GetState(SW_PLUS) == SW_PRE_PRESSED)
            {
                TIME_CurrentTime.hours ++;
                if (TIME_CurrentTime.hours == 24)
                {
                    TIME_CurrentTime.hours = 0;
                }

            } else if (SW_GetState(SW_MINUS) == SW_PRE_PRESSED)
            {
                TIME_CurrentTime.hours --;
                if (TIME_CurrentTime.hours == 255)
                {
                    TIME_CurrentTime.hours = 23;
                }
            } else
            {
                /* Do nothing */
            }
            break;
        case TIME_SET_MINUTES:
            if (SW_GetState(SW_SET) == SW_PRE_PRESSED)
            {
                TIME_State = TIME_NORMAL;
                TIME_seconds_counter = 0;
            } else if (SW_GetState(SW_PLUS) == SW_PRE_PRESSED)
            {
                TIME_CurrentTime.minutes ++;
                if (TIME_CurrentTime.minutes == 60)
                {
                    TIME_CurrentTime.minutes = 0;
                }

            } else if (SW_GetState(SW_MINUS) == SW_PRE_PRESSED)
            {
                TIME_CurrentTime.minutes --;
                if (TIME_CurrentTime.minutes == 255)
                {
                    TIME_CurrentTime.minutes = 59;
                }
            } else
            {
                /* Do nothing */
            }
            break;
    }
}
void TIME_GetTime(tTIME_Time * time)
{
    time->seconds = TIME_CurrentTime.seconds;
    time->minutes = TIME_CurrentTime.minutes;
    time->hours = TIME_CurrentTime.hours;

}

tByte TIME_CompareTime(tTIME_Time * first, tTIME_Time * second)
{
    tByte ret = 1;
    if (/*(first -> seconds == second->seconds) &&*/
        (first -> minutes == second->minutes) &&
        (first -> hours == second->hours))
    {
        ret = 0;
    }
    return ret;
}

tTIME_State TIME_GetState(void)
{
    return TIME_State;
}

void TIME_CopyTime(tTIME_Time * dest, tTIME_Time * src)
{
    dest -> seconds = src->seconds;
    dest -> minutes = src->minutes;
    dest -> hours = src->hours;
}

static void TIME_UpdateTime(void)
{
    TIME_CurrentTime.seconds ++;
    if (TIME_CurrentTime.seconds == 60)
    {
        TIME_CurrentTime.seconds = 0;
        TIME_CurrentTime.minutes++;
        if (TIME_CurrentTime.minutes == 60)
        {
            TIME_CurrentTime.minutes = 0;
            TIME_CurrentTime.hours++;
            if (TIME_CurrentTime.hours == 24)
            {
                TIME_CurrentTime.hours = 0;
            }
        }
    }
}
