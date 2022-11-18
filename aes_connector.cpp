#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "aes_connector.h"
#include "aes_header.h"

#ifdef __cplusplus
FILE * fp;

 int range[3][2]={
			{65, 90},
			{97, 122},
			{48, 57}
			};

void createRandomSalt()
{
	time_t t;
	srand(time_t(&t));
	rand();
	int length = 5 + rand()%5;
	char salt[length];
	int selection=0;
	
	for(int i=0; i<length; i++)
	{
		selection = rand()%3;
		salt[i] = (char)(range[selection][0] + rand()%(range[selection][1]-range[selection][0]));
			
	
	}
	salt[length]='\0';
	printf("\nnew salt%s \n", salt);
	
	fwrite(&salt, sizeof(char), length+1, fp);
}
extern "C" {
#endif

// Inside this "extern C" block, I can implement functions in C++, which will externally 
//   appear as C functions (which means that the function IDs will be their names, unlike
//   the regular C++ behavior, which allows defining multiple functions with the same name
//   (overloading) and hence uses function signature hashing to enforce unique IDs),


void AES_hashPassword(char * unm, char  * password) {
	fp = fopen(unm, "a+");
	printf("username: %s", unm);
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
	
	printf("\nsalted:%s\n", f1);
	sprintf(f1, "%x", aes_main(f1));
	printf("\nhashed:%s", f1);
	
	
	fclose(fp);
	strcpy(password, f1);
	
    	
}

#ifdef __cplusplus
}
#endif
