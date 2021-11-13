//package com.baeldung.jni;

public class TestJni {

    static {
        System.loadLibrary("native");
    }
    
    public static void main(String[] args) {
        new TestJni().sayHello();
    }

    // Declare a native method sayHello() that receives no arguments and returns void
    private native void sayHello();
}
