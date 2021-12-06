#include <Arduino.h>

void bottle_counter_init(void);
void bottle_counter(void *pvParameters);

/// Define setup for IR send and receive
static const gpio_num_t ir_tx_gpio = (gpio_num_t)16;
static const gpio_num_t ir_rx_gpio = (gpio_num_t)4;

#define GPIO_IR_TX ir_tx_gpio
#define GPIO_IR_TX_PIN_SEL (1ULL << ir_tx_gpio)
#define GPIO_IR_RX ir_rx_gpio
#define GPIO_BUTTON_PIN_SEL (1ULL << GPIO_IR_RX)
#define ESP_INTR_FLAG_DEFAULT 0
