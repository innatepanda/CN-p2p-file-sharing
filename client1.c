#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void main()
{
    
    
    char buffer[1024];

    int r = socket(PF_INET, SOCK_STREAM, 0);
    if(r!=-1){
    printf("Socket Created Sucessfully.\n");
    }
    else{exit(1);}
  
    int t, m;
    printf("enter port:");
    scanf("%d", &t);
    struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(t);
	//server.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_addr.s_addr = INADDR_ANY;
	int f1=bind(r,(const struct sockaddr *)&client,sizeof(client));
	if(f1==-1)
	{
		printf("Bind unsuccessful\n");
		exit(1);
	}
	else{
		printf("Bind created\n");
	}
    
    printf("enter port:");
    scanf("%d", &m);


    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    
    serverAddr.sin_port = htons(m);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int r1=connect(r, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(r1==-1){
    printf("\nconnection error");
    exit(1);}
    

    
    
}
