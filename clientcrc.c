#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sd;
    struct sockaddr_in sad, cad;
    sd = socket(AF_INET, SOCK_STREAM, 0);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9997);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    // ---------------- CRC PART ----------------

    char data[100] = {'\0'};
    char divisor[100] = {'\0'};
    char cdata[100] = {'\0'};
    char crc[100] = {'\0'};

    printf("\nEnter the dataword : ");
    scanf("%s", data);

    strcpy(cdata, data);   // copy of data

    printf("\nEnter the divisor : ");
    scanf("%s", divisor);

    int n = strlen(divisor);
    int z = n - 1;   // numbers of zeros need to be padded

    int i = 0;
    for (i = 0; data[i] != '\0'; i++) {
    }

    while (z != 0) {
        data[i++] = '0';
        z--;
    }

    printf("\nThe dataword with padded zeros is : %s\n", data);

    int c;
    for (int idx = 0; idx <= strlen(data) - n; idx++) {
        c = 0;

        if (data[idx] == '0')
            continue;
        else {
            for (int j = idx; j <= (idx + (n - 1)); j++) {
                if (data[j] == divisor[c])
                    data[j] = '0';
                else
                    data[j] = '1';
                c++;
            }
        }
    }

    printf("\nThe crc is : ");

    int f = 0;
    for (int i = strlen(data) - (n - 1); i <= strlen(data) - 1; i++) {
        printf("%c", data[i]);
        crc[f] = data[i];
        f++;
    }

	crc[f]='\0'; //adds null at last

    printf("\n");

    strcat(cdata,crc);
    printf("\nThe crc dataword is : %s\n", cdata);

    // sending the crc + dataword
    send(sd, cdata, strlen(cdata)+1, 0);

    close(sd);
    return 0;

}
