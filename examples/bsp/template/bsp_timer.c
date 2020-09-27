/*********************************************************************
 * INCLUDES
 */
#include "app_timer.h"
#include "bsp_timer.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"





static void timer_testCallback(void *arg);

/*********************************************************************
 * LOCAL VARIABLES
 */
APP_TIMER_DEF(s_testTimer);    // LED��˸���Ķ�ʱ��

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief �������ԵĶ�ʱ��
 @param ��
 @return ��
*/
void CreateTestTimer(void)
{
    app_timer_create(&s_testTimer, APP_TIMER_MODE_REPEATED, timer_testCallback);
}

/**
 @brief �������ԵĶ�ʱ��
 @param ��
 @return ��
*/
void StartTestTimer(void)
{
    app_timer_start(s_testTimer, TEST_PERIOD, NULL);
}

/**
 @brief �رղ��ԵĶ�ʱ��
 @param ��
 @return ��
*/
void StopTestTimer(void)
{
    app_timer_stop(s_testTimer);
}


/*********************************************************************
 * LOCAL FUNCTIONS
 */
/**
 @brief ���Զ�ʱ���Ļص�����
 @param ��
 @return ��
*/
static void timer_testCallback(void *arg)
{
    UNUSED_PARAMETER(arg);
    // ����������Լ���Ӧ�ô���
    NRF_LOG_INFO("Template TIMER_CP.");
		uint8_t temp[1] = {0x01};
		SPI_ReadWriteData(temp, NULL, sizeof(uint8_t));

}
