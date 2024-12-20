#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

// Function to print a byte array as a hexadecimal string
void print_hex(unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Input hexadecimal string
    const char *input = "739437bb3dd6d1983e66629c5f08c70e52769371";
    size_t input_len = strlen(input) / 2;

    // Convert the input hex string to byte array
    unsigned char input_bytes[input_len];
    for (size_t i = 0; i < input_len; i++) {
        sscanf(&input[i * 2], "%2hhx", &input_bytes[i]);
    }

    // Step 1: Apply SHA-256
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256(input_bytes, input_len, sha256_hash);
    printf("SHA-256 hash:\n");
    print_hex(sha256_hash, SHA256_DIGEST_LENGTH);

    // Step 2: Apply RIPEMD-160 to the SHA-256 hash
    unsigned char ripemd160_hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160(sha256_hash, SHA256_DIGEST_LENGTH, ripemd160_hash);
    printf("RIPEMD-160 hash (public key hash):\n");
    print_hex(ripemd160_hash, RIPEMD160_DIGEST_LENGTH);

    return 0;
}
