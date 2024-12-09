#include "common.h"

const int inputPin = 4;

char encryptedMessage[32];

void setup() {
  hackycracky_setup(SETUP_TX, inputPin);

  cryptMessage(ESP_AES_ENCRYPT, trigger_broadcast, encryptedMessage);
  Serial.println("ESP-NOW Transmitter Ready");
}

void loop() {
  while (digitalRead(inputPin) != HIGH)
    delay(500);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)encryptedMessage, sizeof(encryptedMessage));

  if (result == ESP_OK)
    Serial.println("Encrypted message sent successfully");
  else
    Serial.printf("Error %d sending message: %s\n", result, esp_err_to_name(result));

  delay(500);
}

