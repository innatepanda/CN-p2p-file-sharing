#include<stdio.h>
#include <time.h>

FILE *fp;
 int range[3][2]={
			{65, 90},
			{97, 122},
			{48, 57}
			};
void createRandomSalt()
{
	
	srand(time(0));
	int length = 5 + rand()%5;
	char salt[length];
	int selection=0;
	
	for(int i=0; i<length; i++)
	{
		selection = rand()%3;
		salt[i] = (char)(range[selection][0] + rand()%(range[selection][1]-range[selection][0]));
			
	
	}
	salt[length]='\0';
	printf("%s \n", salt);
	
	fwrite(&salt, sizeof(char), length+1, fp);
}

void encrypt(char * password)
{


}

void hashPassword(char * unm, char  *password)
{
	fp = fopen(unm, "a+");
	fseek(fp, 0, SEEK_END);
	   
	   if(ftell(fp)==0)
	   {
	   	createRandomSalt();
	   
	   }
	fseek(fp, 0, SEEK_SET);
	char f1[50];
	
	int count=fread(&f1,sizeof(char),50,fp); 
	f1[count]='\0';
	
	strcat(f1, password);
	
	printf("hashed:%s", f1);
	encrypt(&f1);
	
	fclose(fp);
	strcpy(password, f1);
}








