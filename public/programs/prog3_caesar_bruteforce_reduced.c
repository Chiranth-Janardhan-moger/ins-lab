#include <stdio.h>
#include <ctype.h>

int main() {
    const char *ct = "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj.";
    printf("Ciphertext:\n%s\n\n--- Brute-Force Caesar Decryption Attempts ---\n\n", ct);

    for (int s = 1; s <= 26; s++) {
        printf("Shift %2d: ", s);
        for (int i = 0; ct[i]; i++) {
            if (isalpha(ct[i])) {
                char b = isupper(ct[i]) ? 'A' : 'a';
                putchar((ct[i] - b - s + 26) % 26 + b);
            } else putchar(ct[i]);
        }
        printf("\n");
    }
    return 0;
}
