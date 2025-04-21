#include <stdio.h>
#include <stdlib.h>
void leakyBucket(int outputRate, int bucketSize, int totalTime)
{
    int bucketcontent = 0, Time = 1, upper = 200, lower = 1, Remaining_bucket_Content;
    while (Time <= totalTime)
    {
        int incomingpacket = (rand() % (upper - lower + 1)) + lower;
        if (incomingpacket <= (bucketSize - bucketcontent))
        {
            bucketcontent = bucketcontent + incomingpacket;
            if (bucketcontent < 100)
            {
                Remaining_bucket_Content = bucketcontent;
                printf("\nTime step = %d \nIncoming Packet = %d \nTotal bucket Content = %d \nPacket sent = %d\nRemaining bucket Content = %d\n", Time, incomingpacket, bucketcontent, bucketcontent, Remaining_bucket_Content);
            }
            else
            {
                Remaining_bucket_Content = bucketcontent - outputRate;
                printf("\nTime step = %d \nIncoming Packet = %d \nTotal bucket Content = %d \nPacket sent = %d\nRemaining bucket Content = %d\n", Time, incomingpacket, bucketcontent, outputRate, Remaining_bucket_Content);
                bucketcontent = bucketcontent - outputRate;
            }
        }
        else
        {
            printf("\nBUCKET OVERFLOW! \n", incomingpacket);
            Remaining_bucket_Content = bucketcontent - outputRate;
            printf("Time step = %d \nIncoming Packet(DISCARDED) = %d \nTotal bucket Content = %d \nPacket sent = %d\nRemaining bucket Content = %d\n", Time, incomingpacket, bucketcontent, outputRate, Remaining_bucket_Content);
            bucketcontent = bucketcontent - outputRate;
        }
        Time++;
    }
}
int main()
{
    int outputRate, bucketSize, totalTime;
    printf("\nEnter the Output Rate of the bucket: ");
    scanf("%d", &outputRate);
    printf("Enter the Bucket Size: ");
    scanf("%d", &bucketSize);
    printf("Enter the nmuber of time step to simulate: ");
    scanf("%d", &totalTime);
    leakyBucket(outputRate, bucketSize, totalTime);
    return 0;
}