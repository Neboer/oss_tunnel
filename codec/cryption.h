#pragma once

extern const unsigned char *key;// 256bit
extern const unsigned char *iv;// 128bit

struct binary_data_s {
    unsigned char *content;
    int length;
};

typedef struct binary_data_s binary_data;

binary_data aes_encryption(binary_data data);

binary_data aes_decrypt(binary_data encrypted_data);
