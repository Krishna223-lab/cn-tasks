/*
Bit Stuffing
lets say s = "1001111101" is sent
then since there are 5 consecutive 0s append a 0 in middle
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char a[20];
    scanf("%19s", a);
    size_t n = strlen(a);
    int count = 0;
    char b[20];
    int j = 0;
    for (size_t i = 0; i < n; i++)
    {
        count = (a[i] == '0') ? 0 : count + 1;
        b[j++] = a[i];
        if (count == 5)
        {
            b[j++] = '0';
            count = 0;
        }
    }
    b[j] = '\0';
    printf("Stuffed string: %s", b);
}