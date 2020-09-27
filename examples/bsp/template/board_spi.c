/*********************************************************************
 * INCLUDES
 */
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "app_error.h"

#include "board_spi.h"
#include "nordic_common.h"

static void spiCallbackFunc(nrf_drv_spi_evt_t const* pEvent, void* arg);

/*********************************************************************
 * LOCAL VARIABLES
 */
static volatile bool s_transferOk = true;  										// SPI���ݴ�����ɱ�־
static const nrf_drv_spi_t s_spiHandle = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);	// SPI instance

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
 /**
  @brief SPI�ĳ�ʼ������
  @param ��
  @return ��
 */
void SPI_Init(void)
{
	ret_code_t errCode;

	nrf_drv_spi_config_t spiConfig = NRF_DRV_SPI_DEFAULT_CONFIG;			// ʹ��SPIĬ������
	// ����SPI�˿ڣ�ע��CSN��Ҫ�������ã�������GPIO�ڿ���
	spiConfig.miso_pin = BOARD_SPI0_MISO_IO;
	spiConfig.mosi_pin = BOARD_SPI0_MOSI_IO;
	spiConfig.sck_pin = BOARD_SPI0_CLK_IO;
	spiConfig.mode = NRF_DRV_SPI_MODE_0;
	spiConfig.frequency = SPI_FREQUENCY_FREQUENCY_K250;
	spiConfig.irq_priority = 4;													// �ڶ�ʱ����ʹ�����ȼ���С��6

	errCode = nrf_drv_spi_init(&s_spiHandle, &spiConfig, spiCallbackFunc, NULL);
	APP_ERROR_CHECK(errCode);

	nrf_gpio_cfg_output(BOARD_SPI0_CSN_IO);
}

/**
 @brief SPIƬѡ�ź�����
 @param pinState -[in] ����״̬
 @return ��
*/
void SPI_CsnSet(bool pinState)
{
	if (pinState == BOARD_SPI_CS_OFF)
	{
		nrf_gpio_pin_write(BOARD_SPI0_CSN_IO, 1);
	}
	else if (pinState == BOARD_SPI_CS_ON)
	{
		nrf_gpio_pin_write(BOARD_SPI0_CSN_IO, 0);
	}
}

/**
 @brief SPI����д������
 @param pWriteData -[in] д������
 @param pReadData -[out] ��������
 @param writeDataLen -[in] д�����ݳ���
 @return ��
*/
void SPI_ReadWriteData(uint8_t* pWriteData, uint8_t* pReadData, uint8_t writeDataLen)
{
	s_transferOk = false;

	APP_ERROR_CHECK(nrf_drv_spi_transfer(&s_spiHandle, pWriteData, writeDataLen, pReadData, writeDataLen));

	while (!s_transferOk)
	{
		__WFE();
	}																			// Error in SPI or transfer already in progress.
}

/**
 @brief ����SPI�����ʼ������û�г�ʼ��CS����
 @param ��
 @return ��
*/
void SPI_Enable(void)
{
	ret_code_t errCode;

	nrf_drv_spi_config_t spiConfig = NRF_DRV_SPI_DEFAULT_CONFIG;				// ʹ��SPIĬ������
	// ����SPI�˿ڣ�ע��CSN��Ҫ�������ã�������GPIO�ڿ���
	spiConfig.miso_pin = BOARD_SPI0_MISO_IO;
	spiConfig.mosi_pin = BOARD_SPI0_MOSI_IO;
	spiConfig.sck_pin = BOARD_SPI0_CLK_IO;
	spiConfig.mode = NRF_DRV_SPI_MODE_0;
	spiConfig.frequency = SPI_FREQUENCY_FREQUENCY_M8;
	spiConfig.irq_priority = 4;													// �ڶ�ʱ����ʹ�����ȼ���С��6

	errCode = nrf_drv_spi_init(&s_spiHandle, &spiConfig, spiCallbackFunc, NULL);
	APP_ERROR_CHECK(errCode);
}

/**
 @brief ����SPI
 @param ��
 @return ��
*/
void SPI_Disable(void)
{
	nrf_drv_spi_uninit(&s_spiHandle);
}


/*********************************************************************
 * LOCAL FUNCTIONS
 */
 /**
  @brief SPI�жϴ���ص�����
  @param ��
  @return ��
 */
static void spiCallbackFunc(nrf_drv_spi_evt_t const* pEvent, void* arg)
{
	s_transferOk = true;
}

/****************************************************END OF FILE****************************************************/
