//CYCLIC REDUNDANCY CHECK
#include <stdio.h>
#include <string.h>

#define POLYNOMIAL "10001000000100001" // 17-bit generator polynomial

// Function to perform binary division and calculate CRC
void calculateCRC(char *dataword, char *remainder) {
    int dataLength = strlen(dataword);
    int polyLength = strlen(POLYNOMIAL);
   
    // Append zeros to the dataword (degree of polynomial is 17)
    char augmentedData[100];
    strcpy(augmentedData, dataword);
    for (int i = 0; i < polyLength - 1; i++) {
        augmentedData[dataLength + i] = '0';
    }
    augmentedData[dataLength + polyLength - 1] = '\0'; // Null-terminate the string

    // Perform the binary division
    for (int i = 0; i < dataLength; i++) {
        if (augmentedData[i] == '1') {
            for (int j = 0; j < polyLength; j++) {
                // XOR with the polynomial
                augmentedData[i + j] = (augmentedData[i + j] == POLYNOMIAL[j]) ? '0' : '1';
            }
        }
    }

    // The CRC is the last (polyLength - 1) bits of the augmented data
    strncpy(remainder, augmentedData + dataLength, polyLength - 1);
    remainder[polyLength - 1] = '\0'; // Null-terminate the remainder
}

// Function to check for errors in the received codeword
int checkForErrors(char *codeword) {
    int dataLength = strlen(codeword) - (strlen(POLYNOMIAL) - 1);
    int polyLength = strlen(POLYNOMIAL);
   
    // Perform binary division on the received codeword
    char augmentedData[100];
    strcpy(augmentedData, codeword);
   
    // Perform the binary division
    for (int i = 0; i < dataLength; i++) {
        if (augmentedData[i] == '1') {
            for (int j = 0; j < polyLength; j++) {
                // XOR with the polynomial
                augmentedData[i + j] = (augmentedData[i + j] == POLYNOMIAL[j]) ? '0' : '1';
            }
        }
    }

    // Check the remainder; if it's all zeros, no error is detected
    for (int i = dataLength; i < dataLength + polyLength - 1; i++) {
        if (augmentedData[i] == '1') {
            return 1; // Error detected
        }
    }
    return 0; // No error
}

int main() {
    char dataword[100];
    char remainder[100];
    char codeword[100];

    printf("Enter the dataword (up to 13 bits): ");
    fgets(dataword, sizeof(dataword), stdin);
   
    // Remove newline character from input
    dataword[strcspn(dataword, "\n")] = 0;

    // Ensure the dataword is not longer than 13 bits
    if (strlen(dataword) > 13) {
        printf("Dataword must be 13 bits or less.\n");
        return 1;
    }

    // Calculate the CRC
    calculateCRC(dataword, remainder);

    // Create the codeword by appending the remainder to the dataword
    strcpy(codeword, dataword);
    strcat(codeword, remainder);

    // Print the final remainder (CRC) and the codeword
    printf("Final remainder (CRC): %s\n", remainder);
    printf("Codeword (Dataword + CRC): %s\n", codeword);

    // Ask for the received codeword
    char receivedCodeword[100];
    printf("Enter the received codeword to check for errors: ");
    fgets(receivedCodeword, sizeof(receivedCodeword), stdin);
    receivedCodeword[strcspn(receivedCodeword, "\n")] = 0; // Remove newline character

    // Check for errors in the received codeword
    if (checkForErrors(receivedCodeword)) {
        printf("Error detected in the received codeword.\n");
    } else {
        printf("No error detected in the received codeword.\n");
    }
   
    return 0;
}