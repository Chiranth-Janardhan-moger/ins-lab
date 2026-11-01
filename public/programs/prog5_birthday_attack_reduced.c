#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define HASH_SPACE 1000

int main() {
    srand(time(NULL));
    bool hash_seen[HASH_SPACE] = { false };
    int attempts = 0, hash_value;

    printf("Starting Birthday Attack Simulation...\n");
    printf("----------------------------------------\n");

    while (1) {
        hash_value = rand() % HASH_SPACE;
        attempts++;
        printf("Attempt %d: Generated hash value = %d --> ", attempts, hash_value);

        if (hash_seen[hash_value]) {
            printf("Collision Detected!\n\nSummary:\n");
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
