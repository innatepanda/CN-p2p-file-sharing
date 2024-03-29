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
#include <time.h>

void *func(void *id);
struct clientinfo
{
	char username[50];
	char password[50];
	time_t date[50]; //at time of reg, server assigns
	
};
struct fileinfo //to write in database, prev struct + incoming struct, then write
{
	char username[50];
	char filename[50][50];
	char filepath[50][50];
	int filesize[50];
	int filenum; 
	int status;
	
};


char userdb[] = "mydb.bin"; //username, number of files, filenames, filesizes, status
char users[] = "users.bin"; //username, password, date joined


void displayAll()
{
	FILE *fp;
	struct fileinfo t;
	//struct clientinfo c;

	fp=fopen(userdb,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t All File Details\n\n");
	printf("========================================================\n\n");

	printf("Username\tStatus\tno. of files\tfilenames\t\tfile size\t\n\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

	if(feof(fp))
	{
		break;
	}
	printf("%s\t\t",t.username);
	printf("%d\t",t.status);
	printf("%d\t\t",t.filenum);
	
        
	for(int i=0;i<t.filenum;i++)
	{
	        if(i>0)
                     printf("\t\t\t\t\t");
		printf("%s\t\t",t.filename[i]);
		printf("%d\n",t.filesize[i]);
		
	}
	printf("\n");
	
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
	
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		
		if(strcmp(t.username,user)==0)
		{
			
			
			t.status=1;
			fseek(fp, ftell(fp)-sizeof(struct fileinfo), SEEK_SET);
			fwrite(&t,sizeof(t),1,fp);
			break;
		}
	}
	fclose(fp);
	
	displayAll();
	displayUsers();
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
			break;
		}
		
			
	}
	fclose(fp);
	displayAll();
}


void ADD_File(struct fileinfo finfo)
{

	FILE *fp; 
	struct fileinfo f1;
	int found=0;
	fp=fopen(userdb,"r+");
	//for(int n=0; n<fnum; n++)
	//{
	while(1)
      {
	fread(&f1,sizeof(f1),1,fp);
 	if(feof(fp))
 	{
 		break;
 	}
	//printf("c user %s\n", c2.username);      								
	if(strcmp(finfo.username,f1.username)==0)
	{
	   
                found=1;
                
                for(int i=0;i<finfo.filenum;i++)
                {
                	strcpy(f1.filename[f1.filenum+i],finfo.filename[i]);
                	strcpy(f1.filepath[f1.filenum+i],finfo.filepath[i]);
                	printf("--fn:%s %s\t", f1.filename[f1.filenum+i],f1.filepath[f1.filenum+i]);
                	f1.filesize[f1.filenum+i]=finfo.filesize[i];
                }
                f1.filenum+=finfo.filenum;
                f1.status=1;
		
		fseek(fp, ftell(fp)-sizeof(f1), SEEK_SET);						
		fwrite(&f1,sizeof(f1),1,fp);
	
           
	   
	  break;
	}
	

     }
     
     if(found==0)
     {
		finfo.status=1;
		printf("adding new line\n");
								
		fwrite(&finfo,sizeof(finfo),1,fp);
     }
		
	fclose(fp);
	displayAll();

	
}


void Delete_empty_users()
{

//TODO: delete empty user entries once no of users with filenum=0 reaches 1/3 of all users

}

void GET_File(int sockfd)
{

	FILE *fp; 
	//struct fileinfo *f1=(struct fileinfo *)calloc(100,sizeof(struct fileinfo));
	struct fileinfo f1[10];
	int i=0;
	fp=fopen(userdb,"r+");
	
	//for(int n=0; n<fnum; n++)
	//{
	while(1)
        {
	        fread(&f1[i],sizeof(struct fileinfo),1,fp);
	        
         	if(feof(fp))
         	{
         		break;
         	}
         	
         	if(f1[i].filenum>0 && f1[i].status)
         	i++;
         	
        }
        //f1 = realloc(f1, (i+1)*sizeof(struct fileinfo));
        
	fclose(fp);
	displayAll();
	
	 //printf("--send bytes rec: %d\n", sen);
	  printf("Test choice  %d, %s, i=%d",f1[0].filenum,f1[0].filename[0], i);
	  
	     	  
    
	//return f1;
	int sen1=send(sockfd,(int *)&i, sizeof(int), 0);
	int sen;
	for(int j=0; j<i; j++)
	{ 
		sen=send(sockfd,(struct fileinfo *)&f1[j], sizeof(struct fileinfo), 0); 
		printf("send status:%d %d\n\n", sen1, sen);
	}
	

	
}

/*
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

*/

void DELETE(struct fileinfo finfo)
{
	FILE *fp;
	struct fileinfo t;
	int found=0, i;
	
	
	fp=fopen(userdb,"r+");
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		if(strcmp(t.username,finfo.username)==0)
		{
			
			for( i=0;i<t.filenum;i++)
			{
				if(strcmp(t.filepath[i],finfo.filepath[0])==0)
				{
					
					found=1;
					break;
					
				}
			}
			
			if(found)
			{ 
				for(;i<t.filenum-1;i++)
				{
					strcpy(t.filename[i],t.filename[i+1]);
					strcpy(t.filepath[i],t.filepath[i+1]);
					t.filesize[i]=t.filesize[i+1];
				}
				
				t.filenum--;
				
				fseek(fp, ftell(fp)-sizeof(t), SEEK_SET);	
				fwrite(&t,sizeof(t),1,fp);
				
				
			}
			
		}
		if(found)
		{
			break;
		}
		
			
			
	}
	fclose(fp);
	displayAll();
}	

	

int sen,rec;
int cliPort;
struct sockaddr_in client;
int main()
{
      
	int sockfd,bindvar,listenvar;
	int clientfd[100];
	int i=1,flag=0;
	char serIP[16];int serPort;
	char cliIP[16];
	
	
	//int a= atoi(argv[1]);
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
		server.sin_port=htons(4000);
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
		      strcpy(sent_msg,"500 Username already exists\n");
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
		  printf("Client ( username : %s and password : %s) logged into server.Status updated to online\n",rec_msg.username,rec_msg.password);
		  
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
	     	
	     	rec=recv(*cfd,&finfo, sizeof(finfo), 0);
	     	//printf("recvd file: %s %d", finfo.filename,finfo.filenum);
	     	
	     	   ADD_File(finfo);
	     	
	     	
	     	strcpy(sent_msg,"file added");
                sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	     
	     }
	     
	     
	     else if(choice == 4)
	     {
	     	printf("--here--");
	     	rec=recv(*cfd,&finfo, sizeof(finfo), 0);
	     	//printf("recvd file: %s %d", finfo.filename,finfo.filenum);
	     	
	     	   DELETE(finfo);
	     	
	     	
	     	strcpy(sent_msg,"200 file deleted");
                sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	     
	     }
             
             
		
	     else if(choice==5){
	          rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);
	          printf("Client (%s) logged out of the server.Status updated to offline\n",rec_msg.username);	
	          UPDATE_STATUS_LOGOUT(rec_msg.username);
	          strcpy(sent_msg,"200 Successfully Logged out of p2p server\n");
                  sen=send(*cfd, sent_msg, strlen(sent_msg),0);
                  
	     } 
	     
	     else if(choice == 6)
	     {
	
	     	   GET_File(*cfd);
	    
	     }
	     
	     else if(choice==-1){
	         rec=recv(*cfd,&rec_msg, sizeof(rec_msg), 0);
	          	
	          UPDATE_STATUS_LOGOUT(rec_msg.username);
	          printf("Client (%s) logged out of the server.Status updated to offline\n",rec_msg.username);
                  
                  
                  close(*cfd);
                  pthread_exit(0);
                  //break;
	     } 
	     
	     printf("---end of loop---");
	}						
	        
	}
						

						
    }				
						
