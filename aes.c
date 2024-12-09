#include "common.h"

void cryptMessage(const bool operation, const char *plainText, char *encryptedMessage) {
  esp_aes_context aes;
  esp_aes_init(&aes);
  esp_aes_setkey(&aes, (const unsigned char *)aes_key, 128);

  esp_aes_crypt_ecb(&aes, operation, (const unsigned char *) plainText, (unsigned char *) encryptedMessage);

  esp_aes_free(&aes);
}