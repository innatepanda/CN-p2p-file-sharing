# CN-peer-to-peer-file-sharing
### Run the below code on client side.
#### javac -h . Gui.java
#### gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux client.c -o Gui.o
#### gcc -shared -fPIC -o libnative.so Gui.o -lc
#### java -cp . -Djava.library.path=. Gui

### Run the below code on server side.
#### gcc -o ser multiserver.c -lpthread
#### ./ser 4000
