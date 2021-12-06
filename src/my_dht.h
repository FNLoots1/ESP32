#include <Arduino.h>
#include <dht.h>

void dht_test(void *pvParameters);  //function to read environmentals and print to display

static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
#if defined(CONFIG_IDF_TARGET_ESP8266)
static const gpio_num_t dht_gpio = 4;
#else
static const gpio_num_t dht_gpio = (gpio_num_t)17;
#endif
