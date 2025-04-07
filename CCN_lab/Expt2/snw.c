#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void send_frame(int frame_num)
{
    printf("Transmitted Frame %d... \n", frame_num);
}

// Simulate transmission outcome
// 0 = Success, 1 = ACK lost, 2 = Frame lost
int simulate_outcome()
{
    return rand() % 3;
}

int main()
{
    int total_frames, timeout, rtt;
    printf("Enter the number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter round trip time (in seconds): ");
    scanf("%d", &rtt);
    printf("Enter time out duration (in seconds): ");
    scanf("%d", &timeout);

    srand(time(NULL));

    int Frame = 0;
    while(Frame < total_frames)
    {
        send_frame(Frame);
        int outcome = simulate_outcome(); // Decide what happens AFTER sending
        int ack = 0, wait_time = 0;

        if (outcome == 2) // Frame lost
        {
            printf("Frame %d was lost during transmission.\n", Frame);
        }
        else
        {
            while (wait_time < timeout)
            {
                sleep(1);
                wait_time++;

                if (outcome == 1) // ACK lost
                {
                    printf("Waiting for ACK on frame %d... \n", Frame);
                    if (wait_time == rtt)
                    {
                        printf("ACK lost for Frame %d.\n", Frame);
                        break;
                    }
                }
                else if (outcome == 0) // Successful ACK
                {
                    printf("ACK received for frame %d \n", Frame);
                    ack = 1;
                    break;
                }
            }
        }

        if (!ack)
        {
            printf("Timeout! Retransmitting Frame %d...\n", Frame);
        }
        else
        {
            Frame++;
        }
    }

    printf("All frames transmitted successfully.\n");
    return 0;
}
