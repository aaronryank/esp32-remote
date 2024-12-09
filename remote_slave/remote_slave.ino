#include "common.h"

const int outputPin = D10;

char receivedMessage[32];
char decryptedMessage[32];

// I'm the front door
// 40:4C:CA:57:8D:10

void onReceive(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(receivedMessage, incomingData, len);

  cryptMessage(ESP_AES_DECRYPT, receivedMessage, decryptedMessage);

  Serial.print("Decrypted message: ");
  Serial.println(decryptedMessage);

  if (String(decryptedMessage) == String(trigger_broadcast)) {
    digitalWrite(outputPin, HIGH);
    delay(1500);                 // Keep it high for 1.5 seconds
    digitalWrite(outputPin, LOW);
  }
}

void setup() {
  hackycracky_setup(SETUP_RX, outputPin);

  esp_now_register_recv_cb(esp_now_recv_cb_t(onReceive)); // Register receive callback
  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {
    delay(500);
  // Nothing to do here; everything is handled in the callback
}
