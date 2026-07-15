#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

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

    listen(sd, 5);
    cadl = sizeof(cad);

    cd = accept(sd, (struct sockaddr *)&cad, &cadl);

    recv(cd, str, sizeof(str), 0);

    printf("\nEven parity codeword : %s", str);

    // -----------------------------------------------------

    char inp[100] = {'\0'};
    printf("\nEnter the server side, user provided dataword : ");
    scanf("%s", inp);

    int count = 0;
    int i = 0;
    int m = 0;

    for(i = 0; inp[i] != '\0'; i++)
    {
        if(inp[i] == '1')
            count += 1;
    }

    printf("\nEnter the choice (0 for even parity check / 1 for odd parity check) : ");
    scanf("%d", &m);

    if(m == 0)   // even parity entered
    {
        if(count % 2 == 0)
            printf("\nCorrect data word !");
        else
            printf("\nIncorrect data word !");
    }
    else if(m == 1)   // odd parity entered
    {
        if(count % 2 == 1)
            printf("\nCorrect data word !");
        else
            printf("\nIncorrect data word !");
    }

    // -----------------------------------------------------

    close(cd);
    close(sd);
}

