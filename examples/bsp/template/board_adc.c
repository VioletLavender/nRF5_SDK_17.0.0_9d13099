/*********************************************************************
 * INCLUDES
 */
#include "nrfx_saadc.h"
#include "nrf_drv_saadc.h"
#include "app_error.h" 

#include "board_adc.h"

#include "nrf_log.h"

static void adcCallbackFunc(nrf_drv_saadc_evt_t const* pEvent);

/*********************************************************************
 * LOCAL VARIABLES
 */
static nrf_saadc_value_t s_bufferPool[SAMPLES_IN_BUFFER];

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
 /**
  @brief ADC�ĳ�ʼ������
  @param ��
  @return ��
 */
void ADC_Init(void)
{
	ret_code_t errCode;
	// ADC��ʼ��
	errCode = nrf_drv_saadc_init(NULL, adcCallbackFunc);
	APP_ERROR_CHECK(errCode);
	// ADCͨ������
	nrf_saadc_channel_config_t channelConfig = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);	// ��������
	// ADCͨ����ʼ��
	errCode = nrf_drv_saadc_channel_init(0, &channelConfig);
	APP_ERROR_CHECK(errCode);
	// ��������
	errCode = nrf_drv_saadc_buffer_convert(s_bufferPool, SAMPLES_IN_BUFFER);
	APP_ERROR_CHECK(errCode);
}

/**
 @brief ADC��ȡ
 @param ��
 @return ����ڻص������Ļ�������
*/
void ADC_Read(void)
{
	ret_code_t errCode;
	errCode = nrf_drv_saadc_sample();
	APP_ERROR_CHECK(errCode);
}

/**
 @brief ����ADC�����ʼ��û������Ϊ����Disable�ɶԳ���
 @param ��
 @return ��
*/
void ADC_Enable(void)
{
	ADC_Init();
}

/**
 @brief ����ADC
 @param ��
 @return ��
*/
void ADC_Disable(void)
{
	nrfx_saadc_uninit();
}


/*********************************************************************
 * LOCAL FUNCTIONS
 */
 /**
  @brief ADC�жϴ���ص�����
  @param ��
  @return ��
 */
static void adcCallbackFunc(nrf_drv_saadc_evt_t const* pEvent)
{
	if (pEvent->type == NRF_DRV_SAADC_EVT_DONE)																	// �������
	{
		nrf_saadc_value_t adcResult;
		uint16_t batteryVoltage;
		uint8_t batteryPercentage;
		ret_code_t errCode;

		// ���úû��棬Ϊ�´�ת��������׼�������Ұѵ��뵽�����ֵ��ȡ����
		errCode = nrf_drv_saadc_buffer_convert(pEvent->data.done.p_buffer, SAMPLES_IN_BUFFER);
		APP_ERROR_CHECK(errCode);
		adcResult = pEvent->data.done.p_buffer[0];
		// ��ص�ѹת������
		batteryVoltage = ADC_RESULT_IN_MILLI_VOLTS(adcResult);
	}
}

/****************************************************END OF FILE****************************************************/
