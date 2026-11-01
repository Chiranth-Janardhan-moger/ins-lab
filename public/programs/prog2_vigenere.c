#include <stdio.h>
#include <string.h>

#define MAX 100

void encrypt(char text[], char key[], char cipher[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0, j = 0; i < textLen; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            cipher[i] = ((text[i] - 'A') + (key[j % keyLen] - 'A')) % 26 + 'A';
            j++;
        } else {
            cipher[i] = text[i]; // Keep spaces and special characters
        }
    }
    cipher[textLen] = '\0';
}

void decrypt(char cipher[], char key[], char text[]) {
    int textLen = strlen(cipher);
    int keyLen = strlen(key);

    for (int i = 0, j = 0; i < textLen; i++) {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
            text[i] = ((cipher[i] - 'A') - (key[j % keyLen] - 'A') + 26) % 26 + 'A';
            j++;
        } else {
            text[i] = cipher[i]; // Keep spaces and special characters
        }
    }
    text[textLen] = '\0';
}

int main() {
    char plaintext[MAX], key[MAX], ciphertext[MAX], decrypted[MAX];

    printf("Enter plaintext (UPPERCASE): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    printf("Enter key (UPPERCASE): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    encrypt(plaintext, key, ciphertext);
    printf("\nEncrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
