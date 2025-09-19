/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.2
*	说    明 : 按键检测和LED控制例程。核心文件为 bsp_timer.c bsp_key.c 和 bsp_led.c
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2013-02-01 armfly  首发
*		v1.1    2013-06-20 armfly  更新bsp代码; 更新打印提示信息。
*		V1.2    2014-02-28 armfly  升级固件库到V1.3.0
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/


#include "n32g430.h"
#include <stdio.h>
#include "main.h"
#include "bsp_BitBand.h"


/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME	"V5-004a_USART实验_printf功能"
#define EXAMPLE_DATE	"2015-03-23"
#define DEMO_VER		"1.1"

#define SOFTWARE_VERSION   "1.1.26B"

static void PrintfLogo(void);
static void PrintfHelp(void);

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{

    while(1)
    {

    }
}

/*
*********************************************************************************************************
*	函 数 名: PrintfHelp
*	功能说明: 打印操作提示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
    printf("操作提示:\r\n");
    printf("1. 串口命令1，非法读取异常\r\n");
    printf("2. 串口命令2，字节对齐异常\r\n");
    printf("3. 串口命令3，非法写入异常\r\n");
    printf("4. 串口命令4，非常函数异常\r\n");
    printf("5. 串口命令5，除以0的问题\r\n");
}
/*
*********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
    /* 检测CPU UID */
    {
        /* 参考手册：
        	32.6.1 MCU device ID code
        	33.1 Unique device ID register (96 bits)
        */
        //printf("\n\r");
        printf("*************************************************************\n\r");
        uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;

        CPU_Sn0 = *(__IO uint32_t*)(0x1FFFF7F0);
        CPU_Sn1 = *(__IO uint32_t*)(0x1FFFF7F0 + 4);
        CPU_Sn2 = *(__IO uint32_t*)(0x1FFFF7F0 + 8);

        printf("\r\nUUID = %08X %08X %08X\n\r"
               , CPU_Sn2, CPU_Sn1, CPU_Sn0);
        //printf("\n\r");
        //printf("*************************************************************\n\r");
    }
    /* 检测CPU UCID */
    {
        /* 参考手册：
        	32.6.1 MCU device ID code
        	33.1 Unique device ID register (96 bits)
        */
        //printf("\n\r");
        //printf("*************************************************************\n\r");
        uint32_t UCID_Sn0, UCID_Sn1, UCID_Sn2, UCID_Sn3;

        UCID_Sn0 = *(__IO uint32_t*)(0x1FFFF7C0);
        UCID_Sn1 = *(__IO uint32_t*)(0x1FFFF7C0 + 4);
        UCID_Sn2 = *(__IO uint32_t*)(0x1FFFF7C0 + 8);
        UCID_Sn3 = *(__IO uint32_t*)(0x1FFFF7C0 + 12);
        printf("\r\nUCID = %08X %08X %08X %08X\n\r"
               , UCID_Sn3, UCID_Sn2, UCID_Sn1, UCID_Sn0);
        //printf("\n\r");
        //printf("*************************************************************\n\r");
    }
    //printf("\n\r");
    printf("*************************************************************\n\r");
    printf("* 例程名称   : %s\r\n", EXAMPLE_NAME);	/* 打印例程名称 */
    printf("* 例程版本   : %s\r\n", DEMO_VER);		/* 打印例程版本 */
    printf("* 发布日期   : %s\r\n", EXAMPLE_DATE);	/* 打印例程日期 */

    /* 打印ST固件库版本，这3个定义宏在stm32f10x.h文件中 */
//	printf("* 固件库版本 : V%d.%d.%d (STM32F4xx_StdPeriph_Driver)\r\n", __STM32F4XX_STDPERIPH_VERSION_MAIN,
//			__STM32F4XX_STDPERIPH_VERSION_SUB1,__STM32F4XX_STDPERIPH_VERSION_SUB2);
//	printf("* \r\n");	/* 打印一行空格 */
    printf("* QQ    : 429730679 \r\n");
    printf("* Copyright 深圳市柏瑞纳科技有限公司\r\n");
    printf("*************************************************************\n\r");
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
