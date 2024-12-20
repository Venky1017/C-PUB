#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

void print_hex(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Your public key here (example of 33 bytes public key)
    unsigned char public_key[] = {
        0x04, 0x88, 0xAD, 0xDF, 0x51, 0xF0, 0xB5, 0xD2, 0xBC, 0x3F, 0xC2, 0x13, 0x94, 0xE5, 0x92, 0x6A,
        0x8D, 0xEC, 0x90, 0x45, 0xC1, 0x73, 0x8D, 0xA9, 0xAB, 0xF5, 0xD4, 0x85, 0x2B, 0x4E, 0x1A, 0x9E,
        0x9A
    };
    size_t public_key_len = sizeof(public_key);

    // Step 1: Apply SHA-256 to the public key
    unsigned char sha256_result[SHA256_DIGEST_LENGTH];
    SHA256(public_key, public_key_len, sha256_result);
    printf("SHA-256 of public key: ");
    print_hex(sha256_result, SHA256_DIGEST_LENGTH);

    // Step 2: Apply RIPEMD-160 to the SHA-256 hash
    unsigned char ripemd160_result[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160(sha256_result, SHA256_DIGEST_LENGTH, ripemd160_result);
    printf("RIPEMD-160 hash of the SHA-256 result: ");
    print_hex(ripemd160_result, RIPEMD160_DIGEST_LENGTH);

    // Compare with the given hash
    unsigned char target_hash[] = { 0x73, 0x94, 0x37, 0xbb, 0x3d, 0xd6, 0xd1, 0x98, 0x3e, 0x66, 0x62, 0x9c, 0x5f, 0x08, 0xc7, 0x0e, 0x52, 0x76, 0x93, 0x71 };
    if (memcmp(ripemd160_result, target_hash, RIPEMD160_DIGEST_LENGTH) == 0) {
        printf("Match found: The public key hash matches the target hash!\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}
