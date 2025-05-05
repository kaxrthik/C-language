#include <stdio.h>
#include <string.h>
int main()
{
    int i ,j = 0;
    char frame[100], stuffframe[200]="\0";
    char beginningFlag[] = "dlestx";
    char endFlag[] = "dleetx";
    printf("Enter frame: "); // Prompt the user to enter a frame
    scanf("%s", frame);
    strcpy(stuffframe, beginningFlag); // Start the stuffed frame with the starting flag
    j = strlen(stuffframe);
    while (frame[i] != '\0')
    {
        if (frame[i] == 'd' && frame[i + 1] == 'l' && frame[i + 2] == 'e') // Check if a 'dle' sequence starts here
        {
            stuffframe[j++] = 'd'; // Stuff another 'dle' before the actual 'dle'
            stuffframe[j++] = 'l';
            stuffframe[j++] = 'e';
        }
        stuffframe[j++] = frame[i++]; // Copy the current character
    }
    strcat(stuffframe, endFlag); // Append the ending flag
    printf("\nFrame after stuffing: %s\n", stuffframe);
    return 0;
}