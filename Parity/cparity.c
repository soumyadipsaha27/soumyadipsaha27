#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(){

int sd;
char data[100];
struct sockaddr_in sad;

 sd=socket(AF_INET,SOCK_STREAM,0);

 sad.sin_family=AF_INET;
 sad.sin_port=htons(9995);
 sad.sin_addr.s_addr=inet_addr("127.0.0.1");

 connect(sd,(struct sockaddr *)&sad,sizeof(sad));

 //------------------------------------------------
 printf("Enter the dataword : ");
 scanf(" %[^\n]",data);

 int ch;
 printf("Enter the choice : ");
 scanf("%d",&ch);

 send(sd,data,strlen(data)+1,0); //to server
 
 int n=recv(sd,data,sizeof(data)-1,0);
 printf("Received codeword from server : \n");
 printf("%s",data);
 data[n]='\0';

 int i;
 int c=0;
 for(int i=0;data[i]!='\0';i++){
    if(data[i]=='1'){
        c++;
    }
 }

 if(c%2!=0 && ch!=0){
    printf("codeword accepted!");
 }else if(c%2==0 && ch==0){
    printf("codeword accepted!");
 }else{
    printf("Codeword Rejected!!");
 }

 //--------------------------------------

 close(sd);
 return 0;
}