#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define HASH_SPACE 1000 // Hash values range from 0 to 999

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Array to track seen hash values
    bool hash_seen[HASH_SPACE] = { false };
    int attempts = 0;
    int hash_value;

    printf("Starting Birthday Attack Simulation...\n");
    printf("----------------------------------------\n");

    while (1) {
        hash_value = rand() % HASH_SPACE; // Generate random hash [0, 999]
        attempts++;
        printf("Attempt %d: Generated hash value = %d --> ", attempts, hash_value);

        if (hash_seen[hash_value]) {
            printf("Collision Detected!\n");
            printf("\nSummary:\n");
            printf(" - Total attempts made: %d\n", attempts);
            printf(" - Collided hash value: %d\n", hash_value);
            break;
        } else {
            printf("No collision, marking as seen.\n");
            hash_seen[hash_value] = true;
        }
    }

    printf("----------------------------------------\n");
    printf("Birthday Attack Simulation Completed.\n");

    return 0;
}
