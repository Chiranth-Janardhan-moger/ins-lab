#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Unified cipher function: key for encrypt, -key for decrypt
void cipher(char text[], int key) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + (key % 26) + 26) % 26 + base;
        }
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the security key (shift value): ");
    scanf("%d", &key);

    // Encrypt
    cipher(message, key);
    printf("Encrypted Message: %s\n", message);

    // Decrypt back
    cipher(message, -key);
    printf("Decrypted Message: %s\n", message);

    return 0;
}
