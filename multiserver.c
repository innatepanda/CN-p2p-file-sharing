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

void *func(void *id);
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

char fname[] = "mydb.dat";


void displayAll()
{
	FILE *fp;
	struct clientinfo t;

	fp=fopen(fname,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t All Client Details\n\n");
	printf("========================================================\n\n");

	printf("Username\tPassword\tfilename\tStatus\n\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

	if(feof(fp))
	{
		break;
	}
	printf("%s\t\t",t.username);
	printf("%s\t\t",t.password);
	printf("%s\t\t",t.filename);
	printf("%d\t\t\n\n",t.status);

	}
	printf("========================================================\n\n");

	fclose(fp);
}

void UPDATE_STATUS_LOGIN(char user[50])
{
	FILE *fp,*fp1;
	struct clientinfo t,t1;
	int recvsize,found=0,count=0;
	
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
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
		
	while(1)
	{
		fread(&t,sizeof(t),1,fp);

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
	int rec,sen,found=0,count=0;
	char filename[50],msg[500];
	strcpy(msg,"Enter File to be Searched: ");
	sen=send(sockfd,msg,sizeof(msg),0);
	rec=recv(sockfd,filename,sizeof(filename),0);
	strcpy(msg,"FileFound...The users with the requested file are: ");
	
	fp=fopen(fname,"rb");
		
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
