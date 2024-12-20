#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

#define PREFIX 0x00  // Bitcoin mainnet address prefix

// Function to perform SHA256 hash
void sha256(unsigned char *input, size_t length, unsigned char *output) {
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input, length);
    SHA256_Final(output, &sha256_ctx);
}

// Function to perform RIPEMD160 hash
void ripemd160(unsigned char *input, size_t length, unsigned char *output) {
    RIPEMD160_CTX ripemd160_ctx;
    RIPEMD160_Init(&ripemd160_ctx);
    RIPEMD160_Update(&ripemd160_ctx, input, length);
    RIPEMD160_Final(output, &ripemd160_ctx);
}

// Function to perform double hash (SHA256 -> RIPEMD160)
void double_hash(unsigned char *input, size_t length, unsigned char *output) {
    unsigned char sha256_result[SHA256_DIGEST_LENGTH];
    unsigned char ripemd160_result[RIPEMD160_DIGEST_LENGTH];

    // First SHA256 hash
    sha256(input, length, sha256_result);
    
    // Then RIPEMD160 hash
    ripemd160(sha256_result, SHA256_DIGEST_LENGTH, ripemd160_result);

    // Copy the final result
    memcpy(output, ripemd160_result, RIPEMD160_DIGEST_LENGTH);
}

// Function to add prefix and perform double hash
void generate_public_key(const char *input_hex) {
    unsigned char input_bytes[strlen(input_hex) / 2];
    unsigned char hash_result[RIPEMD160_DIGEST_LENGTH + 1]; // +1 for the prefix
    size_t i;

    // Convert hex string to bytes
    for (i = 0; i < strlen(input_hex); i += 2) {
        sscanf(input_hex + i, "%2hhx", &input_bytes[i / 2]);
    }

    // Add the prefix
    hash_result[0] = PREFIX;

    // Perform the double hash
    double_hash(input_bytes, sizeof(input_bytes), &hash_result[1]);

    // Print the result as a hexadecimal string
    printf("Generated Public Key: ");
    for (i = 0; i < sizeof(hash_result); i++) {
        printf("%02x", hash_result[i]);
    }
    printf("\n");
}

int main() {
    // The input string in hexadecimal (you can modify this input)
    const char *input = "739437bb3dd6d1983e66629c5f08c70e52769371";

    // Generate and print the public key
    generate_public_key(input);

    return 0;
}
