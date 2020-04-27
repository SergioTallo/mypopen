#include <stdio.h>

#include "mypopen.h"

#define MAX 1000

FILE *mypopen(const char *command, const char *mode);

int main(void){

    char string[MAX];

    FILE *fp = mypopen("ls -la", "r");
    if (fp == NULL){
        printf("main(): Error in mypopen happened!\n");
    }else{
        while (fgets(string, MAX, fp)!= NULL){
            printf("%s", string);
        }
    }
    
    mypclose(fp);
    return 0;
}