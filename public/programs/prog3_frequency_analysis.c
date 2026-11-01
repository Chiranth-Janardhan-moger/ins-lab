#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TEXT 1000
#define ALPHABET 26

// Standard English letter frequency order (most frequent to least frequent)
const char english_freq_order[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void calculate_frequency(const char *text, int freq[]) {
    // Initialize frequency array
    for (int i = 0; i < ALPHABET; i++) freq[i] = 0;

    // Count letter frequency
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

void print_frequency(int freq[]) {
    printf("\n--- Letter Frequency in Ciphertext ---\n");
    for (int i = 0; i < ALPHABET; i++) {
        printf("%c : %d\n", 'A' + i, freq[i]);
    }
}

void sort_frequency(int freq[], char letters_sorted[]) {
    int freq_copy[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) freq_copy[i] = freq[i];

    for (int i = 0; i < ALPHABET; i++) {
        int max_idx = -1;
        int max_val = -1;
        for (int j = 0; j < ALPHABET; j++) {
            if (freq_copy[j] > max_val) {
                max_val = freq_copy[j];
                max_idx = j;
            }
        }
        freq_copy[max_idx] = -1; // Mark as used
        letters_sorted[i] = 'A' + max_idx;
    }
}

void apply_frequency_analysis(const char *ciphertext, char *plaintext, char letters_sorted[]) {
    // Mapping from ciphertext letter to guessed plaintext letter
    char mapping[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        mapping[letters_sorted[i] - 'A'] = english_freq_order[i];
    }

    printf("\n--- Mapping of Ciphertext letters to Guessed Letters ---\n");
    for (int i = 0; i < ALPHABET; i++) {
        printf("%c -> %c\n", letters_sorted[i], english_freq_order[i]);
    }

    // Decrypt based on frequency mapping
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            int idx = toupper(ciphertext[i]) - 'A';
            char mapped_char = mapping[idx];
            if (islower(ciphertext[i]))
                plaintext[i] = tolower(mapped_char);
            else
                plaintext[i] = mapped_char;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT];
    char plaintext[MAX_TEXT];

    printf("Enter Ciphertext (max 1000 chars):\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Remove newline if present
    size_t len = strlen(ciphertext);
    if (len > 0 && ciphertext[len - 1] == '\n') ciphertext[len - 1] = '\0';

    int freq[ALPHABET];
    char letters_sorted[ALPHABET + 1];
    letters_sorted[ALPHABET] = '\0';

    printf("\n--- Step 1: Calculating Letter Frequencies ---\n");
    calculate_frequency(ciphertext, freq);
    print_frequency(freq);

    printf("\n--- Step 2: Sorting Letters by Frequency ---\n");
    sort_frequency(freq, letters_sorted);
    printf("Letters sorted by frequency (most frequent first): %s\n", letters_sorted);

    printf("\n--- Step 3: Applying Frequency Analysis Mapping ---\n");
    apply_frequency_analysis(ciphertext, plaintext, letters_sorted);

    printf("\n--- Step 4: Resulting Decrypted Text ---\n");
    printf("%s\n", plaintext);

    return 0;
}
