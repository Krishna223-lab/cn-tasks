#include <stdio.h>
#include <string.h>

int main()
{
    char s[20], res[40] = "dlestx";
    scanf("%19s", s);
    size_t n = strlen(s);
    int j = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (i + 2 < n && s[i] == 'd' && s[i + 1] == 'l' && s[i + 2] == 'e')
        {
            strcat(res, "dledle");
            i += 2;
        }
        else
        {
            char temp[] = {s[i], '\0'};
            strcat(res, temp);
        }
    }
    strcat(res, "dleetx");
    printf("%s", res);
}