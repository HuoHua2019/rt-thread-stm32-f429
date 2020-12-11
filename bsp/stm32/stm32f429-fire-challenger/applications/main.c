/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f429-fire-challenger bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <beep_key.h>

/* defined the LED0 pin: PH10 */
#define LED0_PIN    GET_PIN(C, 2)
#ifndef BEEP_PIN_NUM
#define BEEP_PIN_NUM            GET_PIN(A,  15)  /* PA15 */
#endif

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
	/* 蜂鸣器引脚为输出模式 */
    rt_pin_mode(BEEP_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(BEEP_PIN_NUM, PIN_LOW);

//    while (count<10)
//    {
//        rt_pin_write(LED0_PIN, PIN_HIGH);
//        rt_thread_mdelay(1500);
//			  rt_kprintf("led on\n");
//        rt_pin_write(LED0_PIN, PIN_LOW);
//        rt_thread_mdelay(1500);
//			  rt_kprintf("led off\n");
//			  count++;
//    }
		/* 蜂鸣器引脚为输出模式 */
    rt_pin_mode(BEEP_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
	
	  /* LED1引脚为输出模式 */
    rt_pin_mode(LED1_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(LED1_PIN_NUM, PIN_LOW);
	  /* LED2引脚为输出模式 */
    rt_pin_mode(LED2_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(LED2_PIN_NUM, PIN_LOW);
	  /* LED3引脚为输出模式 */
    rt_pin_mode(LED3_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(LED3_PIN_NUM, PIN_LOW);
	  /* LED4引脚为输出模式 */
    rt_pin_mode(LED4_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认低电平 */
    rt_pin_write(LED4_PIN_NUM, PIN_LOW);	
    rt_pin_write(BEEP_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED1_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED2_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED3_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED4_PIN_NUM, PIN_HIGH);	
		rt_thread_mdelay(200);
		rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED1_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED2_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED3_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED4_PIN_NUM, PIN_LOW);
    return RT_EOK;
}

//#define SAMPLE_UART_NAME       "uart2"    

static rt_device_t serial;
