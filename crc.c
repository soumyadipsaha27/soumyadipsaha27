#include <stdio.h>
#include <string.h>

void main() {

    char data[100] = {'\0'};
    char divisor[100] = {'\0'};
    char cdata[100] = {'\0'};
    char crc[100] = {'\0'};

    printf("\nEnter the dataword : %s", data);
    scanf("%s", data);

    strcpy(cdata, data);   // copy of data

    printf("\nEnter the divisor : %s", divisor);
    scanf("%s", divisor);

    int n = strlen(divisor);
    int z = n - 1;   // number of zeros need to be padded

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

    printf("\n");

    strcat(cdata, crc);
    printf("\nThe crc dataword is : ");
    for (int idx = 0; idx < strlen(cdata); idx++)
        printf("%c", cdata[idx]);
}
