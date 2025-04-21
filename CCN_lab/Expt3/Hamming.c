// HAMMING CODE AND ERROR DETECTION FOR 1 BIT ERRORS CORRECTION ONLY
#include <stdio.h>
int main()
{
    int d[4], h[7], received[7], error_pos = 0;
    printf("Enter 4-bit data (spacing every bit): "); // Input 4-bit data
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &d[i]);
    }
    // Hamming code generation
    h[2] = d[0];
    h[4] = d[1];
    h[5] = d[2];
    h[6] = d[3];
    h[0] = (d[0] + d[1] + d[3]) % 2; // P1
    h[1] = (d[0] + d[2] + d[3]) % 2; // P2
    h[3] = (d[1] + d[2] + d[3]) % 2; // P4
    printf("Generated 7-bit Hamming code:"); // Print generated Hamming code
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", h[i]);
    }
    printf("\n");
    printf("Enter received 7-bit codeword:"); // Input received 7-bit codeword
    for (int i = 0; i < 7; i++)
    {
        scanf(" %d", &received[i]);
    }
    // Check parity bits
    int P1 = (received[0] + received[2] + received[4] + received[6]) % 2;
    int P2 = (received[1] + received[2] + received[5] + received[6]) % 2;
    int P4 = (received[3] + received[4] + received[5] + received[6]) % 2;
    error_pos = (P4 * 4) + (P2 * 2) + (P1 * 1);
    if (error_pos == 0) // Output error detection and correction
    {
        printf("No error detected\n");
    }
    else
    {
        printf("Error detected at position: %d\n", error_pos);
        received[error_pos - 1] ^= 1; // Correct the error
        printf("Corrected codeword: ");
        for (int i = 0; i < 7; i++)
        {
            printf(" %d", received[i]); // Fixed the printing of the values
        }
        printf("\n");
    }
    return 0;
}
