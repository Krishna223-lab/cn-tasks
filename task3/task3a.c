/*
Shortest Routing Protocol -> Dijkstra


*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_EDGES 100
#define MAX_NODES 100

struct Node
{
    int node;
    int wt;
};

struct graph
{
    int node;
    struct Node adj[MAX_EDGES];
    int len;
} g[MAX_NODES];

void dijkstra(int src, int n)
{
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    for (int i = 0; i < n; i++)
    {
        dist[i] = __INT_MAX__;
        visited[i] = false;
    }
    dist[src] = 0;
    for (int it = 0; it < n; it++)
    {
        int min_node = -1;
        int min_dist = __INT_MAX__;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < min_dist)
            {
                min_dist = dist[i];
                min_node = i;
            }
        }

        if (min_node == -1)
            break;

        visited[min_node] = true;
        for (int i = 0; i < g[min_node].len; i++)
        {
            struct Node nei = g[min_node].adj[i];
            if (!visited[nei.node] && dist[min_node] != __INT_MAX__)
            {
                int new_dist = dist[min_node] + nei.wt;
                if (new_dist < dist[nei.node])
                {
                    dist[nei.node] = new_dist;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == __INT_MAX__)
        {
            printf("%d INF\n", i);
        }
        else
        {
            printf("%d %d\n", i, dist[i]);
        }
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        scanf("%d%d%d", &u, &v, &wt);

        g[u].adj[g[u].len++] = (struct Node){v, wt};
        g[v].adj[g[v].len++] = (struct Node){u, wt};
    }

    dijkstra(0, n);
}