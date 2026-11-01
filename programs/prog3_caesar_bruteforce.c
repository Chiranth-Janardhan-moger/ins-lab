#include <stdio.h>
#include <ctype.h>

// Function to decrypt using a given shift
void caesar_decrypt(const char *ciphertext, int shift) {
    for (int i = 0; ciphertext[i]; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char decrypted = (ch - base - shift + 26) % 26 + base;
            printf("%c", decrypted);
        } else {
            printf("%c", ch);
        }
    }
    printf("\n");
}

int main() {
    const char *ciphertext = "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj.";
    printf("Ciphertext:\n%s\n\n", ciphertext);
    printf("--- Brute-Force Caesar Decryption Attempts ---\n\n");

    // Try all 26 possible shifts
    for (int shift = 1; shift <= 26; shift++) {
        printf("Shift %2d: ", shift);
        caesar_decrypt(ciphertext, shift);
    }

    return 0;
}
