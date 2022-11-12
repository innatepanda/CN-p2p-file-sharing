#include <cstdlib>

#include "aes_connector.h"
#include "aes_header.h"

#ifdef __cplusplus
extern "C" {
#endif

// Inside this "extern C" block, I can implement functions in C++, which will externally 
//   appear as C functions (which means that the function IDs will be their names, unlike
//   the regular C++ behavior, which allows defining multiple functions with the same name
//   (overloading) and hence uses function signature hashing to enforce unique IDs),



void AES_enc( char *name) {
    aes_main(name);
}

#ifdef __cplusplus
}
#endif
