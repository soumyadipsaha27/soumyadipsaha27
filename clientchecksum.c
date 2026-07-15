#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

int main()
{
    int sd, cadl;
    struct sockaddr_in sad, cad;

    sd = socket(AF_INET, SOCK_STREAM, 0);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9997);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    // -------------------------------------------------------

    char data[50], data1[50];
    int t, c, k, d, s, l, l1, i, j = 0, sum[50], a;
    printf("enter the the data\n");
    scanf("%s", data);

    d = strlen(data);

    while (1)
    {
        printf("enter the segment length\n");
        scanf("%d", &s);

        for (i = 1; i <= s / 2; i++)
        {
            if (pow(2, i) == s)
            {
                j = 1;
                break;
            }
        }

        if (j == 1)
            break;
        else
            printf("\nsegment length must be in pow of 2\n");
    }

    if (d % s != 0)
    {
        i = s - (d % s);

        for (j = 0; j < i; j++)
            data1[j] = '0';

        data1[j] = '\0';
        strcat(data1, data);
        strcpy(data, data1);
        d = d + i;
    }

    //printf("\n%s\n", data);

    for (i = 0; i < s; i++)
        sum[i] = 0;

    for (i = 0; i < strlen(data); i = i + s)
    {
        c = 0;
        k = s - 1;

        for (j = s + i - 1; j >= i; j--)
        {
            a = (data[j] - 48);
            t = sum[k] + a + c;
            sum[k] = t % 2;
            c = t / 2;
            k--;
        }

        if (c == 1)
        {
            for (j = s - 1; j >= 0; j--)
            {
                t = sum[j] + c;
                sum[j] = t % 2;
                c = t / 2;
            }
        }
    }

    //for (i = 0; i < s; i++)
        //printf("%d", sum[i]);

    printf("\nchecksum=");
    for (i = 0; i < s; i++)
    {
        if (sum[i] == 0)
            sum[i] = 1;
        else
            sum[i] = 0;

        printf("%d", sum[i]);
        data[d + i] = sum[i] + 48;
    }

    data[d + i] = '\0';

    printf("\ncode word is : %s\n", data);

    send(sd, data, sizeof(data), 0);   // sending the data + checksum
    close(sd);
}
