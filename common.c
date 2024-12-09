#include "common.h"

mac_addr_t broadcast_addr = {0xFF, 0xFF, 0XFF, 0XFF, 0XFF, 0XFF}, \
           fd_addr        = {0x40, 0x4C, 0xCA, 0x57, 0x8D, 0x10};
const char aes_key[] = "mgj5sni8hf5wrsde";
const char trigger_broadcast[] = "AYE OPEN SESAME FEED YOUR METH TO A JUUNKIE"

void MUSTWORK(const char *descriptor, esp_err_t code) {
    if (code != ESP_ERR_OK) {
        Serial.printf("Program failed during %s with code %d (%s)", descriptor, code, esp_err_to_name(code));
        esp_deep_sleep_start();
    }
}

void hackycracky_setup(bool rx_or_tx, const int gpioPin) {
  Serial.begin(115200);

  pinMode(gpioPin, rx_or_tx ? OUTPUT : INPUT);

  if (rx_or_tx == SETUP_RX)
	  digitalWrite(gpioPin, LOW);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcast_addr, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  MUSTWORK("Peer connection (to broadcast)", esp_now_add_peer(&peerInfo));
  
  if (rx_or_tx == SETUP_RX)

}