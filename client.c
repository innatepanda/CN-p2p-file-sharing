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

/*struct clientinfo
{
	char username[50];
	char password[50];
	//char uid[10];
	char filename[50]; 
	int filenum;
	int filesize;
	int choice;
	
};
struct fileinfo
{
	char username[50];
	char filename[50];
	char filesize[50];
	int filenum;
	int choice;
	int status;
	
};*/
struct clientinfo
{
	char username[50];
	char password[50];
	int choice;
	time_t date[50]; //at time of reg, server assigns
	
};
struct fileinfo
{
	char username[50];
	char filename[50];
	int filesize;
	int filenum;
	int choice;
	int status;
	
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
  
   const char *unm = (*env)->GetStringUTFChars(env, un,  NULL) ;
   const char *pwd = (*env)->GetStringUTFChars(env, pd,NULL ) ;
   
   struct clientinfo client;
			
   strcpy(client.username,unm);
   strcpy(client.password,pwd);
   //strcpy(client.filename,fname);
   client.choice=choice;
   //client.filesize=fs;
   
   //client.filenum=fno;
   printf("\nOn client side\nUser info %s , %s , %d\n",client.username,client.password, client.choice);
   //printf("File info %s , %d , %d\n\n",client.filename,client.filesize, client.filenum);		
   sen=send(sockfd,(struct clientinfo *) &client, sizeof(client), 0); //sending login details
   
   if(client.choice==-1)
   {
	   exit(0);
   }
   else
   {
   	rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   	rec_msg[rec]='\0';
   	printf("rec msg: %s",rec_msg);		
	   
 	return  (*env)->NewStringUTF(env, rec_msg); 
 }
	         
}

JNIEXPORT jstring JNICALL Java_Gui_Files
  (JNIEnv *env, jobject obj,jstring user, jstring fn, jint fs,jint fno, jint choice)
{
    
   const char *fname = (*env)->GetStringUTFChars(env, fn,  NULL) ;
    struct fileinfo client;
			
   strcpy(client.username,user);
   strcpy(client.filename,fname);
   client.choice=choice;
   client.filesize=fs;
   
   client.filenum=fno;
   printf("\nOn client side\nUser info %s , %s , %d\n",client.username, client.choice);
   printf("File info %s , %d , %d\n\n",client.filename,client.filesize, client.filenum);	
   rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   rec_msg[rec]='\0';
   printf("rec msg: %s",rec_msg);		
	   
	return  (*env)->NewStringUTF(env, rec_msg);	
			

}













