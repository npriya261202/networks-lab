#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // For dynamic memory allocation

// Function to encrypt the message
void encrypt(char *plaintext, const char *key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = key[plaintext[i] - base];
        }
    }
}

// Function to decrypt the message
void decrypt(char *ciphertext, const char *key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            const char *pos = strchr(key, ciphertext[i]);
            if (pos != NULL) {
                ciphertext[i] = base + (pos - key);
            }
        }
    }
}

int main() {
    char plaintext[100];
    char *key;
    char ciphertext[100];
    char decrypted[100];

    // Input plaintext from user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline if present

    // Input key from user
    printf("Enter the key: ");
    key = (char *)malloc(256 * sizeof(char)); // Allocate memory for the key dynamically
    fgets(key, 256, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline if present

    // Encrypt the plaintext
    strcpy(ciphertext, plaintext);
    encrypt(ciphertext, key);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    strcpy(decrypted, ciphertext);
    decrypt(decrypted, key);
    printf("Decrypted plaintext: %s\n", decrypted);

    // Free dynamically allocated memory for key
    free(key);

    return 0;
}

