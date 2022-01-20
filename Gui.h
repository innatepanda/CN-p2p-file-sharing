/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Gui */

#ifndef _Included_Gui
#define _Included_Gui
#ifdef __cplusplus
extern "C" {
#endif
#undef Gui_FOCUS_TRAVERSABLE_UNKNOWN
#define Gui_FOCUS_TRAVERSABLE_UNKNOWN 0L
#undef Gui_FOCUS_TRAVERSABLE_DEFAULT
#define Gui_FOCUS_TRAVERSABLE_DEFAULT 1L
#undef Gui_FOCUS_TRAVERSABLE_SET
#define Gui_FOCUS_TRAVERSABLE_SET 2L
#undef Gui_TOP_ALIGNMENT
#define Gui_TOP_ALIGNMENT 0.0f
#undef Gui_CENTER_ALIGNMENT
#define Gui_CENTER_ALIGNMENT 0.5f
#undef Gui_BOTTOM_ALIGNMENT
#define Gui_BOTTOM_ALIGNMENT 1.0f
#undef Gui_LEFT_ALIGNMENT
#define Gui_LEFT_ALIGNMENT 0.0f
#undef Gui_RIGHT_ALIGNMENT
#define Gui_RIGHT_ALIGNMENT 1.0f
#undef Gui_serialVersionUID
#define Gui_serialVersionUID -7644114512714619750LL
#undef Gui_serialVersionUID
#define Gui_serialVersionUID 4613797578919906343LL
#undef Gui_INCLUDE_SELF
#define Gui_INCLUDE_SELF 1L
#undef Gui_SEARCH_HEAVYWEIGHTS
#define Gui_SEARCH_HEAVYWEIGHTS 1L
#undef Gui_OPENED
#define Gui_OPENED 1L
#undef Gui_serialVersionUID
#define Gui_serialVersionUID 4497834738069338734LL
#undef Gui_DEFAULT_CURSOR
#define Gui_DEFAULT_CURSOR 0L
#undef Gui_CROSSHAIR_CURSOR
#define Gui_CROSSHAIR_CURSOR 1L
#undef Gui_TEXT_CURSOR
#define Gui_TEXT_CURSOR 2L
#undef Gui_WAIT_CURSOR
#define Gui_WAIT_CURSOR 3L
#undef Gui_SW_RESIZE_CURSOR
#define Gui_SW_RESIZE_CURSOR 4L
#undef Gui_SE_RESIZE_CURSOR
#define Gui_SE_RESIZE_CURSOR 5L
#undef Gui_NW_RESIZE_CURSOR
#define Gui_NW_RESIZE_CURSOR 6L
#undef Gui_NE_RESIZE_CURSOR
#define Gui_NE_RESIZE_CURSOR 7L
#undef Gui_N_RESIZE_CURSOR
#define Gui_N_RESIZE_CURSOR 8L
#undef Gui_S_RESIZE_CURSOR
#define Gui_S_RESIZE_CURSOR 9L
#undef Gui_W_RESIZE_CURSOR
#define Gui_W_RESIZE_CURSOR 10L
#undef Gui_E_RESIZE_CURSOR
#define Gui_E_RESIZE_CURSOR 11L
#undef Gui_HAND_CURSOR
#define Gui_HAND_CURSOR 12L
#undef Gui_MOVE_CURSOR
#define Gui_MOVE_CURSOR 13L
#undef Gui_NORMAL
#define Gui_NORMAL 0L
#undef Gui_ICONIFIED
#define Gui_ICONIFIED 1L
#undef Gui_MAXIMIZED_HORIZ
#define Gui_MAXIMIZED_HORIZ 2L
#undef Gui_MAXIMIZED_VERT
#define Gui_MAXIMIZED_VERT 4L
#undef Gui_MAXIMIZED_BOTH
#define Gui_MAXIMIZED_BOTH 6L
#undef Gui_serialVersionUID
#define Gui_serialVersionUID 2673458971256075116LL
/*
 * Class:     Gui
 * Method:    Cmain
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Gui_Cmain
  (JNIEnv *, jobject);

/*
 * Class:     Gui
 * Method:    Auth
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Gui_Auth
  (JNIEnv *, jobject, jstring, jstring, jint);

/*
 * Class:     Gui
 * Method:    Files
 * Signature: (Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;[III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Gui_Files
  (JNIEnv *, jobject, jstring, jobjectArray, jobjectArray, jintArray, jint, jint);

/*
 * Class:     Gui
 * Method:    getStructArray
 * Signature: ()[Lfileinfo;
 */
JNIEXPORT jobjectArray JNICALL Java_Gui_getStructArray
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
