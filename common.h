// common.h

#include <aes/esp_aes.h>
#include <esp_now.h>
#include <esp_err.h>
#include <WiFi.h>

// responses to peer packets
#define RESPONSE_ACK "ackermann"
#define RESPONSE_ERROR "erroneous"
#define RESPONSE_RETURN "cretaceous"
#define RESPONSE_IGNORE "ignacious"

#define SETUP_RX true
#define SETUP_TX false

typedef const uint8_t mac_addr_t[6];

extern mac_addr_t broadcast_addr, \
       fd_addr; /* imaginary things follow
	   master_addr,
       hp_addr,        \
       gp_addr,        \
       car_addr; */
	   
extern const char aes_key[];
extern const char trigger_broadcast[];

void MUSTWORK(const char *descriptor, esp_err_t code);
void hackycracky_setup(bool rx_or_tx);
void cryptMessage(const bool operation, const char *plainText, char *encryptedMessage);