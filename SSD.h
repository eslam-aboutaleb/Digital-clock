/* ////////////////////////////////////////////////////////////////////////////
/ Author :Eslam Aboutaleb
/
/
/////////////////////////////////////////////////////////////////////////// */

#ifndef __SDD_H__
#define __SDD_H__

#include "SSD_port.h"

/* Number of SSDs */
#define N_SSD           (4)

#define SSD_TOGGLE_SECONDS()

typedef enum
{
    SSD_MINUTES_UNITS,
    SSD_MINUTES_TENS,
    SSD_HOURS_UNITS,
    SSD_HOURS_TENS
}tSSD;

/* SSD states */
typedef enum
{
    SSD_OFF = 0,
    SSD_ON = 1
}tSSD_State;

/* SSD symbols */
typedef enum
{
    SSD_0 = 0,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
}tSSD_Symbol;

void SSD_Init(tSSD ssd);
void SSD_Update(void);
void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol);
tSSD_Symbol SSD_GetValue(tSSD ssd);
tSSD_State SSD_GetState(tSSD ssd);
void SSD_SetState(tSSD ssd, tSSD_State state);
void SSD_SetDotState(tByte state);


#endif // __SDD_H__
