#include <Arduino.h>

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <dht.h>
#include <spi.h>
#include <MFRC522.h>
#include <bottle_counter.h> //transmit on GPIO16, receive on GPIO4
#include <my_dht.h>			// connected to GPIO17

//#define RST_PIN         9          // Configurable, see typical pin layout above
//#define SS_PIN          10         // Configurable, see typical pin layout above
//Edit for this implimentation (TTGO LoRa V1.3)
#define RST_PIN 16 // Configurable, see typical pin layout above
#define SS_PIN 17  // Configurable, see typical pin layout above
#define SCK_PIN 14
#define MISO_PIN 12
#define MOSI_PIN 13




MFRC522 mfrc522((byte)SS_PIN, (byte)RST_PIN);  // Create MFRC522 instance, typecast


void rfid_init() {
	Serial.begin(115200);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin((int8_t)SCK_PIN, (int8_t)MISO_PIN, (int8_t)MOSI_PIN , (int8_t)SS_PIN);			// Init SPI bus
	mfrc522.PCD_Init(SS_PIN,RST_PIN);		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}
void setup(){
    rfid_init();
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}




/*
void setup()
{
   // bottle_counter_init();
   // xTaskCreate(dht_test, "dht_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    //xTaskCreate(bottle_counter, "bottle_counter", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(bottle_counter, "bottle_counter", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
*/