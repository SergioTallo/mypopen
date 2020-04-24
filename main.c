#include <stdio.h>

#include "mypopen.h"

FILE *mypopen(const char *command, const char *mode);

int main(int argc, char** argv){

    mypopen(NULL, "w");
    mypclose(NULL);
    return 0;
}