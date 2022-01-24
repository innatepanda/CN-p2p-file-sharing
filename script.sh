javac -h . Gui.java &&
gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux client.c -o Gui.o &&
gcc -shared -fPIC -o libnative.so Gui.o -lc &&
java -cp . -Djava.library.path=. Gui
