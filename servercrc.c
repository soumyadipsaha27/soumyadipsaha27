#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sd, nsd;
    struct sockaddr_in sad, cad;
    socklen_t len = sizeof(cad);

    char recv_codeword[100];

    // Socket creation
    sd = socket(AF_INET, SOCK_STREAM, 0);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9997);
    sad.sin_addr.s_addr = INADDR_ANY;

    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 5);

    printf("Waiting for sender...\n");
    nsd = accept(sd, (struct sockaddr *)&cad, &len);

    // Receive codeword
    recv(nsd, recv_codeword, sizeof(recv_codeword), 0);
    printf("\nReceived CRC dataword from sender : %s\n", recv_codeword);

    // ---------------- RECEIVER CRC PART ----------------

    char data[100], divisor[100];
    char padded[100], crc[100], codeword[100];

    printf("\nEnter the dataword at receiver : ");
    scanf("%s", data);

    printf("Enter the divisor at receiver  : ");
    scanf("%s", divisor);

    strcpy(padded, data);

    int n = strlen(divisor);
    int z = n - 1;

    // Padding zeros
    for (int i = 0; i < z; i++)
        strcat(padded, "0");

    printf("\nReceiver padded dataword : %s\n", padded);

    // CRC Division
    for (int i = 0; i <= strlen(padded) - n; i++) {
        if (padded[i] == '1') {
            for (int j = 0; j < n; j++) {
                padded[i + j] =
                    (padded[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Extract CRC
    strcpy(crc, padded + strlen(padded) - (n - 1));
    printf("Receiver CRC : %s\n", crc);

    // Create receiver codeword
    strcpy(codeword, data);
    strcat(codeword, crc);

    printf("Receiver CRC dataword : %s\n", codeword);

    close(nsd);
    close(sd);
    return 0;
}
