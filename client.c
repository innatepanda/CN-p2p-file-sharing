#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

struct clientinfo
{
	char username[50];
	char password[50];
	char filename[50];
	int status; // 1-online  0-offline 
	
};

struct signup
{
	char username[50];
	char password[50];
	char filename[50]; 
	int filenum;
	
};

struct login
{
	char username[50];
	char password[50];
};

int main(int argc,char *argv[])
{
	char cliIP[16];int cliPort;
	char serIP[16];int serPort;
	int connvar,sockfd;
	int rec,sen;
	char rec_msg[500],sent_msg[500],menu[500];
	char unm[50],pwd[50],fnm[50];
	int a= atoi(argv[1]);
	
/****************************  SOCKET API  **********************************/

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
                   printf("Socket creation failed...\n");
                   exit(1);
	}
	else
	{
	    printf("Socket created successfully...\n");
		
/****************************  CONNECT API  ***********************************/

                   struct sockaddr_in server;
                   struct sockaddr_in client;
                   server.sin_family=AF_INET;
	    server.sin_port=htons(a);
                   server.sin_addr.s_addr=INADDR_ANY;
                   connvar=connect(sockfd,(const struct sockaddr *)(&server),sizeof(server));
                   if(connvar==-1)
                   {
	        printf("Connect failed...\n");
	        exit(1);
	    }
                   else
                   {
	        int slen= sizeof(server);
	        getpeername(sockfd,(struct sockaddr *)(&server),&slen);
	        inet_ntop(AF_INET,&server.sin_addr,serIP,sizeof(serIP));
	        serPort=ntohs(server.sin_port);
	        printf("Connected to the server at IP address %s and port no %d...\n",serIP,serPort);
			
	        rec=recv(sockfd, menu, sizeof(menu), 0);
	        menu[rec]='\0';
	       while(1){
	        printf("%s",menu);
			
				
	        printf("\nEnter choice: ");
	        scanf("%s",sent_msg); //OR  gets(sent_msg);
                       sen=send(sockfd, sent_msg, strlen(sent_msg), 0); 
                       //sending choice 0(signup) or 1(login)
                       
                       rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0);
	        rec_msg[rec]='\0';
	        printf("%s",rec_msg);
				
/****************************  SIGNUP  ****************************************/
			
	        if(strcmp(sent_msg,"0")==0)
	        {
	           int num,n;
	           printf("Enter username: ");
	           scanf("%s",unm);
	           printf("Enter password: ");
	           scanf("%s",pwd);
	           printf("Enter the no of files you want to add: ");
	           scanf("%d",&num);
	           struct signup new[num];
					
	           for(n=0;n<num;n++)
	           {
		printf("Enter filename: ");
	               scanf("%s",fnm);
		strcpy(new[n].username,unm);
	               strcpy(new[n].password,pwd);
	               strcpy(new[n].filename,fnm);
	               new[n].filenum = num;
					
	           }
	           sen=send(sockfd, new, sizeof(new), 0); //sending signup details
	           rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
	           //receiving confirmation message
					
	           rec_msg[rec]='\0';
	           
	           printf("%s",rec_msg);
					
	           //close(sockfd);
	          // printf("Closed the connection with the server\n");
	           //exit(1);
	          //continue;
	       }
/****************************  LOGIN  ************************************/
				
	       else if(strcmp(sent_msg,"1")==0)
	       {				  
				
	           printf("Enter username: ");
	           scanf("%s",unm);
	           printf("Enter password: ");
	           scanf("%s",pwd);
	           struct login client[1];
				
	           strcpy(client[0].username,unm);
	           strcpy(client[0].password,pwd);
				
	           sen=send(sockfd, client, sizeof(client), 0); //sending login details
	           //printf("\namia\n");
	           rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
	           //receiving confirmation or error message
	           rec_msg[rec]='\0';
	          // printf("\n%s\n",rec_msg);		
	            if(strcmp(rec_msg,"nf")==0)
	           {
	              printf("Incorrect username( %s ) or password( %s ). Please try again\n ",client[0].username,client[0].password);
	           }
	           else //if(strcmp(rec_msg,"f")==0)
	           {
	               printf("\nsuccessfully logged in\n");
	               int num,n;
		//rec=recv(sockfd,rec_msg,sizeof(rec_msg),0);
		//rec_msg[rec]='\0';
		//printf("%s",rec_msg);
		//printf("\namia\n");			
		int check = -1;
		while(check != 0)
	               {
		  printf("1 to SEARCH\n2 to ADD FILES\n3 to DELETE files\n0 to LOGOUT\nEnter choice :");
	                 scanf("%s",sent_msg);
		  sen=send(sockfd,sent_msg,sizeof(sent_msg),0);
		  check=atoi(sent_msg);		  	
		 switch(check)
	                {
		  case 1: rec=recv(sockfd,rec_msg,sizeof(rec_msg),0);
	                         rec_msg[rec]='\0';
	                         printf("%s\n",rec_msg);
	                         scanf("%s",fnm); //enter name of file to search for
		          sen=send(sockfd,fnm,strlen(fnm),0);
	                         rec=recv(sockfd,rec_msg,sizeof(rec_msg),0); 
	                         //receiving found or not found
	                         // printf("\nlist of active user having the file:\n");
	                         printf("%s\n",rec_msg);
		          break;
	                 
	                 case 2: printf("Enter the no of files you want to add: ");
		          scanf("%d",&num);
		          struct signup new2[10];
		          for(n=0;n<num;n++)
		          {
		            printf("Enter filename: ");
		            scanf("%s",fnm);
		            strcpy(new2[n].username,client[0].username);
		            strcpy(new2[n].password,client[0].password);
		            strcpy(new2[n].filename,fnm);
		            new2[n].filenum= num;
					
		          }
		          sen=send(sockfd, new2, sizeof(new2), 0); 
		          //sending new file details
		          rec=recv(sockfd, rec_msg, strlen(rec_msg), 0); 
		          //receiving confirmation message
		          rec_msg[rec]='\0';
		          printf("%s",rec_msg);
		          break;
	                 
	                 case 3: rec=recv(sockfd,rec_msg,sizeof(rec_msg),0);
		          rec_msg[rec]='\0';
		          printf("%s\n",rec_msg);
		          scanf("%s",fnm);
	                         sen=send(sockfd,fnm,strlen(fnm),0); 
	                         //sending filename to be deleted
		          rec=recv(sockfd,rec_msg,sizeof(rec_msg),0); 
		          //receiving confirmation or error message
		         
		          printf("%s\n",rec_msg);
		          break;
		  
		  case 0: rec=recv(sockfd,rec_msg,sizeof(rec_msg),0); 
		          //receiving confirmation message for logout
		          rec_msg[rec]='\0';
	                         printf("%s\n",rec_msg);
		          break;
	                }
			  	
			  	
	             }
					
	          }
	          
				
	        //close(sockfd);
	        //printf("Closed the connection with the server\n");
	       // exit(1);
	    }
	    else if(strcmp(sent_msg,"-1")==0)
	    {
	      printf("\nApplication closed!\n");
	      close(sockfd);
	      exit(1);
	    }
	    

/*******************INVALID CHOICE******************************/
                   else
	    {
	       printf("Invalid choice\n");
	      // close(sockfd);
	      // printf("Closed the connection with the server\n");
	      // exit(1);
	    }
              }
             }
          }	
     return 0;	

}
