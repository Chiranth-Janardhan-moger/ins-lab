#include <stdio.h>
#include <string.h>

#define MAX_TEXT 100

void encryptTranspositionCipher(char plaintext[], int key) {
    int len = strlen(plaintext), idx = 0;
    char ciphertext[MAX_TEXT] = {0};

    for (int col = 0; col < key; col++) {
        for (int i = col; i < len; i += key) {
            ciphertext[idx++] = plaintext[i];
        }
    }
    ciphertext[idx] = '\0';
    printf("\nCiphertext: %s\n", ciphertext);
}

void decryptTranspositionCipher(char ciphertext[], int key) {
    int len = strlen(ciphertext), idx = 0;
    int rows = (len + key - 1) / key;
    int fullCols = (len % key) ? (len % key) : key;
    char plaintext[MAX_TEXT];

    for (int col = 0; col < key; col++) {
        int maxRow = (col < fullCols) ? rows : rows - 1;
        for (int r = 0; r < maxRow; r++) {
            plaintext[r * key + col] = ciphertext[idx++];
        }
    }
    plaintext[len] = '\0';
    printf("\nDecrypted Plaintext: %s\n", plaintext);
}

int main() {
    char plaintext[MAX_TEXT], ciphertext[MAX_TEXT];
    int key;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the key (number of columns): ");
    scanf("%d", &key);

    encryptTranspositionCipher(plaintext, key);

    printf("\nEnter the ciphertext to decrypt: ");
    scanf(" %[^\n]", ciphertext);

    decryptTranspositionCipher(ciphertext, key);

    return 0;
}
