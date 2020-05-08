/* ////////////////////////////////////////////////////////////////////////////
/ Author :Eslam Aboutaleb
/
/
/////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "main_SupportFuncs.h"
#include "SW.h"
#include "Display.h"
#include "Time.h"
#include "SSD.h"
#include "Timer_interface.h"


void TIM1_UP_TIM10_IRQHandler (void)
{
	
	  TIM_ClearFlag();
	
	/*Call Task delay routine*/
	  SSD_Update();
    SW_Update();
    TIME_Update();
    DISP_Update();

	
} 

