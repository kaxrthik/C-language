#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void send_frame(int frame_num)
{
    printf("Transmitting Frame %d... \n", frame_num);
}
int wait_for_ACK(int frame_num)
{
    return rand() % 2;
}

int main()
{
    int total_frames, timeout,rtt;
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
        int ack = 0, wait_time = 0;
        while(wait_time < timeout)
        {
            sleep(1);
            wait_time++;
            if(wait_for_ACK(Frame))
            {
                printf("ACK received for frame %d \n", Frame);
                ack = 1;
                break;
            }
            else
            {
                printf("Waiting for ACK on frame %d... \n", Frame);
            }
            if(wait_time>rtt)
            {
                printf("Round trip time limit reached for frame %d\n", Frame);
                break;
            }
        }
        if(!ack)
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