/* ////////////////////////////////////////////////////////////////////////////
/ Author  : Eslam Aboutaleb
/
/ Project : Digital Clock
/
/////////////////////////////////////////////////////////////////////////// */

/*Includes*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "main_SupportFuncs.h"
#include "SW.h"
#include "Display.h"
#include "Time.h"
#include "SSD.h"




int main(void)
{
	/*Initialize modulse*/
	  SW_Init();
    DISP_Init();
    TIME_Init();  
	
	/*Initialize timer*/
	  OS_Timer_Init();
	
	while(1)
	{
		              /*Do Nothing*/
		/*should be running as foreground application*/
	}
	
}

