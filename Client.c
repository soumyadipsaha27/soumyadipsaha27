#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sd, cadl;
    struct sockaddr_in sad, cad;

    sd = socket(AF_INET, SOCK_STREAM, 0);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9997);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    // -------------------------------------------------

    char inp[100] = {'\0'};
    printf("Enter the user provided dataword : ");
    scanf("%s", inp);

    int count = 0;
    int i = 0;

    for(i = 0; inp[i] != '\0'; i++)
    {
        if(inp[i] == '1')
            count += 1;
    }

    // -------- Even parity --------
    if(count % 2 == 0)
    {
        inp[i] = '0';
        printf("\nEven parity codeword : %s", inp);
    }
    else
    {
        inp[i] = '1';
        printf("\nEven parity codeword : %s", inp);
    }

    send(sd, inp, sizeof(inp), 0);   // sending even parity dataword

    // -------- Odd parity --------
    if(count % 2 == 0)
    {
        inp[i] = '1';
        printf("\nOdd parity codeword : %s", inp);
    }
    else
    {
        inp[i] = '0';
        printf("\nOdd parity codeword : %s", inp);
    }

    printf("\n");

    close(sd);
}

