#include <esp_now.h>
#include <WiFi.h>
#include <esp_err.h>
#include <aes/esp_aes.h>
#include "devices.h"
#include "common.h"

//common.h
//const char aes_key[];
//const char plainText[];
//uint8_t broadcastAddress[]; becomes broadcast_addr

//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//const char plainText[] = "CHANGE ME AFTER DOWNLOADING TOO"; // Message to encrypt

char encryptedMessage[32];

const int triggerPin = 4;

void MUSTWORK(const char *descriptor, esp_err_t code) {
    if (code != ESP_ERR_OK) {
        Serial.printf("Program failed during %s with code %d (%s)", descriptor, code, esp_err_to_name(code));
        esp_deep_sleep_start();
    }
}

void encryptMessage(const char *plainText, char *encryptedMessage) {
  esp_aes_context aes;
  esp_aes_init(&aes);
  esp_aes_setkey(&aes, (const unsigned char *)aes_key, 128);

  esp_aes_crypt_ecb(&aes, ESP_AES_ENCRYPT, (const unsigned char *)plainText, (unsigned char *)encryptedMessage);

  esp_aes_free(&aes);
}

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, INPUT);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  MUSTWORK("ESP-NOW initialization", esp_now_init());

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  MUSTWORK("Peer connection", esp_now_add_peer(&peerInfo))

  encryptMessage(plainText, encryptedMessage);
  Serial.println("Message encrypted");
}

void loop() {
  while (digitalRead(triggerPin) != HIGH) {
    delay(500);
  }

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)encryptedMessage, sizeof(encryptedMessage));
  if (result == ESP_OK) {
    Serial.println("Encrypted message sent successfully");
  } else {
    Serial.printf("Error %d sending message: %s\n", result, esp_err_to_name(result));
  }
  delay(500);
}

