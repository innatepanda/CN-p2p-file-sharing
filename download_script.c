
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
#include "Bridge.h"

//IN PROGRESS, CURRENTLY UNUSED
JNIEXPORT void JNICALL Java_Bridge_DownloadFile
  (JNIEnv *env, jobject obj,jint port, jstring fp, jstring new_fp)
{
    
   const char *fpath = (*env)->GetStringUTFChars(env, fp, NULL) ;
   const char *new_fpath = (*env)->GetStringUTFChars(env, new_fp, NULL) ;
   
   printf("dets_port%d", port);
  
   int r = socket(PF_INET, SOCK_STREAM, 0);
    if(r!=-1){
    printf("Socket Created Sucessfully.\n");
    }
    else{exit(1);}
    
        struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int r1=connect(r, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(r1==-1){
    printf("\nconnection error");
    exit(1);}
  
}

