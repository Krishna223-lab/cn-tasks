/*
Character Count Framing method
In data communications, the Character Count framing method uses a field at the beginning of each frame to specify the total number of characters (bytes) contained within that frame.
The receiver reads this count header to determine where the frame ends and the next frame begins.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    char a[n][50];
    for (int i = 0; i < n; i++)
    {
        scanf(" %[^\n]", a[i]);
    }

    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < strlen(a[i]); j++)
        {
            if (a[i][j] != ' ')
            {
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
}