#include <stdio.h>
#include <string.h>

#include "mypopen.h"

#define RETURN_FAILURE 0

/**
 * Return:
 *      SUCCESS: FILE*
 *      FAILURE: NULL
*/

FILE* mypopen(const char *command, const char *mode){

    //check if mode == "read" || "write"
        //if error --> return NULL and set errno
    if (strcmp(mode, "r") != 0 && strcmp(mode, "w") != 0){
        printf("Error occured due to incorrect parameter\n");
        // write errno
        return NULL;
    }
    
    int p[2];
    // Create unnamed pipe with pipe() 
        /**
         * int pipe(int fds[2]);
         * Parameters :
         * fd[0] will be the fd(file descriptor) for the 
         * read end of pipe.
         * fd[1] will be the fd for the write end of pipe.
         * Returns : 0 on Success.
         * -1 on error.
        */
    if (pipe(p)!=0){
        printf("Error occured at creating the pipe!\n");
        // write errno
        return NULL;
    }else{
    }
    
    // Create Child process
    int forkResult = fork();
    
    if (forkResult<0){
        printf("Error occured at forking!\n");
        //write errno;
        return NULL;
    }else if (forkResult == 0){
        //In Child Process
        
        //Properly associate stdin or stdout
        
        if (strcmp(mode, "r") == 0){
            //p[0] --> close
            //Map p[1]-->STDOUT_FILENO with dub()
            //p[1] --> close
        }else if (strcmp(mode, "w") == 0){
            //p[1] --> close
            //Map p[0]-->STDIN_FILENO with dub()
            //p[0] --> close


            //Clear what to do when write
        }
        
        //start new shell and execute command
        //Flush required?
        //End process with exit() instead of return to avoid 2 returns
        /* code */
    }else if (forkResult > 0){
        //In Parent Process
        
        
        if (strcmp(mode, "r") == 0){
            //p[1] --> close
            //Map p[0] to the return-filepointer
            //associate fp = fdopen(p[0], "r");
        }else if (strcmp(mode, "w") == 0){
            //p[0] --> close
            //Map p[1] to the return-filepointer
            //associate fp = fdopen(p[1], "w");
        }
        //End process with return fp;
    }
    
    
    //printf("Hello from mypopen!\n");
}

int mypclose(FILE *stream){

    //tbd
    printf("Hello from mypclose!\n");
}