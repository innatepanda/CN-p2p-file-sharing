g++ -fpic -shared aes_main.cpp -o libaes.so &&
g++ -fpic -shared aes_connector.cpp -L. -laes -o libaes_connector.so 
echo "here"
javac -h . Gui.java &&
gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux client.c -o Gui.o &&
gcc -shared -fPIC -o libnative.so libaes.so Gui.o -lc &&
java -cp . -Djava.library.path=. Gui
