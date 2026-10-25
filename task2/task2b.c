/*
In Go Back ARQ (Sliding Window Protocol)
sender window size is k and receiver window size is 1
out of order frames are not accepted
sender sends k elements at once into the channel



*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int base = 0;
    int next = 0;

    while (base < n)
    {
        while (next < base + k && next < n)
        {
            printf("Transmitting frame %d\n", next);
            next++;
        }
        sleep(1);
        int packet_lost = (rand() % 10 < 3);
        if (packet_lost)
        {
            printf("Frame %d lost. Retransmitting...\n", base);
            next = base;
        }
        else
        {
            printf("Frame %d received.\n", base);
            printf("ACK received.\n");
            base++;
        }
    }
    printf("Done");
}