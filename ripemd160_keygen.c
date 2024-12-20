#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

// Generate a new public key using EC_KEY
void generate_public_key(unsigned char *ripemd160_hash) {
    EC_KEY *ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (!ec_key) {
        fprintf(stderr, "Failed to create EC key.\n");
        exit(1);
    }

    if (!EC_KEY_generate_key(ec_key)) {
        fprintf(stderr, "Failed to generate EC key.\n");
        EC_KEY_free(ec_key);
        exit(1);
    }

    const EC_POINT *pub_key = EC_KEY_get0_public_key(ec_key);
    const EC_GROUP *group = EC_KEY_get0_group(ec_key);

    unsigned char pub_key_bin[65]; // Maximum size for uncompressed public key
    size_t pub_key_len = EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED, pub_key_bin, sizeof(pub_key_bin), NULL);

    if (pub_key_len == 0) {
        fprintf(stderr, "Failed to convert public key to binary.\n");
        EC_KEY_free(ec_key);
        exit(1);
    }

    printf("Generated Public Key: ");
    for (size_t i = 0; i < pub_key_len; i++) {
        printf("%02x", pub_key_bin[i]);
    }
    printf("\n");

    // Compute RIPEMD-160 hash of the public key
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    SHA256(pub_key_bin, pub_key_len, sha256_hash);

    RIPEMD160(sha256_hash, SHA256_DIGEST_LENGTH, ripemd160_hash);

    EC_KEY_free(ec_key);
}

// Main function
int main() {
    unsigned char ripemd160_hash[RIPEMD160_DIGEST_LENGTH];

    generate_public_key(ripemd160_hash);

    printf("RIPEMD-160 Hash: ");
    for (size_t i = 0; i < RIPEMD160_DIGEST_LENGTH; i++) {
        printf("%02x", ripemd160_hash[i]);
    }
    printf("\n");

    return 0;
}
