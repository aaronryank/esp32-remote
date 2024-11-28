#include <esp_now.h>
#include <WiFi.h>
#include "<aes/esp_aes.h>"
#include "devices.h"
#include "private.h"

const int gpioPin = D10;

char receivedMessage[32];
char decryptedMessage[32];

// 40:4C:CA:57:8D:10

void decryptMessage(const char *encryptedMessage, char *decryptedMessage) {
  esp_aes_context aes;
  esp_aes_init(&aes);
  esp_aes_setkey(&aes, (const unsigned char *)aes_key, 128); // AES-128

  esp_aes_crypt_ecb(&aes, ESP_AES_DECRYPT, (const unsigned char *)encryptedMessage, (unsigned char *)decryptedMessage);

  esp_aes_free(&aes);
}

void onReceive(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(receivedMessage, incomingData, len);

  decryptMessage(receivedMessage, decryptedMessage);

  Serial.print("Decrypted message: ");
  Serial.println(decryptedMessage);

  if (String(decryptedMessage) == "CHANGE ME AFTER DOWNLOADING TOO") {
    digitalWrite(gpioPin, HIGH);
    delay(1000);                 // Keep it high for 1 second
    digitalWrite(gpioPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(gpioPin, OUTPUT);
  digitalWrite(gpioPin, LOW);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  // Register peer (replace with receiver's MAC address)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(onReceive)); // Register receive callback
  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {
  // Nothing to do here; everything is handled in the callback
}
