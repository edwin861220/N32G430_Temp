/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
*\*\file n32g430_it.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/


//#include "bsp.h"
//#include "n32g430.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

#include "n32g430_it.h"

#define ERR_INFO "\r\nEnter HardFault_Handler, System Halt.\r\n"
/** Cortex-M4 Processor Exceptions Handlers **/

/* 声明外部变量供本文件使用 */



/**
*\*\name    NMI_Handler.
*\*\fun     This function handles NMI exception.
*\*\param   none
*\*\return  none
**/
void NMI_Handler(void)
{
}

/**
*\*\name    HardFault_Handler.
*\*\fun     This function handles Hard Fault exception.
*\*\param   none
*\*\return  none
**/
#if 0
void HardFault_Handler(void)
{

#if 0
  const char *pError = ERR_INFO;
  uint8_t i;

  for (i = 0; i < sizeof(ERR_INFO); i++)
  {
     USART1->DAT = pError[i];
     /* 等待发送结束 */
     while ((USART1->STS & USART_FLAG_TXC) == (uint16_t)RESET);
  }
#endif	
	
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}
#else

#define rt_uint32_t unsigned int
#define uint16_t    unsigned short
struct exception_info
{
    rt_uint32_t exc_return;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};

/* check the disassembly instruction is 'BL' or 'BLX' */
static int disassembly_ins_is_bl_blx(rt_uint32_t addr) 
{
    uint16_t ins1 = *((uint16_t *)addr);
    uint16_t ins2 = *((uint16_t *)(addr + 2));

	#define BL_INS_MASK         0xF800
	#define BL_INS_HIGH         0xF800
	#define BL_INS_LOW          0xF000
	#define BLX_INX_MASK        0xFF00
	#define BLX_INX             0x4700

    if ((ins2 & BL_INS_MASK) == BL_INS_HIGH && (ins1 & BL_INS_MASK) == BL_INS_LOW) 
	{
        return 1;
    } 
	else if ((ins2 & BLX_INX_MASK) == BLX_INX) 
	{
        return 1;
    } 
	else 
	{
        return 0;
    }
}

static int is_in_text(unsigned int addr)
{
	extern int * Image$$ER_IROM1$$Base;
	extern int * Image$$ER_IROM1$$Length;

	unsigned int text_start = (unsigned int)&Image$$ER_IROM1$$Base;
	unsigned int text_len = (unsigned int)&Image$$ER_IROM1$$Length;

	if ((addr >= text_start) && (addr < text_start + text_len))
		return 1;
	else
		return 0;
}

/*
 * fault exception handler
 */
void usage_fault_exception(struct exception_info * exception_info)
{
	unsigned int *app_sp;

	int i;
	app_sp = (unsigned int *)(exception_info + 1);  /* context + 16*4 */
	
    printf("psr: 0x%08x\r\n", exception_info->psr);
    printf("r00: 0x%08x\r\n", exception_info->r0);
    printf("r01: 0x%08x\r\n", exception_info->r1);
    printf("r02: 0x%08x\r\n", exception_info->r2);
    printf("r03: 0x%08x\r\n", exception_info->r3);
    printf("r04: 0x%08x\r\n", exception_info->r4);
    printf("r05: 0x%08x\r\n", exception_info->r5);
    printf("r06: 0x%08x\r\n", exception_info->r6);
    printf("r07: 0x%08x\r\n", exception_info->r7);
    printf("r08: 0x%08x\r\n", exception_info->r8);
    printf("r09: 0x%08x\r\n", exception_info->r9);
    printf("r10: 0x%08x\r\n", exception_info->r10);
    printf("r11: 0x%08x\r\n", exception_info->r11);
    printf("r12: 0x%08x\r\n", exception_info->r12);
    printf(" lr: 0x%08x\r\n", exception_info->lr);
    printf(" pc: 0x%08x\r\n", exception_info->pc);




    //while (1);
}


unsigned int svc_exception(struct exception_info * exception_info)
{
	unsigned int addr;
	unsigned short swi_inst;
	unsigned int *old_sp;
	unsigned int val;
	unsigned int new_pos;
	unsigned int offset;
	struct exception_info stack_frame;
	
	/* 取出swi指令 */
	addr = exception_info->pc;
	addr -= 2;

	swi_inst = *((unsigned short *)addr);

    printf("use swi 0x%08x to emulat pop\r\n", swi_inst);

	/* 分析swi指令 */
	old_sp = (unsigned int *)(exception_info + 1);
	
	swi_inst = swi_inst & 0xff;

	/* 模拟swi指令 */
	if (swi_inst == 0xff)
	{
		// pop {pc}
		val = *old_sp;
		old_sp++;
		exception_info->pc = val;
	}
	else
	{
		
		if (swi_inst & (1<<0))
		{
			// pop {r0}
			val = *old_sp;
			old_sp++;
			exception_info->r0 = val;
		}

		if (swi_inst & (1<<1))
		{
			// pop {r1}
			val = *old_sp;
			old_sp++;
			exception_info->r1 = val;
		}

		if (swi_inst & (1<<2))
		{
			// pop {r2}
			val = *old_sp;
			old_sp++;
			exception_info->r2 = val;
		}
		

		if (swi_inst & (1<<3))
		{
			// pop {r3}
			val = *old_sp;
			old_sp++;
			exception_info->r3 = val;
		}

		if (swi_inst & (1<<4))
		{
			// pop {r4}
			val = *old_sp;
			old_sp++;
			exception_info->r4 = val;
		}

		if (swi_inst & (1<<5))
		{
			// pop {r5}
			val = *old_sp;
			old_sp++;
			exception_info->r5 = val;
		}

		if (swi_inst & (1<<6))
		{
			// pop {r6}
			val = *old_sp;
			old_sp++;
			exception_info->r6 = val;
		}

		if (swi_inst & (1<<7))
		{
			// pop {r7}
			val = *old_sp;
			old_sp++;
			exception_info->r7 = val;
		}

		// pop {pc}
		val = *old_sp;
		old_sp++;
		exception_info->pc = val;
		printf("exception_info->pc = 0x%08x\r\n", val);
		
	}

	/* 移动栈帧 */
	stack_frame = *exception_info;

	val = (unsigned int)(exception_info + 1); // old_sp
	new_pos = (unsigned int)old_sp;
	offset = new_pos - val;

	exception_info = (struct exception_info *)((unsigned int)exception_info + offset);
	*exception_info = stack_frame;
	return offset;
	/* 返回 */
}

/*
 * fault exception handler
 */
void rt_hw_hard_fault_exception(struct exception_info * exception_info)
{
	unsigned int *app_sp;
	unsigned int lr;
	unsigned int pc;

	int i;
	app_sp = (unsigned int *)(exception_info + 1);  /* context + 16*4 */
	
    printf("psr: 0x%08x\r\n", exception_info->psr);
    printf("r00: 0x%08x\r\n", exception_info->r0);
    printf("r01: 0x%08x\r\n", exception_info->r1);
    printf("r02: 0x%08x\r\n", exception_info->r2);
    printf("r03: 0x%08x\r\n", exception_info->r3);
    printf("r04: 0x%08x\r\n", exception_info->r4);
    printf("r05: 0x%08x\r\n", exception_info->r5);
    printf("r06: 0x%08x\r\n", exception_info->r6);
    printf("r07: 0x%08x\r\n", exception_info->r7);
    printf("r08: 0x%08x\r\n", exception_info->r8);
    printf("r09: 0x%08x\r\n", exception_info->r9);
    printf("r10: 0x%08x\r\n", exception_info->r10);
    printf("r11: 0x%08x\r\n", exception_info->r11);
    printf("r12: 0x%08x\r\n", exception_info->r12);
    printf(" lr: 0x%08x\r\n", exception_info->lr);
    printf(" pc: 0x%08x\r\n", exception_info->pc);


#if 0
	printf("stacks: \r\n");
#else
	//printf("use the command to get callback: arm-none-eabi-addr2line -e project.axf -a -f ");
	printf("use the command to get callback: addr2line -e project.axf -a -f ");
	printf("%08x ", exception_info->pc);
	printf("%08x ", exception_info->lr);
#endif

//	i = 0;
//	for (i = 0; i < 1024; )
//	{
//#if 0		
//		printf("%08x ", *app_sp);		
//		app_sp++;
//		i++;
//		if (i % 16 == 0)
//			printf("\r\n");
//#else
//		lr = *app_sp;
//		app_sp++;
//		i++;

//		/* lr的bit0必定是1, 表示thumb指令集 
//		 * lr必定处于代码段
//		 */
//		if ((lr & 1) && is_in_text(lr))
//		{
//			/* 返回地址前面必定是BL或BLX指令 */
//			pc = (lr & ~1) - 4;
//			if (disassembly_ins_is_bl_blx(pc))
//			{
//				printf("%08x ", pc);
//			}
//			
//		}
//#endif
//	}
//	printf("\r\n");

    while (1);
}

#endif


/**
*\*\name    MemManage_Handler.
*\*\fun     This function handles Memory Manage exception.
*\*\param   none
*\*\return  none
**/
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
		//printf("MemManage_Handler\r\n");
    }
}

/**
*\*\name    BusFault_Handler.
*\*\fun     This function handles Bus Fault exception.
*\*\param   none
*\*\return  none
**/
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
		//printf("BusFault_Handler\r\n");
    }
}

/**
*\*\name    UsageFault_Handler.
*\*\fun     This function handles Usage Fault exception.
*\*\param   none
*\*\return  none
**/
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
		//printf("UsageFault_Handler\r\n");
    }
}

/**
*\*\name    SVC_Handler.
*\*\fun     This function handles SVCall exception.
*\*\param   none
*\*\return  none
**/
void SVC_Handler(void)
{
}

/**
*\*\name    DebugMon_Handler.
*\*\fun     This function handles Debug Monitor exception.
*\*\param   none
*\*\return  none
**/
void DebugMon_Handler(void)
{
}

/**
*\*\name    SysTick_Handler.
*\*\fun     This function handles SysTick Handler.
*\*\param   none
*\*\return  none
**/
/*void SysTick_Handler(void)
{
}*/



//extern __IO uint8_t g_ucKey1IRQ; 
//void EXTI9_5_IRQHandler(void)
//{
//    if (RESET != EXTI_Interrupt_Status_Get(EXTI_LINE5))
//    {
//		EXTI->EMASK&=~(1<<5);	             /* 关闭中断       */
//        EXTI_Interrupt_Status_Clear(EXTI_LINE5);
//		g_ucKey1IRQ = 5;
////		bsp_LedToggle(0);
//		
//    }	
//}

//void EXTI9_5_IRQHandler(void)
//{
//    if (RESET != EXTI_Interrupt_Status_Get(IO_EXTI_LINE_KEY))
//    {

//        printf("\r\IO_EXTI_LINE_KEY\r\n" ); //
//        //NVIC_SystemReset();
//        if(SystemPara.Eve == EVE_POWDONE)
//        {
//            SystemPara.Eve = EVE_NONE;
//        }
//        SystemPara.KeySet   = 1;

//        Reset_Timer(TIMER_CHARFULL);
//        EXTI_Interrupt_Status_Clear(IO_EXTI_LINE_KEY);

//    }
//    if (RESET != EXTI_Interrupt_Status_Get(IO_EXTI_LINE_CHARFULL))
//    {

//        printf("\r\IO_EXTI_LINE_CHARFULL\r\n" ); //
//// 		NVIC_SystemReset();
////
//        SystemPara.CharStep = 0;
//        if( Timer[KEYTIMER].Enable || Timer[INPIECE_TIMER].Enable)
//        {
//            Reset_Timer(TIMER_CHARFULL);
//        }
//        else
//        {
//            Set_Timer(TIMER_CHARFULL, SetTimer_V(TIMER_BASE_Curr,60000,0));
//        }

//        EXTI_Interrupt_Status_Clear(IO_EXTI_LINE_CHARFULL);
//        EXTI_Initialize(IO_EXTI_LINE_CHARFULL, EXTI_Trigger_Falling,DISABLE);
//        NVIC_Initialize(IO_IRQn_CHARFULL,DISABLE);

//    }

//}

//void EXTI0_IRQHandler(void)
//{
//    if (RESET != EXTI_Interrupt_Status_Get(IO_EXTI_LINE_VI))
//    {
//        GPIO_Pins_Set(ISN_PORT, ISN_PIN );
// 
//		printf("\r\nISN_PORT\r\n" ); //
//        SystemPara.WorkMod = WK_CHARG;Reset_Timer(START_TIMER);
// 		LCD_BLK_Set();
////		NVIC_SystemReset();
// 
//        EXTI_Interrupt_Status_Clear(IO_EXTI_LINE_VI);
//    }
//}
//void EXTI15_10_IRQHandler(void)
//{
// 
//    if (RESET != EXTI_Interrupt_Status_Get(IO_EXTI_LINE_WIRELESS))
//    {
//        printf("\r\IO_EXTI_LINE_WIRELESS\r\n" ); //
//        SystemPara.WorkMod = WK_CHARG;Reset_Timer(START_TIMER);
// 
//// 			StopWork(0);
// 		LCD_BLK_Set();
////	     NVIC_SystemReset();
//		 
//        EXTI_Interrupt_Status_Clear(IO_EXTI_LINE_WIRELESS);
//		
//    }
//	
//}


