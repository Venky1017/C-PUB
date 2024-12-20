#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <string.h>

void sha256(const unsigned char *input, unsigned char *output) {
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input, strlen((const char*)input));
    SHA256_Final(output, &sha256_ctx);
}

void ripemd160(const unsigned char *input, unsigned char *output) {
    RIPEMD160_CTX ripemd160_ctx;
    RIPEMD160_Init(&ripemd160_ctx);
    RIPEMD160_Update(&ripemd160_ctx, input, SHA256_DIGEST_LENGTH);
    RIPEMD160_Final(output, &ripemd160_ctx);
}

int main() {
    // Example public key (in hexadecimal format)
    const unsigned char public_key[] = "739437bb3dd6d1983e66629c5f08c70e52769371";

    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    unsigned char ripemd160_hash[RIPEMD160_DIGEST_LENGTH];

    // Step 1: Apply SHA-256
    sha256(public_key, sha256_hash);
    printf("SHA-256 Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", sha256_hash[i]);
    }
    printf("\n");

    // Step 2: Apply RIPEMD-160
    ripemd160(sha256_hash, ripemd160_hash);
    printf("RIPEMD-160 Hash (Public Key Hash): ");
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++) {
        printf("%02x", ripemd160_hash[i]);
    }
    printf("\n");

    return 0;
}
