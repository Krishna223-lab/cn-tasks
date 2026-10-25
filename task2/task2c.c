/*
Implement the Selective Repeat ARQ protocol to optimize bandwidth utilization over error-prone channels.
Unlike Go-Back-N, the sender window size equals the receiver window size, and the receiver accepts and buffers out-of-order frames, requesting retransmission only for specific unacknowledged or lost frames.
*/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    bool ack[50] = {false};
    int base = 0;
    while (base < n)
    {
        for (int i = base; i < min(base + k, n); i++)
        {
            if (!ack[i])
            {
                printf("Transmitting frame %d\n", i);
            }
        }
        sleep(1);
        for (int i = base; i < min(base + k, n); i++)
        {
            if (!ack[i])
            {
                int lost = rand() % 10 < 3;
                if (lost)
                {
                    printf("Frame or ACK %d lost.\nRetransmitting\n", i);
                }
                else
                {
                    ack[i] = true;
                    printf("Frame %d received. ACK %d sent.\n", i, i);
                    printf("ACK received\n");
                }
            }
        }
        while (base < n && ack[base])
        {
            base++;
        }
    }
    printf("Done");
}