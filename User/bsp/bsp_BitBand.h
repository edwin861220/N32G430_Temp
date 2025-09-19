#ifndef _N3G430_BITBAND_H_
#define _N3G430_BITBAND_H_
#include "n32g430.h"

/** 位带操作 */
// 根据公式将位带区寄存器转换成对应的位带别名区的地址
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 

// 将地址转换成指针的形式，方便赋值
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))

// 封装好要操作的寄存器地址和比特位
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

/** 列出各个GPIO口的输入输出寄存器地址映射 */ 
// 输出
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x4001140C 
  

// 输入
#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40011408 

 

/** 
  * IO口操作，只对单一的IO口
  * 注意：确保n的值在0~16区间，分别对应PIN脚
  */
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入

#endif
