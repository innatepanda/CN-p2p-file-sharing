g++ -fpic -shared aes_main.cpp -o libaes.so &&
g++ -fpic -shared aes_connector.cpp -L. -laes -o libaes_connector.so &&
gcc hashPassword.c -L. -laes_connector -o c_aes -laes

export LD_LIBRARY_PATH=/home/virtualpanda/Desktop/p2p:$LD_LIBRARY_PATH
./c_aes


