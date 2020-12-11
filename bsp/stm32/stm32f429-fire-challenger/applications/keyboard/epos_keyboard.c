/**
 * @File:    demo_rtt_iotboard.c
 * @Author:  MurphyZhao
 * @Date:    2018-09-29
 * 
 * Copyright (c) 2018-2019 MurphyZhao <d2014zjt@163.com>
 *               https://github.com/murphyzhao
 * All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * message:
 * This demo is base on rt-thread IoT Board, reference
 *     https://github.com/RT-Thread/IoT_Board
 * Hardware version: RT-Thread IoT Board Pandora v2.51.
 * 
 * Change logs:
 * Date        Author       Notes
 * 2018-09-29  MurphyZhao   First add
 * 2019-08-02  MurphyZhao   Migrate code to github.com/murphyzhao account
 * 2020-02-14  MurphyZhao   Fix grammar bug
*/

#include <rtthread.h>
#include <board.h>
#include <beep_key.h>
#include "flexible_button.h"

#ifndef PIN_BEEP
#define PIN_BEEP GET_PIN(A,  15)  /* PA15 */
#endif

#ifndef PIN_KEY_S2
#define PIN_KEY_S2 GET_PIN(D, 3)
#endif

#ifndef PIN_KEY_S3
#define PIN_KEY_S3 GET_PIN(D, 2)
#endif

#ifndef PIN_ROW4
#define PIN_ROW4 GET_PIN(C, 9)
#endif

#ifndef PIN_ROW3
#define PIN_ROW3 GET_PIN(C, 8)
#endif

#ifndef PIN_ROW2
#define PIN_ROW2 GET_PIN(C, 7)
#endif

#ifndef PIN_ROW1
#define PIN_ROW1 GET_PIN(C, 6)
#endif

#ifndef PIN_COL5
#define PIN_COL5 GET_PIN(D, 15)
#endif

#ifndef PIN_COL4
#define PIN_COL4 GET_PIN(D, 14)
#endif

#ifndef PIN_COL3
#define PIN_COL3 GET_PIN(D, 13)
#endif

#ifndef PIN_COL2
#define PIN_COL2 GET_PIN(D, 12)
#endif

#ifndef PIN_COL1
#define PIN_COL1 GET_PIN(D, 11)
#endif

#define ENUM_TO_STR(e) (#e)

typedef enum
{
    USER_BUTTON_1 = 0,
    USER_BUTTON_2,
    USER_BUTTON_3,
    USER_BUTTON_AMOUNT,
    USER_BUTTON_4,
    USER_BUTTON_5,
    USER_BUTTON_6,
    USER_BUTTON_VOLUME,
    USER_BUTTON_7,	
    USER_BUTTON_8,
    USER_BUTTON_9,
    USER_BUTTON_EJECT,
    USER_BUTTON_DOT,
    USER_BUTTON_0,
    USER_BUTTON_OK,
    USER_BUTTON_CHANGE,
    USER_BUTTON_SET,
    USER_BUTTON_UP,
    USER_BUTTON_DOWN,
    USER_BUTTON_SELECT,
    USER_BUTTON_S2,
    USER_BUTTON_S3,		
    USER_BUTTON_MAX
} user_button_t;

static char *enum_event_string[] = {
    ENUM_TO_STR(FLEX_BTN_PRESS_DOWN),
    ENUM_TO_STR(FLEX_BTN_PRESS_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_DOUBLE_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_REPEAT_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_MAX),
    ENUM_TO_STR(FLEX_BTN_PRESS_NONE),
};

static char *enum_btn_id_string[] = {
    ENUM_TO_STR(USER_BUTTON_1),
    ENUM_TO_STR(USER_BUTTON_2),
    ENUM_TO_STR(USER_BUTTON_3),
    ENUM_TO_STR(USER_BUTTON_AMOUNT),
    ENUM_TO_STR(USER_BUTTON_4),
    ENUM_TO_STR(USER_BUTTON_5),
    ENUM_TO_STR(USER_BUTTON_6),
    ENUM_TO_STR(USER_BUTTON_VOLUME),
    ENUM_TO_STR(USER_BUTTON_7),
    ENUM_TO_STR(USER_BUTTON_8),
    ENUM_TO_STR(USER_BUTTON_9),
    ENUM_TO_STR(USER_BUTTON_EJECT),
    ENUM_TO_STR(USER_BUTTON_DOT),
    ENUM_TO_STR(USER_BUTTON_0),
    ENUM_TO_STR(USER_BUTTON_OK),
    ENUM_TO_STR(USER_BUTTON_CHANGE),
    ENUM_TO_STR(USER_BUTTON_SET),
    ENUM_TO_STR(USER_BUTTON_UP),
    ENUM_TO_STR(USER_BUTTON_DOWN),
    ENUM_TO_STR(USER_BUTTON_SELECT),
    ENUM_TO_STR(USER_BUTTON_S2),
    ENUM_TO_STR(USER_BUTTON_S3),		
    ENUM_TO_STR(USER_BUTTON_MAX),
};

static flex_button_t user_button[USER_BUTTON_MAX];

static uint8_t common_btn_read(void *arg)
{
    uint8_t value = 0;

    flex_button_t *btn = (flex_button_t *)arg;
	
		rt_pin_write(PIN_ROW1,PIN_HIGH);
		rt_pin_write(PIN_ROW2,PIN_HIGH);
		rt_pin_write(PIN_ROW3,PIN_HIGH);
		rt_pin_write(PIN_ROW4,PIN_HIGH);	

    switch (btn->id)
    {
    case USER_BUTTON_S2:
        value = rt_pin_read(PIN_KEY_S2);
        break;
    case USER_BUTTON_S3:
        value = rt_pin_read(PIN_KEY_S3);
        break;
		
    case USER_BUTTON_SELECT:
				rt_pin_write(PIN_ROW1,PIN_LOW);				
        value = rt_pin_read(PIN_COL5);
        break;
    case USER_BUTTON_DOWN:
				rt_pin_write(PIN_ROW2,PIN_LOW);				
        value = rt_pin_read(PIN_COL5);
        break;
    case USER_BUTTON_UP:
				rt_pin_write(PIN_ROW3,PIN_LOW);				
        value = rt_pin_read(PIN_COL5);
        break;
    case USER_BUTTON_SET:
				rt_pin_write(PIN_ROW4,PIN_LOW);				
        value = rt_pin_read(PIN_COL5);
        break;		
		
    case USER_BUTTON_CHANGE:
				rt_pin_write(PIN_ROW1,PIN_LOW);				
        value = rt_pin_read(PIN_COL4);
        break;
    case USER_BUTTON_OK:
				rt_pin_write(PIN_ROW2,PIN_LOW);				
        value = rt_pin_read(PIN_COL4);
        break;
    case USER_BUTTON_0:
				rt_pin_write(PIN_ROW3,PIN_LOW);				
        value = rt_pin_read(PIN_COL4);
        break;
    case USER_BUTTON_DOT:
				rt_pin_write(PIN_ROW4,PIN_LOW);				
        value = rt_pin_read(PIN_COL4);
        break;		
		
    case USER_BUTTON_EJECT:
				rt_pin_write(PIN_ROW1,PIN_LOW);				
        value = rt_pin_read(PIN_COL3);
        break;
    case USER_BUTTON_9:
				rt_pin_write(PIN_ROW2,PIN_LOW);				
        value = rt_pin_read(PIN_COL3);
        break;
    case USER_BUTTON_8:
				rt_pin_write(PIN_ROW3,PIN_LOW);				
        value = rt_pin_read(PIN_COL3);
        break;
    case USER_BUTTON_7:
				rt_pin_write(PIN_ROW4,PIN_LOW);				
        value = rt_pin_read(PIN_COL3);
        break;		

    case USER_BUTTON_VOLUME:
				rt_pin_write(PIN_ROW1,PIN_LOW);				
        value = rt_pin_read(PIN_COL2);
        break;
    case USER_BUTTON_6:
				rt_pin_write(PIN_ROW2,PIN_LOW);				
        value = rt_pin_read(PIN_COL2);
        break;
    case USER_BUTTON_5:
				rt_pin_write(PIN_ROW3,PIN_LOW);				
        value = rt_pin_read(PIN_COL2);
        break;
    case USER_BUTTON_4:
				rt_pin_write(PIN_ROW4,PIN_LOW);				
        value = rt_pin_read(PIN_COL2);
        break;		

    case USER_BUTTON_AMOUNT:
				rt_pin_write(PIN_ROW1,PIN_LOW);				
        value = rt_pin_read(PIN_COL1);
        break;
    case USER_BUTTON_3:
				rt_pin_write(PIN_ROW2,PIN_LOW);				
        value = rt_pin_read(PIN_COL1);
        break;
    case USER_BUTTON_2:
				rt_pin_write(PIN_ROW3,PIN_LOW);				
        value = rt_pin_read(PIN_COL1);
        break;
    case USER_BUTTON_1:
				rt_pin_write(PIN_ROW4,PIN_LOW);				
        value = rt_pin_read(PIN_COL1);
        break;				
		
    default:
        RT_ASSERT(0);
    }

    return value;
}

void beep__on()
{
//    rt_kprintf("turn on beep!\n");

    rt_pin_write(PIN_BEEP, PIN_HIGH);
}

void beep__off()
{
//    rt_kprintf("turn off beep!\n");

    rt_pin_write(PIN_BEEP, PIN_LOW);
}

static void common_btn_evt_cb(void *arg)
{
    flex_button_t *btn = (flex_button_t *)arg;
		unsigned int n;
		rt_pin_mode(LED1_PIN_NUM, PIN_MODE_OUTPUT);
    /* ????? */
    rt_pin_write(LED1_PIN_NUM, PIN_LOW);
	  /* LED2??????? */
    rt_pin_mode(LED2_PIN_NUM, PIN_MODE_OUTPUT);
    /* ????? */
    rt_pin_write(LED2_PIN_NUM, PIN_LOW);
	  /* LED3??????? */
    rt_pin_mode(LED3_PIN_NUM, PIN_MODE_OUTPUT);
    /* ????? */
    rt_pin_write(LED3_PIN_NUM, PIN_LOW);
	  /* LED4??????? */
    rt_pin_mode(LED4_PIN_NUM, PIN_MODE_OUTPUT);
    /* ????? */
    rt_pin_write(LED4_PIN_NUM, PIN_LOW);	

		if (btn->event == FLEX_BTN_PRESS_CLICK)
		{
			rt_kprintf("id: [%d - %s]  event: [%d - %30s]  repeat: %d\n", 
					btn->id, enum_btn_id_string[btn->id],
					btn->event, enum_event_string[btn->event],
					btn->click_cnt);
			n = btn->id;
//    if ((flex_button_event_read(&user_button[USER_BUTTON_0]) == FLEX_BTN_PRESS_CLICK) &&\
//        (flex_button_event_read(&user_button[USER_BUTTON_1]) == FLEX_BTN_PRESS_CLICK))
//    {
//        rt_kprintf("[combination]: button 0 and button 1\n");
//    }
			beep__on();
			rt_thread_mdelay(20); // 20 ms
			beep__off();
			if(n==1)
			{
					
				rt_pin_write(LED1_PIN_NUM, PIN_HIGH);
				rt_thread_mdelay(20); // 20 ms
				rt_pin_write(LED1_PIN_NUM, PIN_LOW);
			}
			else if(n==0)
			{
				rt_pin_write(LED2_PIN_NUM, PIN_HIGH);
				rt_thread_mdelay(20); // 20 ms
				rt_pin_write(LED2_PIN_NUM, PIN_LOW);
			}
			else if(n==2)
			{
					rt_pin_write(LED3_PIN_NUM, PIN_HIGH);
				rt_thread_mdelay(20); // 20 ms
				rt_pin_write(LED3_PIN_NUM, PIN_LOW);
			}
			else if(n==4)
			{
					rt_pin_write(LED4_PIN_NUM, PIN_HIGH);
				rt_thread_mdelay(20); // 20 ms
				rt_pin_write(LED4_PIN_NUM, PIN_LOW);
			}
			else
			{
				rt_pin_write(LED1_PIN_NUM, PIN_HIGH);	
				rt_pin_write(LED2_PIN_NUM, PIN_HIGH);
				rt_pin_write(LED3_PIN_NUM, PIN_HIGH);				
				rt_pin_write(LED4_PIN_NUM, PIN_HIGH);
				rt_thread_mdelay(20); // 20 ms
				rt_pin_write(LED2_PIN_NUM, PIN_LOW);
				rt_pin_write(LED1_PIN_NUM, PIN_LOW);
				rt_pin_write(LED3_PIN_NUM, PIN_LOW);				
				rt_pin_write(LED4_PIN_NUM, PIN_LOW);
			}
		}
}

static void button_scan(void *arg)
{
    while(1)
    {
        flex_button_scan();
        rt_thread_mdelay(20); // 20 ms
    }
}

static void user_button_init(void)
{
    int i;
    
    rt_memset(&user_button[0], 0x0, sizeof(user_button));

    rt_pin_mode(PIN_KEY_S2, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_KEY_S3, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_COL1, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_COL2, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_COL3, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_COL4, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */
    rt_pin_mode(PIN_COL5, PIN_MODE_INPUT_PULLUP); /* set KEY pin mode to input */	
    rt_pin_mode(PIN_ROW1, PIN_MODE_OUTPUT); /* set KEY pin mode to output */
    rt_pin_mode(PIN_ROW2, PIN_MODE_OUTPUT); /* set KEY pin mode to output */
    rt_pin_mode(PIN_ROW3, PIN_MODE_OUTPUT); /* set KEY pin mode to output */
    rt_pin_mode(PIN_ROW4, PIN_MODE_OUTPUT); /* set KEY pin mode to output */	

    for (i = 0; i < USER_BUTTON_MAX; i ++)
    {
        user_button[i].id = i;
        user_button[i].usr_button_read = common_btn_read;
        user_button[i].cb = common_btn_evt_cb;
        user_button[i].pressed_logic_level = 0;
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(3000);
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(4500);

//        if (i == USER_BUTTON_3)
//        {
//            user_button[USER_BUTTON_3].pressed_logic_level = 1;
//        }

        flex_button_register(&user_button[i]);
    }
}

int flex_button_main(void)
{
    rt_thread_t tid = RT_NULL;
    /* ?????????? */
    rt_pin_mode(PIN_BEEP, PIN_MODE_OUTPUT);
    /* ????? */
    beep__off();
	
    user_button_init();

    /* Create background ticks thread */
    tid = rt_thread_create("flex_btn", button_scan, RT_NULL, 1024, 10, 10);
    if(tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

    return 0;
}
#ifdef FINSH_USING_MSH
INIT_APP_EXPORT(flex_button_main);
#endif