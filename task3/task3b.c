#include <stdio.h>
#define INF 99999

struct Router
{
    int dist[20];
    int from[20];
} rt[20];

struct Edge
{
    int u, v, w;
};

int main()
{
    int n, e;
    scanf("%d%d", &n, &e);
    struct Edge edges[e];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rt[i].dist[j] = INF;
            rt[i].from[j] = -1; // -1 means no route yet
        }
        rt[i].dist[i] = 0; // Distance to self is always 0
        rt[i].from[i] = i; // Next hop to self is self
    }
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

        // Populate the initial direct link for the source router
        rt[edges[i].u].dist[edges[i].v] = edges[i].w;
        rt[edges[i].u].from[edges[i].v] = edges[i].v;
    }
    for (int step = 0; step < n - 1; step++)
    {
        for (int i = 0; i < e; i++)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;

            for (int src = 0; src < n; src++)
            {
                if (rt[src].dist[u] == INF)
                    continue;
                if (rt[src].dist[v] > rt[src].dist[u] + w)
                {
                    rt[src].dist[v] = rt[src].dist[u] + w;
                    rt[src].from[v] = rt[src].from[u];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nRouting Table for Router %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < n; j++)
        {
            if (rt[i].dist[j] == INF)
            {
                printf("Node %d\t\t-\t\tINF\n", j);
            }
            else
            {
                printf("Node %d\t\tNode %d\t\t%d\n", j, rt[i].from[j], rt[i].dist[j]);
            }
        }
    }
}