#ifndef PATCH_H
#define PATCH_H
/*
header file responsible for 
fixing simple bugs at compiling time
-->not develeped for fixing bugs in source code
-->it is for cache mngt and internal monitering
ie loading user's library's etc 

but it is also responsible for booting tokenization process
*/
#include <iostream>
void static inline fix(int instance)
{
    //for fixing small error's on compiler at runtime
    switch (instance)
    {
        //actions
    case 1:
        std::cout << "undefined bug" << std::endl;
    case 2:
        std::cout << "delete intern folder of compiler" << std::endl;
    }
}
#endif