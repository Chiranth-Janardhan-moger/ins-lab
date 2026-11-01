#include <stdio.h>
#include <string.h>

#define MAX 100

// Unified vigenere: mode = 1 for encrypt, mode = -1 for decrypt
void vigenere(char text[], char key[], char out[], int mode) {
    int tLen = strlen(text), kLen = strlen(key);
    for (int i = 0, j = 0; i < tLen; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            out[i] = ((text[i] - 'A') + mode * (key[j++ % kLen] - 'A') + 26) % 26 + 'A';
        } else {
            out[i] = text[i];
        }
    }
    out[tLen] = '\0';
}

int main() {
    char plaintext[MAX], key[MAX], ciphertext[MAX], decrypted[MAX];

    printf("Enter plaintext (UPPERCASE): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter key (UPPERCASE): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    vigenere(plaintext, key, ciphertext, 1);
    printf("\nEncrypted Text: %s\n", ciphertext);

    vigenere(ciphertext, key, decrypted, -1);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
