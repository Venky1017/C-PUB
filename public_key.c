#include <stdio.h>
#include <string.h>
#include <openssl/ripemd.h>

void create_public_key(const char *input) {
    unsigned char hash[RIPEMD160_DIGEST_LENGTH];

    // Calculate the RIPEMD-160 hash
    RIPEMD160_CTX ctx;
    RIPEMD160_Init(&ctx);
    RIPEMD160_Update(&ctx, (unsigned char*)input, strlen(input));
    RIPEMD160_Final(hash, &ctx);

    // Print the resulting hash
    printf("RIPEMD-160 Hash: ");
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    // The input string you want to hash
    const char *input = "739437bb3dd6d1983e66629c5f08c70e52769371";
    
    create_public_key(input);
    return 0;
}
