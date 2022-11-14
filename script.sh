
g++ -fpic -shared aes_main.cpp -o libaes.so &&
g++ -fpic -shared aes_connector.cpp -L. -laes -o libaes_connector.so &&
#gcc hashPassword.c -L. -laes_connector -o c_aes -laes

#export LD_LIBRARY_PATH=/home/virtualpanda/Desktop/p2p:$LD_LIBRARY_PATH &&

echo "here"
javac -h . Gui.java &&
export LD_LIBRARY_PATH=/home/virtualpanda/Desktop/p2p &&
#gcc hashPassword.c -L. -laes_connector -o c_aes -laes
gcc -c -fPIC -shared -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L{$LD_LIBRARY_PATH} client.c -o  Gui.o -w && 
gcc -fPIC    libaes_connector.so libnative.so   -o Gui.o   -lc && 
java -cp . -Djava.library.path=. Gui 

