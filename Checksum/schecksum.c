#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
void checksum(char data[]){
    int i,j,k;
    int c,t;
    int dl=strlen(data),sl;
    int sum[50],f=0;
    char temp[500];

    //s-1:check the sl is a power of 2 or not!!
    //check for correct segment length if not re enter 
    while(1){
         printf("Enter the segment length : ");
        scanf("%d",&sl);

        for(int i=1;i<=sl;i++){
            if((1<<i)==sl){//sl is power of 2 (valid)
                f=1;
                break;  //out from for loop
            }
        }
        if(f)
            break;  //out from while loop
        else{
            printf("The segment length must be power of 2 !");
        }
    }//while ends 

    //s-2:padding of data is must 
    if(dl%sl!=0){ //do padding
        for(i=0;i<sl-(dl%sl);i++){
            temp[i]='0';
        }

        for(j=0;j<dl;j++){
            temp[j+i]=data[j];
        }


        temp[j+i]='\0'; //should be able to know where the data ends 
        strcpy(data,temp);  //should only happen if padding ossours

    }

     
     dl=strlen(data);

    //s-3:compute the checksum:

    for(i=0;i<sl;i++){
        sum[i]=0; //initialized 
    }

    for(i=dl;i>0;i-=sl){
        k=sl-1;
        c=0;
        for(j=i-1;j>=i-sl;j--){
           t=sum[k]+(data[j]-'0')+c;
            sum[k]=t%2;
            c=t/2;
            k--;
        }

    }

    //s-4 : if still carry exists
    while(c){
        for(i=sl-1;i>=0;i--){
            t=c+sum[i];
            sum[i]=t%2;
            c=t/2;
        }
    }

    //s-5:inverse the sum[].append it with the data.
    //inversion
    for(i=0;i<sl;i++){
        if(sum[i]==0)
            sum[i]=1;
        else
            sum[i]=0;
    }

    //appending with the data
    for(i=0;i<sl;i++){
        data[dl+i]=sum[i]+'0';
    }
    data[dl+i]='\0';
}
int main(){
    int sd;int f;
    int cd;
    struct sockaddr_in sad,cad;
    char data[500];
    int sl;

    sd=socket(AF_INET,SOCK_STREAM,0); //socket creation

    sad.sin_family=AF_INET;
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    sad.sin_port=htons(9995);

    bind(sd,(struct sockaddr *)&sad,sizeof(sad));
    listen(sd,10);

    socklen_t len=sizeof(cad);
    cd=accept(sd,(struct sockaddr *)&cad,&len);  //newsocket=cd 

    int n = recv(cd,data,sizeof(data)-1,0);
    data[n]='\0';  //received the data from the client
    //-----------------------------------------------
    printf("The dataword received : ");
    printf("%s",data);
 
    //checksum computation of the data
    checksum(data);  //void checksum only since call by value in c so manipulated in the same data 

    //after checksum evaluation data holds the codeword 
    //send the codeword to the client
    send(cd,data,strlen(data),0);

    close(cd);
    close(sd);

    return 0;
}