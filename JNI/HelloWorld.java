public class HelloWorld {
    static{
        System.loadLibrary("java_c");
    }    
    public native void DisplayHello();

    public static void main(String[] args) {
       
       try {
        System.out.print("Java Test");
        new HelloWorld().DisplayHello();
       } catch (Exception e) {
           //TODO: handle exception
           System.out.print("Java Test Fail");
           e.printStackTrace();
       }
    }
}
// javac -h . Hello.java
// gcc -c -I"%JAVA_HOME%/include" -I"%JAVA_HOME%/include/win32" Hello.c -o Hello.o
// You12:07 AM
// gcc -shared -o hello.dll Hello.o -Wl, --add-stdcall-alias
// java -cp . -Djava.library.path="java_c/x64/Debug" HelloWorld