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

//0-reg, 1-login, 2-add file, 3-search, 4-del file, 5-logout, -1 - err logout
struct clientinfo
{
	char username[50];
	char password[50];
	time_t date[50]; //at time of reg, server assigns
	
};
struct fileinfo
{
	char username[50];
	char filename[50][50];
	char filepath[50][50];
	int filesize[50];
	int filenum;
	int status;
	
};

char cliIP[16];int cliPort;
char serIP[16];int serPort;
int connvar,sockfd;
int rec,sen;
char rec_msg[500],sent_msg[500];
//char unm[50],pwd[50],fnm[50];
int userChoice;


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
   userChoice=choice;
   //client.filesize=fs;
   
   //client.filenum=fno;
   printf("\nOn client side\nUser info %s , %s , %d\n",client.username,client.password, choice);
   //printf("File info %s , %d , %d\n\n",client.filename,client.filesize, client.filenum);	
   sen=send(sockfd, &userChoice, sizeof(userChoice), 0);	
   
   if(userChoice==-1)
   {
	   exit(0);
   }
   else
   {
   	sen=send(sockfd,(struct clientinfo *) &client, sizeof(client), 0); //sending login details
   
   	rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   	rec_msg[rec]='\0';
   	printf("rec msg: %s",rec_msg);		
	   
 	return  (*env)->NewStringUTF(env, rec_msg); 
 }
	         
}

JNIEXPORT jstring JNICALL Java_Gui_Files
  (JNIEnv *env, jobject obj,jstring user, jobjectArray fn,jobjectArray fp, jintArray fs,jint fno, jint choice)
{
    //printf("user info %s\n", user);
   
   const char *uname = (*env)->GetStringUTFChars(env, user,  NULL) ;
   jint *filesize = (*env)->GetIntArrayElements(env, fs, 0);
   
    struct fileinfo client;
    client.filenum=fno;
   
   for(int i=0;i<fno;i++)
   {
   	const char *fname = (*env)->GetStringUTFChars(env, (*env)->GetObjectArrayElement(env, fn, i), NULL) ;
   	const char *fpath = (*env)->GetStringUTFChars(env, (*env)->GetObjectArrayElement(env, fp, i), NULL) ;
   	strcpy(client.filename[i],fname);
   	strcpy(client.filepath[i],fpath);
   	client.filesize[i]=filesize[i];   
   	printf("File info %s ,%s, %d , %d\n\n",client.filename[i],client.filepath[i],client.filesize[i], client.filenum);
   
   }			
   strcpy(client.username,uname);
   userChoice=choice;
   
   printf("\n---On client side\nUser info %s , %d----\n",client.username, choice);
   
   sen=send(sockfd, &userChoice, sizeof(userChoice), 0);
   printf("--sent bytes choice: %d\n", sen);
   sen=send(sockfd,(struct fileinfo *) &client, sizeof(client), 0); 
   printf("sent bytes file: %d--\n", sen);
   	
   rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   rec_msg[rec]='\0';
   printf("rec msg: %s",rec_msg);		
	   
	return  (*env)->NewStringUTF(env, rec_msg);	
			

}

JNIEXPORT jobjectArray JNICALL Java_Gui_getStructArray(JNIEnv *env, jobject obj){


   //Declare an object array
    jobjectArray args = 0;
   
    //Array size
    jsize len=50;

    //Get the class of the object, generally ava/lang/Object is enough
    jclass objClass = (*env)->FindClass(env,"java/lang/Object");

    //New object array
    args = (*env)->NewObjectArray(env,len, objClass, 0);

    /**//* The following are the variables in the corresponding instance class obtained in Java*/

    //Get the instance class in Java
    jclass objectClass = (*env)->FindClass(env,"fileinfo");
   
    //Get the definition of each variable in the class
    //first name
    jfieldID str = (*env)->GetFieldID(env,objectClass,"usern","Ljava/lang/String;");
    //serial number
    jfieldID stat = (*env)->GetFieldID(env,objectClass,"status","I");
    jfieldID fnumber = (*env)->GetFieldID(env,objectClass,"fno","I");
    
    int choice=6,fno=0;
    struct fileinfo *rec_msg;
    
    sen=send(sockfd, &choice, sizeof(userChoice), 0);
    rec=recv(sockfd,(struct fileinfo *)rec_msg, sizeof(rec_msg), 0);
    fno=rec_msg[0].filenum;
    printf("\nFile no.(new func) %d\n",fno);
    printf("--rec bytes rec: %d\n", rec);
    printf("--bytes size: %d\n", sizeof(rec_msg));
    printf("File info(new func) %s ,%s, %d , %d\n\n",rec_msg[0].filename[0],rec_msg[0].filepath[0],rec_msg[0].filesize[0], rec_msg[0].filenum);
    //for(int i=0;i<fno;i++)
   //{
   //     printf("File info(new func) %s ,%s, %d , %d\n\n",rec_msg[0].filename[i],rec_msg[0].filepath[i],rec_msg[0].filesize[i], rec_msg[0].filenum);
  // }     
    for(int i=0; i < len; i++ )
    {
        
        (*env)->SetShortField(env,obj,stat,1);
        (*env)->SetShortField(env,obj,fnumber,10);

        //Add to the objcet array
        (*env)->SetObjectArrayElement(env,args, i, obj);
    }
    //Return object array
    return args;

}







