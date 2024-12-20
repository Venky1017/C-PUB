#include <stdio.h>
#include <string.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>

void generate_public_key(const char* input) {
    // Initialize RIPEMD160 context
    unsigned char hash[RIPEMD160_DIGEST_LENGTH];
    
    // Perform RIPEMD160 hash on the input (input is already a hex string)
    RIPEMD160_CTX ctx;
    RIPEMD160_Init(&ctx);
    RIPEMD160_Update(&ctx, input, strlen(input));
    RIPEMD160_Final(hash, &ctx);
    
    // Print the resulting public key (in hexadecimal form)
    printf("Public Key: ");
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    // Example input hash
    const char* input = "739437bb3dd6d1983e66629c5f08c70e52769371";
    
    generate_public_key(input);
    
    return 0;
}
