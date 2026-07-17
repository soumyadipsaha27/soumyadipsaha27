#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(){

int cd,sd;
char data[100];
struct sockaddr_in cad,sad;
socklen_t cadl;

 sd=socket(AF_INET,SOCK_STREAM,0);

 sad.sin_family=AF_INET;
 sad.sin_port=htons(9995);
 sad.sin_addr.s_addr=inet_addr("127.0.0.1");

 bind(sd,(struct sockaddr *)&sad,sizeof(sad));
 listen(sd,10);

 printf("\nwaiting for client.....\n");
 cadl=sizeof(cad);

 cd=accept(sd,(struct sockaddr *)&cad,&cadl);
//---------------------------------------------------
int n=recv(cd,data,sizeof(data)-1,0);
data[n]='\0';

 int ch;
 printf("Enter the choice : (0=even,1=odd)");
 scanf("%d",&ch);

int i;
int c=0;
for(i=0;data[i]!='\0';i++){
    if(data[i]=='1'){
        c++;
    }
}

if(ch==0){  //choice is even
    if(c%2!=0){  //c is odd
        data[i]='1';
        i++;

    }
    else{
        data[i]='0';
        i++;
    }

}
else if(ch!=1){ //choice is odd
    if(c%2==0){ //c is even
        data[i]='1';
        i++;
    }
     else{
        data[i]='0';
        i++;
    }
}

data[i]='\0';
printf("The codeword is : %s ",data);

send(cd,data,strlen(data)+1,0);  //to the client

//---------------------------------------------------

close(cd);
close(sd);
return 0;


}