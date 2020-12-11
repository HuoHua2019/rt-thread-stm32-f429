/*
 * �����嵥������һ�� PIN �豸ʹ������
 * ���̵����� pin_beep_sample ��������ն�
 * ������ø�ʽ��pin_beep_sample
 * �����ܣ�ͨ���������Ʒ�������Ӧ���ŵĵ�ƽ״̬���Ʒ�����
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <beep_key.h>


void beep_on(void *args)
{
//    rt_kprintf("turn on beep!\n");

    rt_pin_write(BEEP_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED1_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED2_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED3_PIN_NUM, PIN_HIGH);
	  rt_pin_write(LED4_PIN_NUM, PIN_HIGH);	
}

void beep_off(void *args)
{
//    rt_kprintf("turn off beep!\n");

    rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED1_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED2_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED3_PIN_NUM, PIN_LOW);
	  rt_pin_write(LED4_PIN_NUM, PIN_LOW);	
}

static void key_beep_sample(void)
{
    /* ����������Ϊ���ģʽ */
    rt_pin_mode(BEEP_PIN_NUM, PIN_MODE_OUTPUT);
    /* Ĭ�ϵ͵�ƽ */
    rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
	
	  /* LED1����Ϊ���ģʽ */
    rt_pin_mode(LED1_PIN_NUM, PIN_MODE_OUTPUT);
    /* Ĭ�ϵ͵�ƽ */
    rt_pin_write(LED1_PIN_NUM, PIN_LOW);
	  /* LED2����Ϊ���ģʽ */
    rt_pin_mode(LED2_PIN_NUM, PIN_MODE_OUTPUT);
    /* Ĭ�ϵ͵�ƽ */
    rt_pin_write(LED2_PIN_NUM, PIN_LOW);
	  /* LED3����Ϊ���ģʽ */
    rt_pin_mode(LED3_PIN_NUM, PIN_MODE_OUTPUT);
    /* Ĭ�ϵ͵�ƽ */
    rt_pin_write(LED3_PIN_NUM, PIN_LOW);
	  /* LED4����Ϊ���ģʽ */
    rt_pin_mode(LED4_PIN_NUM, PIN_MODE_OUTPUT);
    /* Ĭ�ϵ͵�ƽ */
    rt_pin_write(LED4_PIN_NUM, PIN_LOW);	

    /* ����0����Ϊ����ģʽ */
    rt_pin_mode(KEY0_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    /* ���жϣ��½���ģʽ���ص�������Ϊbeep_on */
    rt_pin_attach_irq(KEY0_PIN_NUM, PIN_IRQ_MODE_FALLING, beep_on, RT_NULL);
    /* ʹ���ж� */
    rt_pin_irq_enable(KEY0_PIN_NUM, PIN_IRQ_ENABLE);

    /* ����1����Ϊ����ģʽ */
    rt_pin_mode(KEY1_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    /* ���жϣ��½���ģʽ���ص�������Ϊbeep_off */
    rt_pin_attach_irq(KEY1_PIN_NUM, PIN_IRQ_MODE_FALLING, beep_off, RT_NULL);
    /* ʹ���ж� */
    rt_pin_irq_enable(KEY1_PIN_NUM, PIN_IRQ_ENABLE);
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(key_beep_sample, pin beep sample);