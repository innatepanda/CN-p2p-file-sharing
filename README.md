# CN-peer-to-peer-file-sharing
### Run the below code if change java file .
#### javac -h . Gui.java
#### gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux Gui.c -o Gui.o
#### gcc -shared -fPIC -o libnative.so Gui.o -lc
#### java -cp . -Djava.library.path=. Gui
### If didn't change java file then simply run
#### java -cp . -Djava.library.path=. Gui

