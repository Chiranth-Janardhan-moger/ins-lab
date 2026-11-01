#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char eng[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

int main() {
    char text[1000], order[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", map[26];
    int freq[26] = {0};

    printf("Enter Ciphertext (max 1000 chars):\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("\n--- Step 1: Calculating Letter Frequencies ---\n\n--- Letter Frequency in Ciphertext ---\n");
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) freq[toupper(text[i]) - 'A']++;
    for (int i = 0; i < 26; i++)
        printf("%c : %d\n", 'A' + i, freq[i]);

    printf("\n--- Step 2: Sorting Letters by Frequency ---\n");
    for (int i = 0; i < 26; i++) {
        int m = i;
        for (int j = i + 1; j < 26; j++)
            if (freq[order[j] - 'A'] > freq[order[m] - 'A']) m = j;
        char temp = order[m];
        while (m > i) { order[m] = order[m - 1]; m--; }
        order[i] = temp;
    }
    printf("Letters sorted by frequency (most frequent first): %s\n", order);

    printf("\n--- Step 3: Applying Frequency Analysis Mapping ---\n\n--- Mapping of Ciphertext letters to Guessed Letters ---\n");
    for (int i = 0; i < 26; i++) {
        map[order[i] - 'A'] = eng[i];
        printf("%c -> %c\n", order[i], eng[i]);
    }

    printf("\n--- Step 4: Resulting Decrypted Text ---\n");
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char m = map[toupper(text[i]) - 'A'];
            putchar(islower(text[i]) ? tolower(m) : m);
        } else putchar(text[i]);
    }
    printf("\n");
    return 0;
}
