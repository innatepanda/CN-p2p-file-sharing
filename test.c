#include<stdio.h>
#include<jni.h>
#include "TestJni.h"
JNIEXPORT void JNICALL Java_TestJni_sayHello
  (JNIEnv * evn, jobject thisobject){
      printf("Hello from c(Test JNI)\n");
  }
