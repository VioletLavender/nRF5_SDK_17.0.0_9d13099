/*********************************************************************
 * INCLUDES
 */
#include "nrf_gpio.h"
#include "nordic_common.h"
#include "bsp_led.h"

 /*********************************************************************
  * PUBLIC FUNCTIONS
  */
  /**
   @brief ������������ʼ��
   @param ��
   @return ��
  */
void Board_LED0Init(void)
{
    nrf_gpio_cfg_output(BSP_LED0_IO);
    nrf_gpio_pin_write(BSP_LED0_IO, 0);
}

/**
 @brief ���÷���������ģʽ
 @param beepMode -[in] ����ģʽ
 @return ��
*/
void Board_LED0Set(uint8_t LED0Mode)
{
    switch (LED0Mode)                                                        // ִ��ģʽ
    {
    case BSP_LED0_OFF:                                                          // ����������ģʽ
        nrf_gpio_pin_write(BSP_LED0_IO, 0);
        break;

    case BSP_LED0_ON:                                                           // ��������ģʽ
        nrf_gpio_pin_write(BSP_LED0_IO, 1);
        break;

    default:
        break;
    }
}

/**
 @brief LED��������ʼ��
 @param ��
 @return ��
*/
void Board_LedInit(void)
{
    nrf_gpio_cfg_output(BSP_LED1_IO);
    nrf_gpio_pin_write(BSP_LED1_IO, 1);
}

/**
 @brief ����LED�ƹ���ģʽ
 @param ledMode -[in] ����ģʽ
 @return ��
*/
void Board_LedSet(uint8_t ledMode)
{
    switch (ledMode)                                                         // ִ��ģʽ
    {
    case BSP_LED1_OFF:                                                           // LED��ģʽ
        nrf_gpio_pin_write(BSP_LED1_IO, 0);
        break;

    case BSP_LED1_ON:                                                            // LED��ģʽ
        nrf_gpio_pin_write(BSP_LED1_IO, 1);
        break;

    default:
        break;
    }
}

/****************************************************END OF FILE****************************************************/
