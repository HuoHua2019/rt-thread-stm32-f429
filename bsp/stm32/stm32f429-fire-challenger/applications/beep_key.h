/* 引脚编号，通过查看设备驱动文件drv_gpio.c确定 */
#ifndef BEEP_PIN_NUM
#define BEEP_PIN_NUM            GET_PIN(A,  15)  /* PA15 */
#endif
#ifndef KEY0_PIN_NUM
#define KEY0_PIN_NUM            GET_PIN(D,  2)  /* PD2 */
#endif
#ifndef KEY1_PIN_NUM
#define KEY1_PIN_NUM            GET_PIN(D,  3)  /* PD3 */
#endif
#ifndef LED1_PIN_NUM
#define LED1_PIN_NUM            GET_PIN(C,  2)  /* PC2 */
#endif
#ifndef LED2_PIN_NUM
#define LED2_PIN_NUM            GET_PIN(C,  3)  /* PC3 */
#endif
#ifndef LED3_PIN_NUM
#define LED3_PIN_NUM            GET_PIN(A,  5)  /* PA5 */
#endif
#ifndef LED4_PIN_NUM
#define LED4_PIN_NUM            GET_PIN(A,  6)  /* PA6 */
#endif