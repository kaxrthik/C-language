#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 100

int window_size, total_frames;

// Function to simulate sending a frame
void send_frame(int frame_number) 
{
    printf("Sent Frame %d\n", frame_number);
}

// Function to simulate receiving an acknowledgment
int receive_ack(int frame_number)
{
    return (rand() % 10) < 7; // 70% chance of successful ACK
}

// Function to simulate frame loss
int frame_lost(int frame_number) 
{
    return (rand() % 10) < 2; // 20% chance of frame loss
}

int main() 
{
    int base = 0;           // Base of the sliding window
    int next_frame = 0;     // Next frame to send

    printf("Enter total frames to send: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    srand(time(NULL));

    while (base < total_frames) 
    {
        // Send frames within the window
        while (next_frame < base + window_size && next_frame < total_frames) 
        {
            send_frame(next_frame);
            next_frame++;
        }

        // Wait for acknowledgments
        sleep(2);

        while (base < next_frame) 
        {
            if (frame_lost(base)) 
            {
                printf("Frame %d lost. Resending window from Frame %d...\n", base, base);
                next_frame = base; // Reset next_frame to resend from the base
                break;
            } 
            else if (receive_ack(base)) 
            {
                printf("ACK received for Frame %d\n", base);
                base++; // Move the window forward
            } 
            else 
            {
                printf("ACK lost for Frame %d. Resending from Frame %d...\n", base, base);
                next_frame = base; // Resend from the base
                break;
            }
        }
    }

    printf("All frames sent successfully!\n");
    return 0;
}
