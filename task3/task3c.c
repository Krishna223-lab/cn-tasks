#include <stdio.h>

int main()
{
    int capacity, rate, tokens, n;
    int queue = 0;
    scanf("%d%d%d%d", &capacity, &rate, &tokens, &n);
    // printf("%d\n", rate);
    int packets[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &packets[i]);
    }
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        tokens += rate;
        if (tokens > capacity)
        {
            tokens = capacity;
        }
        printf("Time %d: Packet %d of size %d incoming\n", time, i, packets[i]);
        queue += packets[i];
        if (tokens >= queue)
        {
            tokens -= queue;
            queue = 0;
        }
        else
        {
            queue -= tokens;
            tokens = 0;
        }
        printf("Queue: %d and Tokens in Bucket: %d\n\n", queue, tokens);
        time++;
    }
    while (queue)
    {
        tokens += rate;
        if (tokens > rate)
        {
            tokens = capacity;
        }
        if (tokens >= queue)
        {
            tokens -= queue;
            queue = 0;
        }
        else
        {
            queue -= tokens;
            tokens = 0;
        }
        printf("Time %d:\n", time);
        printf("Queue: %d and Tokens in Bucket: %d\n\n", queue, tokens);
        time++;
    }
    return 0;
}