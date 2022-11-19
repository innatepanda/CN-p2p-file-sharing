
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
#include <time.h>

#include "structs.h"
#include "Gui.h"
#include "aes_connector.h"
//0-reg, 1-login, 2-add file, 3-search, 4-del file, 5-logout, -1 - err logout




char serIP[16];int serPort, lisPort;
int connvar,sockfd;
int rec,sen;
char rec_msg[500],sent_msg[500];
//char unm[50],pwd[50],fnm[50];
int userChoice;
struct fileinfo fi[50];
pthread_t listen_id;
int n_files=0;

int create_receiving_socket();
int create_listening_socket();
void * listening_thread(void *port);

JNIEXPORT jint JNICALL Java_Gui_Cmain
  (JNIEnv *env, jobject obj){
  
  	return (create_receiving_socket() && create_listening_socket());
  	

}

int create_receiving_socket()
{

/****************************  SOCKET API  **********************************/

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
                   printf("Socket creation failed...\n");
                   return 0;
	}
	else
	{
	    //printf("Socket created successfully...\n");
		
/****************************  CONNECT API  ***********************************/

           struct sockaddr_in server;
           
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
		
              //create fork
              	//pthread_create(&listen_id,NULL,create_listening_thread, NULL);
              	
              
               
               return 1;
            }

     }

}

int create_listening_socket()
{
      
	int listen_fd,listenvar;
	
/****************************  SOCKET API  ***********************************************************************************************/

	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd==-1)
	{
		printf("Socket creation failed...\n");
		return 0;
	}
	else{
		//printf("Socket created successfully...\n");


/****************************  LISTEN API  ***********************************************************************************************/

		listenvar = listen(listen_fd,5);
		if(listenvar==-1)
		{
			printf("Listen failed....\n");
			return 0;
		}
		else
		{
			//printf("Listen successful...\n");
			struct sockaddr_in address;
			
			int addressSize1=sizeof(address);
			int g=getsockname(listen_fd, (struct sockaddr *)&address, &addressSize1);
			lisPort = ntohs(address.sin_port);
			printf( "Waiting for connection at Port no: %d \n\n", lisPort);
			
			pthread_create(&listen_id,NULL,listening_thread, (listen_fd));
		}
          
        }	
	
  return 1;	

}

void * listening_thread(void *fd)
{	
	int listening_fd = (int)fd;
	
	int clientfd[100];
	int i=0;
	
	while(1)
	{
				
           struct sockaddr_in client;	
           int clen = sizeof(client);
	
           clientfd[i] = accept(listening_fd,(struct sockaddr*)&client,&clen);
          
          
           //pthread_create(&thread_id[i],NULL,func,&conn);
           
           int cli_port = ntohs(client.sin_port);
    
	   if(clientfd[i]==-1)
	   {
	     printf("Accept failed....\n");
	     //exit(1);
	   }
	   else
	   {
	   	++i;
	       printf("...Client with port no %d connected to server...\n",cli_port);
	   }
  
       }

}

void update_n_files(int n)
{
	n_files = n;
	printf("\ncurrent files=%d\n", n_files);
	//sleep or wake up forked thread

}
JNIEXPORT jstring JNICALL Java_Gui_Auth
  (JNIEnv *env, jobject obj, jstring un, jstring pd, jint choice) {
  
   const char *unm = (*env)->GetStringUTFChars(env, un,  NULL) ;
   const char *pwd = (*env)->GetStringUTFChars(env, pd,  NULL ) ;
   
   struct clientinfo client;
			
   strcpy(client.username,unm);
   strcpy(client.password,pwd);
   //strcpy(client.filename,fname);
   userChoice=choice;
   client.status=lisPort;
   //client.filesize=fs;
   
   if(choice!=-1)
   {
	   
	AES_hashPassword(client.username, &client.password);
	   
   }
   
   //client.filenum=fno;
   //printf("\nUser info %s , %d\n",client.username, client.status);
   //printf("File info %s , %d , %d\n\n",client.filename,client.filesize, client.filenum);	
   sen=send(sockfd, &userChoice, sizeof(userChoice), 0);	
   
   if(userChoice==-1)
   {
	   exit(0);
   }
   else
   {
   	int n=0;
   	sen=send(sockfd,(struct clientinfo *) &client, sizeof(client), 0); //sending login details
   	
   	if(choice)
   	rec = recv(sockfd, &n, sizeof(int), 0);
   	rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   	rec_msg[rec]='\0';
   	update_n_files(n);
   	
   	//printf("rec msg: %s",rec_msg);		
 	return  (*env)->NewStringUTF(env, rec_msg); 
 	
 }
	         
}

JNIEXPORT jstring JNICALL Java_Gui_File
  (JNIEnv *env, jobject obj,jstring user, jobjectArray fn,jobjectArray fp, jintArray fs,jint fno, jint choice)
{
    //printf("user info %s\n", user);
   
   const char *uname = (*env)->GetStringUTFChars(env, user,  NULL) ;
   jint *filesize = (*env)->GetIntArrayElements(env, fs, 0);
   
    struct fileinfo client;
    client.filenum=fno;
   if(choice == 2)
   update_n_files(n_files+fno);
   else update_n_files(n_files-1);
   
   for(int i=0;i<fno;i++)
   {
   	const char *fname = (*env)->GetStringUTFChars(env, (*env)->GetObjectArrayElement(env, fn, i), NULL) ;
   	const char *fpath = (*env)->GetStringUTFChars(env, (*env)->GetObjectArrayElement(env, fp, i), NULL) ;
   	strcpy(client.filename[i],fname);
   	strcpy(client.filepath[i],fpath);
   	client.filesize[i]=filesize[i];   
   	//printf("File info %s ,%s, %d , %d\n\n",client.filename[i],client.filepath[i],client.filesize[i], client.filenum);
   
   }			
   strcpy(client.username,uname);
   userChoice=choice;
   
   sen=send(sockfd, &userChoice, sizeof(userChoice), 0);
   
   sen=send(sockfd,(struct fileinfo *) &client, sizeof(client), 0); 
   
   	
   rec=recv(sockfd, rec_msg, sizeof(rec_msg), 0); 
   rec_msg[rec]='\0';
   		
	   
	return  (*env)->NewStringUTF(env, rec_msg);	
			

}
JNIEXPORT jint JNICALL Java_Gui_getUserNumber(JNIEnv *env, jobject obj){
   int choice=6,unum=0;
       
    sen=send(sockfd, &choice, sizeof(userChoice), 0);
    rec=recv(sockfd,(int*)&unum, sizeof(unum), 0);
}


JNIEXPORT jobjectArray JNICALL Java_Gui_getStructArray(JNIEnv *env, jobject obj){

    int choice=6;
    uint32_t unum=0;
       
    sen=send(sockfd, &choice, sizeof(choice), 0);
    rec=recv(sockfd,(int*)&unum, sizeof(unum), 0);
    //unum = ntohl(unum);
    //printf("\nUser no.(---) %d \tuser bytes%d\n",unum, rec);
   //Declare an object array
    jobjectArray args;
   

    //Get the class of the object, generally ava/lang/Object is enough
    jclass objClass = (*env)->FindClass(env,"java/lang/Object");
    jclass stringClass = (*env)->FindClass(env,"java/lang/String");

    //New object array
    args = (*env)->NewObjectArray(env,unum, objClass, 0);
    
    //Get the instance class in Java
    jclass objectClass = (*env)->FindClass(env,"fileinfo");
   
    //Get the definition of each variable in the class
    //first name
    jfieldID user = (*env)->GetFieldID(env,objectClass,"usern","Ljava/lang/String;");
    jfieldID  fname = (*env)->GetFieldID(env,objectClass,"fnm","[Ljava/lang/String;");
    jfieldID  fpath = (*env)->GetFieldID(env,objectClass,"fpath","[Ljava/lang/String;");
    jfieldID  fs = (*env)->GetFieldID(env,objectClass,"fs","[I");
    jfieldID stat = (*env)->GetFieldID(env,objectClass,"status","I"); // see if we can remove status from class
    jfieldID fnumber = (*env)->GetFieldID(env,objectClass,"fno","I");
    
    
    
    
    //struct fileinfo *rec_msg=(struct fileinfo *)calloc(unum,sizeof(struct fileinfo));
    struct fileinfo rec_msg[unum];
    for(int i=0; i<unum; i++)
    {
    	rec=recv(sockfd,(struct fileinfo *)&rec_msg[i], sizeof(struct fileinfo), 0);
    	
    	
    }
    
    jstring str, str2;
    
    /*
    printf("--rec bytes rec: %d\n", rec);
    printf("--bytes size: %d\n", sizeof(rec_msg));
    printf("File info(new func) %s ,%s, %d , %d\n\n",rec_msg[0].filename[0],rec_msg[0].filepath[0],rec_msg[0].filesize[0], rec_msg[0].filenum);
    
    */
      
   
   jmethodID method = (*env)->GetMethodID(env,objectClass, "<init>", "()V");
  
  if(unum)
   
    for(int i=0; i < unum; i++ )
    {
      
	     jobject obj2 = (*env)->NewObjectA(env,objectClass,method,"()V");
	    (*env)->SetShortField(env,obj2,stat,rec_msg[i].status);
	    (*env)->SetShortField(env,obj2,fnumber,rec_msg[i].filenum );

	    //printf("Fileno---%d",rec_msg[i].filenum);
	    
	    jobjectArray js_arr = (*env)->NewObjectArray(env, rec_msg[i].filenum, stringClass, 0);
            jobjectArray jp_arr = (*env)->NewObjectArray(env, rec_msg[i].filenum, stringClass, 0);
            
            
	    for(int j=0;j<rec_msg[i].filenum;j++){
        	//str = (*env)->NewStringUTF(env,(*env)->GetObjectArrayElement(env, rec_msg[i].filepath, j));
        	str = (*env)->NewStringUTF(env,rec_msg[i].filepath[j]);
        	(*env)->SetObjectArrayElement(env,js_arr,j,str);
        	//str2 = (*env)->NewStringUTF(env, (*env)->GetObjectArrayElement(env, rec_msg[i].filename, j));
        	str2 = (*env)->NewStringUTF(env,rec_msg[i].filename[j]);
        	(*env)->SetObjectArrayElement(env,jp_arr,j,str2);
        }
	(*env)->SetObjectField(env, obj2, fpath, js_arr);
	(*env)->SetObjectField(env, obj2, fname, jp_arr);
	
	jintArray j_arr = (*env)->NewIntArray(env, rec_msg[i].filenum);
	(*env)->SetIntArrayRegion(env, j_arr, 0, rec_msg[i].filenum, rec_msg[i].filesize);
        (*env)->SetObjectField(env, obj2, fs, j_arr);
	
	
	
	     str = (*env)->NewStringUTF(env, rec_msg[i].username);
	    (*env)->SetObjectField(env,obj2,user, str);
	    
	    //printf("Username---%s",rec_msg[i].username);

                
          
           str = (*env)->NewStringUTF(env, rec_msg[i].username);
       
           (*env)->SetObjectArrayElement(env,args, i,obj2);
       
   }
    return args;


}







