#include<stdio.h>
#include "Gui.h"
JNIEXPORT jint JNICALL Java_Gui_sayHello
  (JNIEnv *env, jobject obj, jint a, jint b) {
    printf("Hello\n"); 
    return a + b;
}
