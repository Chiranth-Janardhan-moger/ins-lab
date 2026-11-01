#include <stdio.h>
#include <string.h>

#define MAX_TEXT 100

// Encryption function
void encryptTranspositionCipher(char plaintext[], int key) {
    int len = strlen(plaintext);
    char ciphertext[MAX_TEXT] = {0};
    int index = 0;

    for (int col = 0; col < key; col++) {
        for (int i = col; i < len; i += key) {
            ciphertext[index++] = plaintext[i];
        }
    }

    ciphertext[index] = '\0';
    printf("\nCiphertext: %s\n", ciphertext);
}

// Decryption function
void decryptTranspositionCipher(char ciphertext[], int key) {
    int len = strlen(ciphertext);
    int numRows = len / key;
    if (len % key != 0)
        numRows++;

    char grid[numRows][key];
    int index = 0;

    // Calculate number of filled cells in the last row
    int fullColumns = len % key;
    if (fullColumns == 0)
        fullColumns = key;

    // Initialize grid with '\0' to mark empty positions
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < key; c++)
            grid[r][c] = '\0';

    // Fill grid column by column
    for (int col = 0; col < key; col++) {
        int maxRow = numRows;
        // Last column may have fewer elements
        if (col >= fullColumns)
            maxRow = numRows - 1;
        for (int row = 0; row < maxRow; row++) {
            if (index < len)
                grid[row][col] = ciphertext[index++];
        }
    }

    printf("\nDecrypted Plaintext: ");
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < key; col++) {
            if (grid[row][col] != '\0')
                putchar(grid[row][col]);
        }
    }
    printf("\n");
}

int main() {
    char plaintext[MAX_TEXT];
    int key;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the key (number of columns): ");
    scanf("%d", &key);

    encryptTranspositionCipher(plaintext, key);

    char ciphertext[MAX_TEXT];
    printf("\nEnter the ciphertext to decrypt: ");
    scanf(" %[^\n]", ciphertext); // Read full line including spaces

    decryptTranspositionCipher(ciphertext, key);

    return 0;
}
