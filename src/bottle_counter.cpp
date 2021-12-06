#include <Arduino.h>

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "driver/adc.h"
#include "driver/ledc.h"

#define SAMPLE_CNT 32
static const adc1_channel_t adc_channel = ADC1_CHANNEL_6;

// Define setup for IR send and receive
static const gpio_num_t ir_tx_gpio = (gpio_num_t)16;
static const gpio_num_t ir_rx_gpio = (gpio_num_t)4;

#define GPIO_IR_TX ir_tx_gpio
#define GPIO_IR_TX_PIN_SEL (1ULL << ir_tx_gpio)
#define GPIO_IR_RX ir_rx_gpio
#define GPIO_BUTTON_PIN_SEL (1ULL << GPIO_IR_RX)

void bottle_counter_init(void)
{

    //configure transmitter on GPIO 16
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_IR_TX_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = (gpio_pulldown_t)0;
    io_conf.pull_up_en = (gpio_pullup_t)0;
    gpio_config(&io_conf);

    //Configure Receiver on GPIO 34
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
}

void bottle_counter(void *pvParameters)
{
    // static uint32_t laser_tics = 0;
    //  static uint32_t bottles = 0;
    static uint32_t adc_val = 0;

    for (;;)
    {
        printf("Led on, take reading\n");
        gpio_set_level(GPIO_IR_TX, HIGH); //turn LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
        adc_val = 0;
        for (int i = 0; i < SAMPLE_CNT; ++i)
        {
            adc_val += adc1_get_raw(adc_channel);
//            printf("Led on Value: %d /n", adc_val);
  //          vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        adc_val /= SAMPLE_CNT;
        printf("Led on Value: %d    ----", adc_val);
        gpio_set_level(GPIO_IR_TX, LOW); //turn LED off
        vTaskDelay(100 / portTICK_PERIOD_MS);
        adc_val = 0;
        for (int i = 0; i < SAMPLE_CNT; ++i)
        {
            adc_val += adc1_get_raw(adc_channel);
//            printf("Led on Value: %d /n", adc_val);
  //          vTaskDelay(100 / portTICK_PERIOD_MS);            
        }

        adc_val /= SAMPLE_CNT;
        printf("Led off Value: %d\n", adc_val);

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
