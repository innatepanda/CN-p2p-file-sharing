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
#include "Gui.h"

struct clientinfo
{
	char username[50];
	char password[50];
	//char uid[10];
	char filename[50];
	int filenum;
	int status; // 1-online  0-offline 
	int choice;
	
};

char cliIP[16];int cliPort;
char serIP[16];int serPort;
int connvar,sockfd;
int rec,sen;
char rec_msg[500],sent_msg[500],menu[500];
char unm[50],pwd[50],fnm[50];



JNIEXPORT jint JNICALL Java_Gui_Cmain
  (JNIEnv *env, jobject obj){
	
	
/****************************  SOCKET API  **********************************/

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
                   printf("Socket creation failed...\n");
                   return 0;
	}
	else
	{
	    printf("Socket created successfully...\n");
		
/****************************  CONNECT API  ***********************************/

                   struct sockaddr_in server;
                   struct sockaddr_in client;
                   server.sin_family=AF_INET;
	           server.sin_port=htons(4000);
                   server.sin_addr.s_addr=INADDR_ANY;
                   connvar=connect(sockfd,(const struct sockaddr *)(&server),sizeof(server));
                   if(connvar==-1)
                   {
	               printf("Connect failed...\n");
	               return 0;
	           }
                   else
                   {
	               int slen= sizeof(server);
	               getpeername(sockfd,(struct sockaddr *)(&server),&slen);
	               inet_ntop(AF_INET,&server.sin_addr,serIP,sizeof(serIP));
	               serPort=ntohs(server.sin_port);
	               printf("Connected to the server at IP address %s and port no %d...\n",serIP,serPort);
			
	              
	               return 1;
	            }

     }

}

JNIEXPORT jstring JNICALL Java_Gui_Auth
  (JNIEnv *env, jobject obj, jstring un, jstring pd, jint choice) {
    printf("Auth"); 
    //jboolean isCopy;
    
    const char *unm = (*env)->GetStringUTFChars(env, un,  NULL) ;
    const char *pwd = (*env)->GetStringUTFChars(env, pd,NULL ) ;
    printf("Auth1 %s , %s , %d\n",unm,pwd,choice); 
   // main();
       
	         //  return  (*env)->NewStringUTF(env, rec_msg);
	       
	         struct clientinfo client;
				
	           strcpy(client.username,unm);
	           strcpy(client.password,pwd);
                   client.choice=choice;
                   printf("choice %s , %d",client.username, client.choice);	
	           sen=send(sockfd,(struct clientinfo *) &client, sizeof(client), 0); //sending login details
	           rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
	           //receiving confirmation or error message
	           rec_msg[rec]='\0';
	           printf("%s",rec_msg);		
	           /* if(strcmp(rec_msg,"nf")==0)
	           {
	              printf("%s, %s", client.username, client.password);
	              return "Incorrect username or password. Please try again";
	           }
	           else
	           {
	             return "Login successful";
	           }*/
	 return  (*env)->NewStringUTF(env, rec_msg);
	         
}















