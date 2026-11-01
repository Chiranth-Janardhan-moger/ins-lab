#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to encrypt text using Caesar Cipher
void encrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            text[i] = (ch - base + key) % 26 + base;
        }
    }
}

// Function to decrypt text using Caesar Cipher
void decrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            text[i] = (ch - base - key + 26) % 26 + base;
        }
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    // Remove newline character if any
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the security key (shift value): ");
    scanf("%d", &key);

    // Encrypt
    encrypt(message, key);
    printf("Encrypted Message: %s\n", message);

    // Decrypt back
    decrypt(message, key);
    printf("Decrypted Message: %s\n", message);

    return 0;
}
