#include <stdio.h>

// Function to generate Hamming code (7,4)
void generateHammingCode(int data[4], int hamming[7]) {
   

    hamming[2] = data[0]; // d1 at position 3
    hamming[4] = data[1]; // d2 at position 5
    hamming[5] = data[2]; // d3 at position 6
    hamming[6] = data[3]; // d4 at position 7

    // Calculate parity bits (even parity)
    hamming[0] = hamming[2] ^ hamming[4] ^ hamming[6]; // p1
    hamming[1] = hamming[2] ^ hamming[5] ^ hamming[6]; // p2
    hamming[3] = hamming[4] ^ hamming[5] ^ hamming[6]; // p4
}

// Function to detect the position of a single-bit error
int detectError(int hamming[7]) {
    int p1 = hamming[0] ^ hamming[2] ^ hamming[4] ^ hamming[6];
    int p2 = hamming[1] ^ hamming[2] ^ hamming[5] ^ hamming[6];
    int p4 = hamming[3] ^ hamming[4] ^ hamming[5] ^ hamming[6];

    int errorPos = p4 * 4 + p2 * 2 + p1 * 1;
    return errorPos;
}
A
int main() {
    int data[4], hamming[7];
    printf("Enter 4 data bits (0 or 1): ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &data[i]);
    }

    generateHammingCode(data, hamming);

    printf("\nGenerated Hamming Code (7 bits): ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", hamming[i]);
    }
    printf("\n");

    char simulate;
    printf("\nDo you want to simulate an error? (y/n): ");
    scanf(" %c", &simulate);

    if (simulate == 'y' || simulate == 'Y') {
        int pos;
        printf("Enter bit position to flip (1 to 7): ");
        scanf("%d", &pos);

        if (pos >= 1 && pos <= 7) {
            hamming[pos - 1] ^= 1; // Flip the bit

            printf("Hamming Code after error: ");
            for (int i = 0; i < 7; i++) {
                printf("%d ", hamming[i]);
            }
            printf("\n");

            int errorPos = detectError(hamming);
            if (errorPos == 0) {
                printf("No error detected.\n");
            } else {
                printf("Error detected at position: %d\n", errorPos);
                hamming[errorPos - 1] ^= 1; // Correct the bit

                printf("Corrected Hamming Code: ");
                for (int i = 0; i < 7; i++) {
                    printf("%d ", hamming[i]);
                }
                printf("\n");
            }
        } else {
            printf("Invalid position!\n");
        }
    }

    return 0;
}
