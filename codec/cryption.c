#include <openssl/evp.h>
#include <openssl/rand.h>

#include "cryption.h"


binary_data aes_encryption(binary_data data) {
    EVP_CIPHER_CTX *ctx;
    int len;
    binary_data encrypted_data = {
            (unsigned char *) malloc(data.length + 10),
            0
    };
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, encrypted_data.content, &len, data.content, data.length);
    encrypted_data.length = len;
    EVP_EncryptFinal_ex(ctx, encrypted_data.content + len, &len);
    encrypted_data.length += len;
    EVP_CIPHER_CTX_free(ctx);
    return encrypted_data;
}

binary_data aes_decrypt(binary_data encrypted_data) {
    EVP_CIPHER_CTX *ctx;
    binary_data decrypted_plain_data = {
            (unsigned char *) malloc(encrypted_data.length),
            0
    };
    int len;
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, decrypted_plain_data.content, &len, encrypted_data.content, encrypted_data.length);
    decrypted_plain_data.length = len;
    EVP_DecryptFinal_ex(ctx, decrypted_plain_data.content + len, &len);
    decrypted_plain_data.length += len;
    EVP_CIPHER_CTX_free(ctx);
    return decrypted_plain_data;
}