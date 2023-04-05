/*
 * Copyright (c) 2019 Manivannan Sadhasivam
 *
 * SPDX-License-Identifier: Apache-2.0
 * lora_receiver
 */

// #include <zephyr/device.h>
// #include <zephyr/drivers/lora.h>
// #include <errno.h>
// #include <zephyr/sys/util.h>
// #include <zephyr/zephyr.h>

// #define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
// BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
// 	     "No default LoRa radio specified in DT");

// #define MAX_DATA_LEN 255

// #define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
// #include <zephyr/logging/log.h>
// LOG_MODULE_REGISTER(lora_receive);

// void lora_receive_cb(const struct device *dev, uint8_t *data, uint16_t size,
// 		     int16_t rssi, int8_t snr)
// {
// 	static int cnt;

// 	ARG_UNUSED(dev);
// 	ARG_UNUSED(size);

// 	LOG_INF("Received data: %s (RSSI:%ddBm, SNR:%ddBm)",
// 		data, rssi, snr);

// 	/* Stop receiving after 10 packets */
// 	if (++cnt == 10) {
// 		LOG_INF("Stopping packet receptions");
// 		lora_recv_async(dev, NULL);
// 	}
// }

// void main(void)
// {
// 	const struct device *lora_dev = DEVICE_DT_GET(DEFAULT_RADIO_NODE);
// 	struct lora_modem_config config;
// 	int ret, len;
// 	uint8_t data[MAX_DATA_LEN] = {0};
// 	int16_t rssi;
// 	int8_t snr;

// 	if (!device_is_ready(lora_dev)) {
// 		LOG_ERR("%s Device not ready", lora_dev->name);
// 		return;
// 	}

// 	config.frequency = 868000000;
// 	config.bandwidth = BW_125_KHZ;
// 	config.datarate = SF_7;
// 	config.preamble_len = 8;
// 	config.coding_rate = CR_4_5;
// 	config.tx_power = 14;
// 	config.tx = false;

// 	ret = lora_config(lora_dev, &config);
// 	if (ret < 0) {
// 		LOG_ERR("LoRa config failed");
// 		return;
// 	}

// 	SX126xIoRfSwitchInit();
// 	SX126xIoTcxoInit();
	
// 	/* Receive 4 packets synchronously */
// 	LOG_INF("Synchronous reception");
// 	for (int i = 0; i < 4; i++) {
// 		/* Block until data arrives */
// 		len = lora_recv(lora_dev, data, MAX_DATA_LEN, K_FOREVER,
// 				&rssi, &snr);
// 		if (len < 0) {
// 			LOG_ERR("LoRa receive failed");
// 			return;
// 		}

// 		LOG_INF("Received data: %s (RSSI:%ddBm, SNR:%ddBm)",
// 			data, rssi, snr);
// 	}

// 	/* Enable asynchronous reception */
// 	LOG_INF("Asynchronous reception");
// 	lora_recv_async(lora_dev, lora_receive_cb);
// 	k_sleep(K_FOREVER);
// }


// /*
//  * Copyright (c) 2019 Manivannan Sadhasivam
//  *
//  * SPDX-License-Identifier: Apache-2.0
//  * lora_sender
//  */

#include <zephyr/device.h>
#include <zephyr/drivers/lora.h>
#include <errno.h>
#include <zephyr/sys/util.h>
#include <zephyr/zephyr.h>

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
	     "No default LoRa radio specified in DT");

#define MAX_DATA_LEN 10

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lora_send);

//char data[MAX_DATA_LEN] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'};
char data[4] = {'P', 'I', 'N', 'G'};
char data2[4];

void main(void)
{
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
		ret = lora_send(lora_dev, data, 4);
		if (ret < 0) {
			LOG_ERR("LoRa send failed");
			return;
		}

		LOG_INF("Data sent!");

		/* Send data at 1s interval */
		//k_sleep(K_MSEC(1000));

		len = lora_recv(lora_dev, data2, 4, K_FOREVER, &rssi, &snr);
		if (len < 0) {
			LOG_ERR("LoRa receive failed");
			return;
		}

		LOG_INF("Received data: %s (RSSI:%ddBm, SNR:%ddBm)",
			data2, rssi, snr);
	}
}
