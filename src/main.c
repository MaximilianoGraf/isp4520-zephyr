
#include <zephyr/device.h>
#include <zephyr/drivers/lora.h>
#include <errno.h>
#include <zephyr/sys/util.h>
#include <zephyr/kernel.h>

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
	     "No default LoRa radio specified in DT");

#define MAX_DATA_LEN 10

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lora_send);

void main(void)
{
	char dataTx[4] = {'P', 'I', 'N', 'G'};
	char dataRx[4];

	const struct device *lora_dev = DEVICE_DT_GET(DEFAULT_RADIO_NODE);
	struct lora_modem_config config;
	int ret;

	if (!device_is_ready(lora_dev)) {
		LOG_ERR("%s Device not ready", lora_dev->name);
		return;
	}

	config.frequency = 868000000;
	config.bandwidth = BW_125_KHZ;
	config.datarate = SF_7;
	config.preamble_len = 8;
	config.coding_rate = CR_4_5;
	config.tx_power = 14;
	config.tx = true;

//  from sx126x.c
//	static const struct lora_driver_api sx126x_lora_api = {
//		.config = sx12xx_lora_config,
//		.send = sx12xx_lora_send,
//		.send_async = sx12xx_lora_send_async,
//		.recv = sx12xx_lora_recv,
//		.recv_async = sx12xx_lora_recv_async,
//		.test_cw = sx12xx_lora_test_cw,
//	};

	ret = lora_config(lora_dev, &config);
	if (ret < 0) {
		LOG_ERR("LoRa config failed");
		return;
	}

	LOG_INF("before while");

	int16_t rssi;
	int8_t snr;
	int len;

	while (1) {
		ret = lora_send(lora_dev, dataTx, 4);
		if (ret < 0) {
			LOG_ERR("LoRa send failed");
			return;
		}

		LOG_INF("Data sent!");

		/* Send data at 1s interval */
		//k_sleep(K_MSEC(1000));

		len = lora_recv(lora_dev, dataRx, 4, K_FOREVER, &rssi, &snr);
		if (len < 0) {
			LOG_ERR("LoRa receive failed");
			return;
		}

		LOG_INF("Received data: %s (RSSI:%ddBm, SNR:%ddBm)",
			dataRx, rssi, snr);
	}
}
