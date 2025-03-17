#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int window_size, total_frames;

void send_frame(int frame) 
{
    printf("Sent Frame %d... \n", frame);
}

int receive_ack(int frame) 
{
    return rand() % 2; // Simulating random ACK loss (50% probability)
}

int main() 
{
    int base = 0;
    int next_frame = 0;
    int ack_received;
    
    printf("Enter total frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    srand(time(NULL)); // Seed for random ACK loss simulation

    while (base < total_frames) {
        // Sending frames in the window
        while (next_frame < base + window_size && next_frame < total_frames) 
        {
            send_frame(next_frame);
            next_frame++;
        }

        sleep(2); // Simulating transmission delay

        ack_received = 1; // Assume all frames are acknowledged initially

        // Checking acknowledgments for sent frames
        for (int i = base; i < next_frame; i++) 
        {
            if (receive_ack(i)) 
            {
                printf("ACK received for Frame %d\n", i);
                base++; // Move base forward if ACK received
            } 
            else 
            {
                printf("ACK lost for Frame %d. Resending from Frame %d...\n", i, base);
                next_frame = base; // Reset next_frame to resend unacknowledged frames
                ack_received = 0; // Mark that not all frames were acknowledged
                break; // Stop and resend lost frames
            }
        }
    }

    printf("All frames sent successfully!\n");
    return 0;
}
