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
#include <pthread.h>
#include<time.h>

void *func(void *id);
struct clientinfo
{
	char username[50];
	char password[50];
	time_t date[50]; //at time of reg, server assigns
	
};
struct fileinfo
{
	char username[50];
	char filename[50];
	int filesize;
	int filenum;
	int status;
	
};


char userdb[] = "mydb.dat"; //username, number of files, filenames, filesizes, status
char users[] = "users.dat"; //username, password, date joined


void displayAll()
{
	FILE *fp;
	struct fileinfo t;
	//struct clientinfo c;

	fp=fopen(userdb,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t All Client Details\n\n");
	printf("========================================================\n\n");

	printf("Username\tno. of files\tfilenames\t\tfile size\tStatus\n\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

	if(feof(fp))
	{
		break;
	}
	printf("%s\t\t",t.username);
	printf("%d\t\t",t.filenum);
	printf("%s\t\t\t",t.filename);
	printf("%d\t\t",t.filesize);
	printf("%d\t\n\n",t.status);

	}
	printf("========================================================\n\n");

	fclose(fp);
}

void displayUsers()
{
	FILE *fp;
	struct clientinfo t;

	fp=fopen(users,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t Clients \n\n");
	printf("========================================================\n\n");

	printf("Username\tPassword\tDate Joined\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

	if(feof(fp))
	{
		break;
	}
	
	printf("%s\t\t",t.username);
	printf("%s\t\t",t.password);
	printf("%s",ctime(t.date));

	}
	printf("========================================================\n\n");

	fclose(fp);
}

void UPDATE_STATUS_LOGIN(char user[50])
{
	FILE *fp;
	struct fileinfo t;
	fp=fopen(userdb,"r+");
	printf("update login %s\n", user);
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		//printf("t user %s\n", t.username);
		if(strcmp(t.username,user)==0)
		{
			
			
			t.status=1;
			fseek(fp, ftell(fp)-sizeof(t), SEEK_SET);
			fwrite(&t,sizeof(t),1,fp);
		}
	}
	fclose(fp);
	
	displayAll();
}

void ADD_USER (char usrn[50],char pwd[50])
{

	FILE *fp; struct clientinfo c1; struct fileinfo f1;
	time_t t;   // date of joining
	time(&t);
	
	fp=fopen(users,"ab");
	strcpy(c1.username,usrn);
	strcpy(c1.password,pwd);
	time(c1.date);
	fwrite(&c1,sizeof(c1),1,fp);
	fclose(fp);
	//fp=fopen(userdb,"ab");
	
        //f1.status=1;
	        
								
	//fwrite(&f1,sizeof(f1),1,fp);	
	//fclose(fp);
	displayUsers();
	//displayAll();
}

int SEARCH_USER(char usrn[50],char pwd[50]){
     FILE *fp;
      fp=fopen(users,"rb");
      struct clientinfo c2;
      int found=0;
      //printf("search user %s %s %d\n",usrn, pwd, strlen(pwd));
      while(1)
      {
	fread(&c2,sizeof(c2),1,fp);
 	if(feof(fp))
 	{
 		break;
 	}
	//printf("c user %s\n", c2.username);      								
	if(strcmp(usrn,c2.username)==0)
	{
	   if(strlen(pwd)==1 || (strlen(pwd)>1 && strcmp(pwd,c2.password)==0))
           {
                found=1;
           }
	   
	  break;
	}
	

     }
     fclose(fp);
     //printf("found in search %d\n", found);
     return found;
    
		  
				
}

void UPDATE_STATUS_LOGOUT(char user[50])
{
	FILE *fp;
	struct fileinfo t;
	int count=0;
	
	fp=fopen(userdb,"r+");
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
		{break;}
		if(strcmp(t.username,user)==0)
		{
			
			t.status=0;
			fseek(fp, ftell(fp)-sizeof(t), SEEK_SET);
			fwrite(&t,sizeof(t),1,fp);
		}
			
	}
	fclose(fp);
	//displayAll();
}


void ADD_File(char usrn[50],char fname[50],int fsize,int fnum)
{

	FILE *fp; 
	struct fileinfo f1;
	
	fp=fopen(userdb,"ab");
	//for(int n=0; n<fnum; n++)
	//{
		strcpy(f1.username,usrn);
	        strcpy(f1.filename,fname);
	        f1.filenum=fnum;
	        f1.filesize=fsize;
	        f1.status=1;
	        
								
		fwrite(&f1,sizeof(f1),1,fp);
	//}	
	fclose(fp);
	
	//displayUsers();
	//displayAll();
}

void SEARCH(int sockfd)
{
	FILE *fp;
	struct fileinfo t;
	int rec,sen,found=0,count=0;
	char filename[50],msg[500];
	strcpy(msg,"Enter File to be Searched: ");
	sen=send(sockfd,msg,sizeof(msg),0);
	rec=recv(sockfd,filename,sizeof(filename),0);
	strcpy(msg,"FileFound...The users with the requested file are: ");
	
	fp=fopen(userdb,"rb");
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		if(strcmp(t.filename,filename)==0 && t.status==1)
		{
			count++;
			strcat(msg , t.username);
			strcat(msg, ", ");
			//sen=send(sockfd,msg,sizeof(msg),0);
			//break;
		}
	}
	
	if(count!=0)
	{
		sen=send(sockfd,msg,sizeof(msg),0);
	}
	else   //if(count==0)
	{
		strcpy(msg,"FileNotFound\n");
		sen=send(sockfd,msg,sizeof(msg),0);
	}
	
	
	fclose(fp);
}



void DELETE(int sockfd,char user[50])
{
	FILE *fp,*fp1;
	struct fileinfo t,t1;
	int rec,sen,found=0,count=0;
	char filename[50],msg[200];
	strcpy(msg,"Enter Filename to be Deleted\n");
	sen=send(sockfd,msg,strlen(msg),0);
	rec=recv(sockfd,filename,sizeof(filename),0);
	fp=fopen(userdb,"rb");
	fp1=fopen("temp.dat","wb");
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		if(strcmp(t.username,user)==0 && strcmp(t.filename,filename)==0)
		{
			found=1;
			strcpy(msg,"File Successfully Deleted\n");
			send(sockfd,msg,sizeof(msg),0);
			
		}
		else
		{
			fwrite(&t,sizeof(t),1,fp1);
		}	
	}
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
	{
		strcpy(msg,"FileNotFound\n");
		send(sockfd,msg,strlen(msg),0);
	}
	else
	{
		fp=fopen(userdb,"wb");
		fp1=fopen("temp.dat","rb");
	
		while(1)
		{
			fread(&t,sizeof(t),1,fp1);
		
			if(feof(fp1))
			{
				break;
			}
			fwrite(&t,sizeof(t),1,fp);
		}
	}
		
	fclose(fp);
	fclose(fp1);
}	

	

int sen,rec;
int cliPort;
struct sockaddr_in client;
int main(int argc,char *argv[])
{
      
	int sockfd,bindvar,listenvar;
	int clientfd[100];
	int i=1,flag=0;
	char serIP[16];int serPort;
	char cliIP[16];
	
	
	int a= atoi(argv[1]);
/****************************  SOCKET API  ***********************************************************************************************/

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Socket creation failed...\n");
		exit(1);
	}
	else{
		printf("Socket created successfully...\n");

/****************************  BIND API  ***********************************************************************************************/
		
		struct sockaddr_in server;
		server.sin_family=AF_INET;
		server.sin_port=htons(a);
		server.sin_addr.s_addr=INADDR_ANY;
		
		int clen = sizeof(client);

		bindvar = bind(sockfd,(const struct sockaddr *)(&server),sizeof(server));
		if(bindvar==-1)
		{
			printf("Binding failed....\n");
			exit(1);
		}
		else
		{
			printf("Binding successful...\n");
			
/****************************  LISTEN API  ***********************************************************************************************/

			listenvar = listen(sockfd,5);
			if(listenvar==-1)
			{
				printf("Listen failed....\n");
				exit(1);
			}
			else
			{
				printf("Listen successful...\n");
				
/****************************  ACCEPT API  ***********************************************************************************************/
                       pthread_t thread_id[100];	
                       while(1)
	               {
				
	                   struct sockaddr_in client;	
	        //printf("Waiting for the connection request from clients at server\n");	
	                   clientfd[i] = accept(sockfd,(struct sockaddr*)&client,&clen);
	                  
	                   pthread_create(&thread_id[i],NULL,func,&clientfd[i]);
	                   ++i;
	          
                       }
             }
          }
        }	
	
  return 0;	

}
void *func(void *id)
{
    pthread_detach(pthread_self());
    int *cfd = (int*)id;
    char sent_msg[500];
    struct clientinfo rec_msg; int choice; struct fileinfo finfo;
   if(*cfd==-1)
   {
     printf("Accept failed....\n");
     exit(1);
   }
   else
   {
       cliPort=ntohs(client.sin_port);
       printf("Client with port no %d connected to the server...\n",cliPort);
      while(1)
      {
         rec = recv(*cfd,&choice, sizeof(choice), 0);
         printf("choice %d\n", choice);
         
         
                
						
/****************************  SIGNUP  ******************************/		

          if(choice==0)   //CODE FOR SIGNUP
          {
          	rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);
          	
		  int found = SEARCH_USER(rec_msg.username,"p");
		  if(found==1)
		  {
		      strcpy(sent_msg,"500 Username alreay exists\n");
		      sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
		        
		  }
		  else{
		       //ADD_USER(rec_msg.username, rec_msg.password,"",0,0);
	               ADD_USER(rec_msg.username, rec_msg.password);
		       strcpy(sent_msg,"200 Successfully signed up and record added to database\n");
		       printf("New client ( username : %s ) added to database.\n",rec_msg.username);
		       sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
							        
		      // displayAll();
				
		  }				
	   
		}				        
	
	   

/****************************  LOGIN  ***********************************/
						
        else if(choice==1)   //CODE FOR LOGIN
        {
             	rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);								
             //check for the details in database and return found or not found
		printf("details %s %s\n", rec_msg.username,rec_msg.password);	
       	int found=SEARCH_USER(rec_msg.username,rec_msg.password);
       	printf("login found %d\n", found);			
		if(found==1)
		{
		   
		   strcpy(sent_msg,"200 f");
		   sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
								
		   //update the status to online of the logged in user
		  UPDATE_STATUS_LOGIN(rec_msg.username);
		  printf("New client ( username : %s and password : %s) logged into server.Status updated to online\n",rec_msg.username,rec_msg.password);
		  
		  //displayAll();
		   //return "Successfully Logedin";
		   
		   
		   
		   
		}
		
               
                else if(found==0)
                {
	             strcpy(sent_msg,"500 nf");
                     sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	             printf("Incorrect details\n");
	        }
	     }
	     
	     else if(choice == 2)
	     {
	     	printf("--here--");
	     	rec=recv(*cfd,&finfo, sizeof(finfo), 0);
	     	printf("recvd file: %s %d", finfo.filename,finfo.filenum);
	     	
	     	   ADD_File(finfo.username,finfo.filename,finfo.filesize,finfo.filenum);
	     	
	     	displayAll();
	     	strcpy(sent_msg,"file added");
                sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	     
	     }
             
             
		
	     else if(choice==5){
	          rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);
	          printf("Client ( username : %s and password : %s) logged out of the server.Status updated to offline\n",rec_msg.username,rec_msg.password);	
	          UPDATE_STATUS_LOGOUT(rec_msg.username);
	          strcpy(sent_msg,"200 Successfully Logged out of p2p server\n");
                  sen=send(*cfd, sent_msg, strlen(sent_msg),0);
                  
                  
                  //close(*cfd);
                 // pthread_exit(0);
                  //break;
	     } 
	     else if(choice==-1){
	         rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);
	          printf("Client ( username : %s and password : %s) logged out of the server.Status updated to offline\n",rec_msg.username,rec_msg.password);	
	          UPDATE_STATUS_LOGOUT(rec_msg.username);
                  
                  
                  //close(*cfd);
                  pthread_exit(0);
                  //break;
	     } 
	     
	     printf("---end of loop---");
	}						
	        
	}
						

						
    }				
						
