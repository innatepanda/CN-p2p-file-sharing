g++ -fpic -shared aes_main.cpp -o libaes.so &&
g++ -fpic -shared aes_connector.cpp -L. -laes -o libaes_connector.so &&
gcc hashPassword.c -L. -laes_connector -o c_aes -laes


