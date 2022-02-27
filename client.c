
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
struct fileinfo fi[50];

JNIEXPORT jint JNICALL Java_Gui_Cmain
  (JNIEnv *env, jobject obj){
	

	
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
   const char *pwd = (*env)->GetStringUTFChars(env, pd,  NULL ) ;
   
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

    int choice=6,unum=0;
       
    sen=send(sockfd, &choice, sizeof(userChoice), 0);
    rec=recv(sockfd,(int*)&unum, sizeof(unum), 0);
   //Declare an object array
    jobjectArray args;
   

    //Get the class of the object, generally ava/lang/Object is enough
    jclass objClass = (*env)->FindClass(env,"java/lang/Object");

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
    rec=recv(sockfd,(struct fileinfo *)rec_msg, sizeof(rec_msg), 0);
    jstring str, str2;
    
    printf("\nUser no.(---) %d\n",unum);
    printf("--rec bytes rec: %d\n", rec);
    printf("--bytes size: %d\n", sizeof(rec_msg));
    printf("File info(new func) %s ,%s, %d , %d\n\n",rec_msg[0].filename[0],rec_msg[0].filepath[0],rec_msg[0].filesize[0], rec_msg[0].filenum);
    
    
      
   
   jmethodID method = (*env)->GetMethodID(env,objectClass, "<init>", "()V");
  
   printf("\n------- loop start--------- \n");
    for(int i=0; i < unum; i++ )
    {
      
        printf("\ni-%d---", i);
      
             jobject obj2 = (*env)->NewObjectA(env,objectClass,method,"()V");
            (*env)->SetShortField(env,obj2,stat,1);
            (*env)->SetShortField(env,obj2,fnumber,rec_msg[i].filenum );
            printf("Fileno---%d",rec_msg[i].filenum);
            
             str = (*env)->NewStringUTF(env, rec_msg[i].username);
            (*env)->SetObjectField(env,obj2,user, str);
            
            printf("Uesrname---%s",rec_msg[i].username);
                
          
         str = (*env)->NewStringUTF(env, rec_msg[i].username);
       
        (*env)->SetObjectArrayElement(env,args, i,obj2);
       
   }
    return args;


}








