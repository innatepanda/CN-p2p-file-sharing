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
<<<<<<< HEAD
=======
#include <time.h>
>>>>>>> kriti

void *func(void *id);
struct clientinfo
{
	char username[50];
	char password[50];
<<<<<<< HEAD
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

char fname[] = "mydb.dat";
=======
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


char userdb[] = "mydb.dat"; //username, number of files, filenames, filesizes, status
char users[] = "users.dat"; //username, password, date joined
>>>>>>> kriti


void displayAll()
{
	FILE *fp;
<<<<<<< HEAD
	struct clientinfo t;

	fp=fopen(fname,"rb");
=======
	struct fileinfo t;
	//struct clientinfo c;

	fp=fopen(userdb,"rb");
>>>>>>> kriti

	printf("\n========================================================\n\n");
	printf("\t\t All Client Details\n\n");
	printf("========================================================\n\n");

<<<<<<< HEAD
	printf("Username\tPassword\tfilename\tStatus\n\n");
=======
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
>>>>>>> kriti

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

	if(feof(fp))
	{
		break;
	}
<<<<<<< HEAD
	printf("%s\t\t",t.username);
	printf("%s\t\t",t.password);
	printf("%s\t\t",t.filename);
	printf("%d\t\t\n\n",t.status);
=======
	
	printf("%s\t\t",t.username);
	printf("%s\t\t",t.password);
	printf("%s",ctime(t.date));
>>>>>>> kriti

	}
	printf("========================================================\n\n");

	fclose(fp);
}

void UPDATE_STATUS_LOGIN(char user[50])
{
<<<<<<< HEAD
	FILE *fp,*fp1;
	struct clientinfo t,t1;
	int recvsize,found=0,count=0;
	
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
		
=======
	FILE *fp;
	struct fileinfo t;
	fp=fopen(userdb,"r+");
	printf("update login %s\n", user);
	
>>>>>>> kriti
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
<<<<<<< HEAD
		if(strcmp(t.username,user)==0)
		{
			found=1;
			//strcpy(msg,"UserFound");
			//send(sockfd,msg,sizeof(msg),0);
			
			t.status=1;
			
			fwrite(&t,sizeof(t),1,fp1);
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
		//strcpy(msg,"UserNotFound");
		//send(sockfd,msg,sizeof(msg),0);
	}
	else
	{
		fp=fopen(fname,"wb");
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



void UPDATE_STATUS_LOGOUT(char user[50])
{
	FILE *fp,*fp1;
	struct clientinfo t,t1;
	int recvsize,found=0,count=0;
	
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
=======
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
>>>>>>> kriti
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
<<<<<<< HEAD

		if(feof(fp))
		{
			break;
		}
		if(strcmp(t.username,user)==0)
		{
			found=1;
			//strcpy(msg,"UserFound");
			//send(sockfd,msg,sizeof(msg),0);
			
			t.status=0;
			
			fwrite(&t,sizeof(t),1,fp1);
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
		//strcpy(msg,"UserNotFound");
		//send(sockfd,msg,sizeof(msg),0);
	}
	else
	{
		fp=fopen(fname,"wb");
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



void SEARCH(int sockfd)
{
	FILE *fp;
	struct clientinfo t;
=======
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
void GET_File(int sockfd)
{

	FILE *fp; 
	//struct fileinfo *f1=(struct fileinfo *)calloc(100,sizeof(struct fileinfo));
	struct fileinfo f1[20];
	struct fileinfo f2;
	int found=0;
	int i=0;
	fp=fopen(userdb,"r+");
	//for(int n=0; n<fnum; n++)
	//{
	while(1)
        {
	        fread(&f1[i],sizeof(f1[i]),1,fp);
         	if(feof(fp))
         	{
         		break;
         	}
         	i++;
        }
        //f1 = realloc(f1, (i+1)*sizeof(struct fileinfo));
        
	fclose(fp);
	displayAll();
	
	 //printf("--send bytes rec: %d\n", sen);
	  printf("Test choice  %d, %s, i=%d",f1[0].filenum,f1[0].filename[0], i);
	    
	     	  
    printf("--bytes size: %d\n", sizeof(f1));
	//return f1;
	int sen1=send(sockfd,(int*)&i, sizeof(i), 0);
	int sen=send(sockfd,(struct fileinfo *)f1, sizeof(f1), 0);

	
}

/*
void SEARCH(int sockfd)
{
	FILE *fp;
	struct fileinfo t;
>>>>>>> kriti
	int rec,sen,found=0,count=0;
	char filename[50],msg[500];
	strcpy(msg,"Enter File to be Searched: ");
	sen=send(sockfd,msg,sizeof(msg),0);
	rec=recv(sockfd,filename,sizeof(filename),0);
	strcpy(msg,"FileFound...The users with the requested file are: ");
	
<<<<<<< HEAD
	fp=fopen(fname,"rb");
=======
	fp=fopen(userdb,"rb");
>>>>>>> kriti
		
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

<<<<<<< HEAD

void ADDFILE(int sockfd)
{
	struct signup neww2[20];
	int rec,sen;
	char msg[200];
	rec=recv(sockfd, neww2, sizeof(neww2), 0);

	//add all the new files to the database of clientinfo
	int no_of_files = neww2[0].filenum;
	
	FILE *fp;
	fp=fopen(fname,"ab");
						
	for(int n=0; n<no_of_files; n++)
	{
		struct clientinfo cli;
		strcpy(cli.username,neww2[n].username);
		strcpy(cli.password,neww2[n].password);
		strcpy(cli.filename,neww2[n].filename);
		cli.status=1;
								
		fwrite(&cli,sizeof(cli),1,fp);
	}
	fclose(fp);
	
	strcpy(msg,"Successfully added new files to database\n");
	sen=send(sockfd, msg, strlen(msg), 0);
}

void DELETE(int sockfd,char user[50])
{
	FILE *fp,*fp1;
	struct clientinfo t,t1;
	int rec,sen,found=0,count=0;
	char filename[50],msg[200];
	strcpy(msg,"Enter Filename to be Deleted\n");
	sen=send(sockfd,msg,strlen(msg),0);
	rec=recv(sockfd,filename,sizeof(filename),0);
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
=======
*/

void DELETE(struct fileinfo finfo)
{
	FILE *fp;
	struct fileinfo t;
	int found=0, i;
	
	
	fp=fopen(userdb,"r+");
>>>>>>> kriti
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
<<<<<<< HEAD
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
		fp=fopen(fname,"wb");
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
=======
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
>>>>>>> kriti
}	

	

int sen,rec;
int cliPort;
struct sockaddr_in client;
<<<<<<< HEAD
int main(int argc,char *argv[])
=======
int main()
>>>>>>> kriti
{
      
	int sockfd,bindvar,listenvar;
	int clientfd[100];
	int i=1,flag=0;
	char serIP[16];int serPort;
	char cliIP[16];
	
	
<<<<<<< HEAD
	int a= atoi(argv[1]);
=======
	//int a= atoi(argv[1]);
>>>>>>> kriti
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
<<<<<<< HEAD
		server.sin_port=htons(a);
=======
		server.sin_port=htons(4000);
>>>>>>> kriti
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
<<<<<<< HEAD
	        {
				
	           struct sockaddr_in client;	
	//printf("Waiting for the connection request from clients at server\n");	
	           clientfd[i] = accept(sockfd,(struct sockaddr*)&client,&clen);
	           
	           pthread_create(&thread_id[i],NULL,func,&clientfd[i]);
	           ++i;
              }
=======
	               {
				
	                   struct sockaddr_in client;	
	        //printf("Waiting for the connection request from clients at server\n");	
	                   clientfd[i] = accept(sockfd,(struct sockaddr*)&client,&clen);
	                  
	                   pthread_create(&thread_id[i],NULL,func,&clientfd[i]);
	                   ++i;
	          
                       }
>>>>>>> kriti
             }
          }
        }	
	
  return 0;	

}
void *func(void *id)
<<<<<<< HEAD
	         {
	            pthread_detach(pthread_self());
	            int *cfd = (int*)id;
	            char rec_msg[500],sent_msg[500];
	           if(*cfd==-1)
	           {
	             printf("Accept failed....\n");
	             exit(1);
	           }
	           else
	           {
		cliPort=ntohs(client.sin_port);
		printf("Client with port no %d connected to the server...\n",cliPort);
		strcpy(sent_msg,"\nWelcome to the P2P server\nPress 0 and enter to SIGN-UP\nPress 1 and enter to LOGIN\nPress -1 to exit\n\n");
		sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	              while(1)
	              {
		rec=recv(*cfd, rec_msg, sizeof(rec_msg), 0);
		//receiving choice 0 or 1
		rec_msg[rec]='\0';
						
/****************************  SIGNUP  ******************************/		
		
		if(strcmp(rec_msg,"0")==0)   //CODE FOR SIGNUP
                              {
		  strcpy(sent_msg,"Please enter your username , password and list of filenames to SIGNUP\n");
		  sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
							
		  struct signup neww[100];
		  rec=recv(*cfd, neww, sizeof(neww), 0);
							
		  //add all the records to the database of clientinfo
		  int no_of_files = neww[0].filenum;
		  int n;
							
		  FILE *fp;
		  fp=fopen(fname,"ab");
							
		  for(n=0; n<no_of_files; n++)
		 {
		   struct clientinfo c1;
		   strcpy(c1.username,neww[n].username);
		   strcpy(c1.password,neww[n].password);
		   strcpy(c1.filename,neww[n].filename);
		   c1.status=0;
								
		   fwrite(&c1,sizeof(c1),1,fp);
	                }
		   fclose(fp);
							
		 strcpy(sent_msg,"Successfully signed up and record added to database\n");
		 printf("New client ( username : %s ) added to database.\n",neww[0].username);
		 sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
							
		displayAll();
		//close(sockfd);
		//exit(1);
                              //continue;
	             }

/****************************  LOGIN  ***********************************/
						
                           else if(strcmp(rec_msg,"1")==0)   //CODE FOR LOGIN
	            {
	              strcpy(sent_msg,"Please enter your username and password to LOGIN\n");
	              sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	              struct login chk[1];
	              rec=recv(*cfd,chk, sizeof(chk), 0);
	              //receiving username and password
													
	             //check for the details in database and return found or not found
							
	              FILE *fp;
	              fp=fopen(fname,"rb");
	              struct clientinfo c2;
	              int found=0;
	              while(1)
	             {
		fread(&c2,sizeof(c2),1,fp);

		if(feof(fp))
		   break;     								
		if(strcmp(chk[0].username,c2.username)==0  &&   strcmp(chk[0].password,c2.password)==0 )
		{
		   found=1;
		   strcpy(sent_msg,"f");
		   sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
								
		   //update the status to online of the logged in user
		  UPDATE_STATUS_LOGIN(c2.username);
		  printf("New client ( username : %s and password : %s) logged into server.Status updated to online\n",chk[0].username,chk[0].password);
		  break;
		}
		

	             }
	             fclose(fp);
	             if(found==0)
	             {
		  strcpy(sent_msg,"nf");
	                 sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
		  printf("Incorrect details ( username : %s and password : %s).\n",chk[0].username,chk[0].password);
	             }
	             displayAll();
		  
							
							
	             if(found==1)
	             {
	              // strcpy(sent_msg,"Enter 1 to SEARCH\nEnter 2 to ADD FILES\nEnter 3 to DELETE files\nEnter 0 to LOGOUT\n");
		//sen=send(clientfd[i], sent_msg, strlen(sent_msg), 0);
								
		int check = -1;
		while(check != 0)
		//while(1)
		{
		  //printf("\namia\n");	
		  rec=recv(*cfd,rec_msg,sizeof(rec_msg),0);
		  rec_msg[rec]='\0';
		 // printf("\n%s\n",rec_msg);
		  check=atoi(rec_msg);
		  //printf("\n%d\n",check);			
		  switch(check)
		  {
		    case 1: SEARCH(*cfd);
		            break;
									
		    case 2: ADDFILE(*cfd);
		            displayAll();
		            break;
									
		    case 3: DELETE(*cfd,c2.username);
		            displayAll();
		            break;	
										
		    case 0: UPDATE_STATUS_LOGOUT(c2.username);
		            printf("Client ( username : %s and password : %s) logged out of the server.Status updated to offline\n",c2.username,c2.password);	
		            strcpy(sent_msg,"Successfully Logged out of p2p server\n");
                                          sen=send(*cfd, sent_msg, strlen(sent_msg),0);
                                          displayAll();
                                          break;	
	                 }
	                // if(check==0)
	                 //{
	                 //  break;
	                 //}
	               }
	           }
							
	         // close(sockfd);
	        //  exit(1);
	           }
	           else if(strcmp(rec_msg,"-1")==0)
	           {
	              // flag=1;
	               close(*cfd);
	               pthread_exit(0);
	               //break;
	           }
						
/****************************  INVALID CHOICE **********************************/
						
	      else
	      {			
	          printf("Invalid choice. Please try again.\n");
	          displayAll();
	          //close(sockfd);
	          //exit(1);
	      }
	      
	      //if(flag==1)
	      //{
	      //  break;
	      //}
						
                    }				
						
	    }
	}
=======
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
	     	
	     	rec=recv(*cfd,&finfo, sizeof(finfo), 0);
	     	//printf("recvd file: %s %d", finfo.filename,finfo.filenum);
	     	
	     	   ADD_File(finfo);
	     	
	     	
	     	strcpy(sent_msg,"file added");
                sen=send(*cfd, sent_msg, strlen(sent_msg), 0);
	     
	     }
	     
	     else if(choice == 6)
	     {
	     	
	     	//rec=recv(*cfd,&finfo, sizeof(finfo), 0);
	     	//printf("recvd file: %s %d", finfo.filename,finfo.filenum);
	     	   
	     	   //struct fileinfo *finfo;
	     	   GET_File(*cfd);
	     	   
	     	   //printf("Test choice %d , %d, %s", choice,finfo[0].filenum,finfo[0].filename[0]);
	     	   //sen=send(*cfd,(struct fileinfo *)finfo, sizeof(finfo), 0);
	     	  
    //printf("--bytes size: %d\n", sizeof(finfo));
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
						
>>>>>>> kriti
