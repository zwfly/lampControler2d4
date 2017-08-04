#ifndef _BSP_H_
#define _BSP_H

#include <stdio.h>
#include <N76E003.h>
#include "Version.h"
#include "Function_Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"

#include "bsp_bt.h"
#include "bsp_uart.h"
#include "bsp_timer0.h"
#include "bsp_timer1.h"


#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void bsp_Init(void);


#endif

/***************************** (END OF FILE) *********************************/
