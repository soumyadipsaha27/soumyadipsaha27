#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>


int main(){
int sd;
char data[100];
struct sockaddr_in sad;

sd=socket(AF_INET,SOCK_STREAM,0);

sad.sin_family=AF_INET;
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
sad.sin_port=htons(9995);

connect(sd,(struct sockaddr*)&sad,sizeof(sad));

while(1){
    
 printf("Enter your message : ...");
	scanf(" %[^\n]",data);

send(sd,data,strlen(data)+1,0);



int n=recv(sd,data,sizeof(data)-1,0);
if(n<=0)
break;
data[n]='\0';

if(strcmp(data,"bye")==0)
	break;

printf("server says : %s\n",data);

}

close(sd);

return 0;

}



