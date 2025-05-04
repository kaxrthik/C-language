#include <stdio.h>
#include <string.h>
int main()
{
    int i,j = 0;
    char frame[100], stufframe[200];
    printf("Enter input frame (0's & 1's only): ");
    scanf("%s", frame);
    strcat(stufframe, "01111110 ");
    for (i = 0; frame[i]; i++)
    {
        stufframe[j++] = frame[i];
        if (i >= 5 && frame[i - 5] == '0' && frame[i - 4] == '1' && frame[i - 3] == '1' && frame[i - 2] == '1' && frame[i - 1] == '1' && frame[i] == '1')
        {
            stufframe[j++] = '0';
        }
    }
    strcat(stufframe, " 01111110");
    printf("After Bit Stuffing: %s\n", stufframe);
    return 0;
}
