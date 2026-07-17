#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(){
int sd,cd;
socklen_t cdl;
char data[100];
struct sockaddr_in sad,cad;

sd=socket(AF_INET,SOCK_STREAM,0);

sad.sin_family=AF_INET;
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
sad.sin_port=htons(9995);

bind(sd,(struct sockaddr*)&sad,sizeof(sad));
listen(sd,10);

printf("\nserver is waiting...\n");

cdl=sizeof(cad);

cd=accept(sd,(struct sockaddr*)&cad,&cdl);

while(1){

int n=recv(cd,data,sizeof(data)-1,0);

if(n<=0)
	break;

data[n]='\0';

printf("client says : %s\n",data);

if(strcmp(data,"bye")==0)
break;

printf("Enter the message : ");
scanf(" %[^\n]",data);
send(cd,data,strlen(data)+1,0);



}


close (cd);
close (sd);

return 0;

}



