#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 100

int window_size, total_frames;

// Function to simulate sending a frame
void send_frame(int frame_number) {
    printf("Sent Frame %d\n", frame_number);
}

// Function to simulate receiving an acknowledgment
int receive_ack(int frame_number) {
    return (rand() % 10) < 7; // 70% chance of successful ACK
}

// Function to simulate frame loss
int frame_lost(int frame_number) {
    return (rand() % 10) < 2; // 20% chance of frame loss
}

int main() {
    int base = 0;
    int next_frame = 0;
    int ack_received;

    printf("Enter total frames to send: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    srand(time(NULL));

    while (base < total_frames) 
    {
        while (next_frame < base + window_size && next_frame < total_frames)
        {
            if (frame_lost(next_frame)) 
            {
                printf("Frame %d Lost. Resending from Frame %d...\n", next_frame, base);
                next_frame = base; // Reset next_frame and resend window
                break;
            }
            else 
            {
                send_frame(next_frame);
                next_frame++;
            }
        }

        if(next_frame > base) // only wait for ack if frames were sent.
        {
          sleep(2);

          ack_received = 0;
          for (int i = base; i < next_frame; i++) 
          {
              if (receive_ack(i)) 
              {
                  printf("ACK received for Frame %d\n", i);
                  ack_received = 1;
                  base++;
              } else 
              {
                  printf("ACK lost for Frame %d. Resending from Frame %d...\n", i, base);
                  next_frame = base;
                  break;
              }
          }
        }
    }
    printf("All frames sent successfully!\n");
    return 0;
}