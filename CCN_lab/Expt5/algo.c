#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void leakyBucket(int outputRate, int bucketSize, int totalTime)
{
    int bucketcontent = 0;
    int Time = 0;
    int upper = 200;
    int lower = 1;
    printf("BucketSize = %d | OutputRate=%d\n\n", bucketSize, outputRate);
    while (Time <= totalTime)
    {
        int incomingpacket = (rand() % (upper - lower + 1)) + lower;
        if (incomingpacket <= (bucketSize - bucketcontent))
        {
            bucketcontent = bucketcontent + incomingpacket;
            int Remaining_bucket_Content = bucketcontent - outputRate;
            printf("Time step = %d \nIncoming Packet = %d \nCurrent bucket Content= %d \nPacket sent=%d\nRemaining bucket Content=%d\n", Time, incomingpacket, bucketcontent, outputRate, Remaining_bucket_Content);
            bucketcontent = bucketcontent - outputRate;
        }
        else
        {
            printf("Discarding packet");
            break;
        }
        Time++;
    }
}
int main()
{
    int outputRate, bucketSize, totalTime;
    printf("Enter the Output Rate of the bucket: ");
    scanf("%d", &outputRate);
    printf("Enter the nmuber of time step to simulate: ");
    scanf("%d", &totalTime);
    printf("Enter the Bucket Size ");
    scanf("%d", &bucketSize);
    leakyBucket(outputRate, bucketSize, totalTime);
    return 0;
}