/*
simplex protocol :

simply send a single frame and receive a single frame (send signal)
once received : send an ack signal

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n;
    scanf("%d", &n);
    int frame = 1;
    while (frame <= n)
    {
        printf("Sender: Sent frame %d\n", frame);
        sleep(1); // simulating network delay
        int frame_lost = (rand() % 10) < 3;
        if (frame_lost)
        {
            printf("Channel: Frame %d lost.\nSender: Retransmitting...\n", frame);
            continue;
        }
        printf("Receiver: Received frame %d\n", frame);
        printf("Receiver: Sent ACK signal\n");
        sleep(1); // simulating network delay
        int ack_lost = (rand() % 10) < 3;
        if (ack_lost)
        {
            printf("Channel: Ack %d lost.\nSender: Retransmitting...\n", frame);
            continue;
        }
        printf("Sender: Ack received\n");
        frame++;
    }
    printf("Sender:All frames sent to receiver");
}