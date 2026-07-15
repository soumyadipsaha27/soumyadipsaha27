#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

int main()
{
    int sd, cd, cadl;
    struct sockaddr_in sad, cad;   // stores ip and port number
    char str[100];

    sd = socket(AF_INET, SOCK_STREAM, 0);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9997);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 1);

    cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);

    printf("waiting for client...\n");

    recv(cd, str, sizeof(str), 0);
    printf("\nFrom client side,the received dataword is : %s", str);

    // -------------------------------------------------------

    char data[50], data1[50];
    int t, c, k, d, l, s, l1, j = 0, sum[50], a;

    strcpy(data, str);    // copying the data
    d = strlen(data);

    while (1)
    {
        printf("\nenter the segment length:\n");
        scanf("%d", &s);

        for (l = 1; l <= s / 2; l++)
        {
            if (pow(2, l) == s)
            {
                j = 1;
                break;
            }
        }

        if (j == 1)
            break;
        else
            printf("\n segment length must be in pow of 2");
    }

    if (d % s != 0)
    {
        l1 = s - (d % s);

        for (j = 0; j < l1; j++)
            data1[j] = '0';

        data1[j] = '\0';
        strcat(data1, data);
        strcpy(data, data1);
        d = d + l1;
    }

    printf("\n%s\n", data);

    for (l = 0; l < s; l++)
        sum[l] = 0;

    for (l = 0; l < strlen(data); l = l + s)
    {
        c = 0;
        k = s - 1;

        for (j = s + l - 1; j >= l; j--)
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

    printf("\nchecksum=");
    for (l = 0; l < s; l++)
    {
        if (sum[l] == 0)
            sum[l] = 1;
        else
            sum[l] = 0;

        printf("%d", sum[l]);
        data[d + l] = sum[l] + 48;
    }

    data[d + l] = '\0';

    // printf("\nserver side code word is : %s\n", data);
	/* -------- CHECKSUM VERIFICATION -------- */

int error = 0;

for (l = 0; l < s; l++)
{
    if (sum[l] != 0)
    {
        error = 1;
        break;
    }
}

if (error == 0)
    printf("\nCodeword is ACCEPTED (No Error Detected)\n");
else
    printf("\nCodeword is REJECTED (Error Detected)\n");

/* --------------------------------------- */




    close(cd);
    close(sd);
}
