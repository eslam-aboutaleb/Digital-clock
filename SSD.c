/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: SSD.c
//////////////////////////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Timer_interface.h"
#include "SSD.h"

/* SSD_Update period */
#define SSD_PERIOD_MS   (5)

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (11)


/* SSD Symbols port data values */
static tByte SSD_Data[N_SSD_SYMBOLS] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000,
};

/* Current SSD to be updated */
static tSSD SSD_current = SSD_MINUTES_UNITS;

/* SSD values */
static tSSD_Symbol SSD_Values[N_SSD] = {SSD_NULL};

static tByte SSD_DotState = SSD_OFF;

static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol);

void SSD_Init(tSSD ssd)
{
    /* Initialize SSD data pins */
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_1,GPIO_OUT);
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_2,GPIO_OUT);
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_3,GPIO_OUT);
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_4,GPIO_OUT);
    GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_5,GPIO_OUT);
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_6,GPIO_OUT);
    GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_7,GPIO_OUT);
	  GPIO_InitPortPin(SSD_DATA_PORT_CR,SSD_PIN_8,GPIO_OUT);
    
    SSD_Out(ssd, SSD_NULL);

    /* Initialize SSD control pin and turn SSD OFF*/
    switch (ssd)
    {
        case SSD_MINUTES_UNITS:
            GPIO_InitPortPin(SSD_MINUTES_UNITS_CR, SSD_MINUTES_UNITS_PIN, GPIO_OUT);
            break;
        case SSD_MINUTES_TENS:
            GPIO_InitPortPin(SSD_MINUTES_TENS_CR, SSD_MINUTES_TENS_PIN, GPIO_OUT);
            break;
        case SSD_HOURS_UNITS:
            GPIO_InitPortPin(SSD_HOURS_UNITS_CR, SSD_HOURS_UNITS_PIN, GPIO_OUT);
            break;
        case SSD_HOURS_TENS:
            GPIO_InitPortPin(SSD_HOURS_TENS_CR, SSD_HOURS_TENS_PIN, GPIO_OUT);
            break;
        /* Should not be here */
        default:
            break;
    }
    SSD_SetState(ssd, SSD_OFF);
}

void SSD_Update(void)
{
    static tWord SSD_counter = 0;

    /* Check if it is time for the SSD_Update to run */
    SSD_counter += TMR_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS){
        return;
    }

    SSD_counter = 0;

    /* display current SSD value of the current SSD */
    SSD_Out(SSD_current, SSD_Values[SSD_current]);

    if (SSD_current == SSD_HOURS_TENS)
    {
        SSD_current = SSD_MINUTES_UNITS;
    } else
    {
        SSD_current++;
    }
}

tSSD_Symbol SSD_GetValue(tSSD ssd)
{
    return SSD_Values[ssd];
}

void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    SSD_Values[ssd] = ssd_symbol;
}

tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;
    switch (ssd)
    {
        case SSD_MINUTES_UNITS:
            ret = GPIO_ReadPortPin(SSD_MINUTES_UNITS_DR, SSD_MINUTES_UNITS_PIN);
            break;
        case SSD_MINUTES_TENS:
            ret = GPIO_ReadPortPin(SSD_MINUTES_TENS_DR, SSD_MINUTES_TENS_PIN);
            break;
        case SSD_HOURS_UNITS:
            ret = GPIO_ReadPortPin(SSD_HOURS_UNITS_DR, SSD_HOURS_UNITS_PIN);
            break;
        case SSD_HOURS_TENS:
            ret = GPIO_ReadPortPin(SSD_HOURS_TENS_DR, SSD_HOURS_TENS_PIN);
            break;
        default:
            break;
    }
     return ret;

}

void SSD_SetState(tSSD ssd, tSSD_State state)
{
    switch (ssd)
    {
        case SSD_MINUTES_UNITS:
            GPIO_WritePortPin(SSD_MINUTES_UNITS_DR, SSD_MINUTES_UNITS_PIN, state);
            break;
        case SSD_MINUTES_TENS:
            GPIO_WritePortPin(SSD_MINUTES_TENS_DR, SSD_MINUTES_TENS_PIN, state);
            break;
        case SSD_HOURS_UNITS:
            GPIO_WritePortPin(SSD_HOURS_UNITS_DR, SSD_HOURS_UNITS_PIN, state);
            GPIO_WritePortPin(SSD_DATA_PORT_DR, GPIO_PIN_7, SSD_DotState);
            break;
        case SSD_HOURS_TENS:
            GPIO_WritePortPin(SSD_HOURS_TENS_DR, SSD_HOURS_TENS_PIN, state);
            break;
        /* Should not be here */
        default:
            break;
    }
}


void SSD_SetDotState(tByte state)
{
    SSD_DotState = state;
}

static  void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    /* Turn off SSDs */
    SSD_SetState(SSD_MINUTES_UNITS, SSD_OFF);
    SSD_SetState(SSD_MINUTES_TENS, SSD_OFF);
    SSD_SetState(SSD_HOURS_UNITS, SSD_OFF);
    SSD_SetState(SSD_HOURS_TENS, SSD_OFF);

    /* Output ssd_symbol on selected ssd */
    GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],0));
   	GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],1));
	  GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],2));
	  GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],3));
	  GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],4));
   	GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],5));
	  GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],6));
	  GPIO_WritePortPin(SSD_DATA_PORT_DR,SSD_PIN_1,GET_BIT(SSD_Data[ssd_symbol],7));



    /* Turn ssd ON */
    SSD_SetState(ssd, SSD_ON);


}
