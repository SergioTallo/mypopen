#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#include "mypopen.h"

#define RETURN_FAILURE -1

//int removePipe(void);


/**
 * Return:
 *      SUCCESS: FILE*
 *      FAILURE: NULL
*/

FILE* mypopen(const char *command, const char *mode){

    int p[2];
    int forkResult = -1;

    if (strcmp(mode, "r") != 0 && strcmp(mode, "w") != 0){
        //remove printf
        printf("Error occured due to incorrect parameter\n");
        errno = EINVAL; //Invalid Argument
        return NULL;
    }
    
    if (pipe(p)!=0){
        printf("Error occured at creating the pipe!\n");
        //pipe() might write errno on its own --> ask Galla 
        printf("errno: %d\n", errno);
        //errno = EPIPE; //Broken Pipe
        return NULL;
    }


    // Create Child process
    forkResult = fork();
    if (forkResult<0){
        printf("Error occured at forking!\n");
        //fork() might set errno --> ask Galla
        printf("errno: %d\n", errno);
        return NULL;
    }else if (forkResult == 0){
        //In Child Process
        
        //Properly associate stdin or stdout
        if (strcmp(mode, "r") == 0){

            if(close(p[0]) < 0){
                printf("Error occured at close(p[0])!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }

            if (dup2(p[1], STDOUT_FILENO) < 0){
                printf("Error occured at dup2(p[1], STDOUT_FILENO)!\n");
                //dup2() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            
            if(close(p[1]) < 0){
                printf("Error occured at close(p[1])!\n");
                //close() might set errno --> ask Galla
                exit(EXIT_FAILURE);
            }
        }else if (strcmp(mode, "w") == 0){
            
            if(close(p[1]) < 0){
                printf("Error occured at close(p[1])!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }

            if (dup2(p[0], STDIN_FILENO) < 0){
                printf("Error occured at dup2(p[0], STDIN_FILENO)!\n");
                //dup2() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            
            if(close(p[0]) < 0){
                printf("Error occured at close(p[0])!\n");
                //close() might set errno --> ask Galla
                exit(EXIT_FAILURE);
            }
        }
        //start new shell and execute command

        execl("/bin/sh", "sh", "-c" ,command,NULL);
        printf("Error occured at execl()!\n");
        errno = EINVAL; //Invalid Argument
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);

        //Flush required?

    }else if (forkResult > 0){
        //In Parent Process
        
        if (strcmp(mode, "r") == 0){
            if(close(p[1]) < 0){
                printf("Error occured at close(p[1])!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                return NULL;
            }
            
            FILE* fp = fdopen(p[0], "r");
            if(fp == NULL){
                printf("Error occured at fdopen(p[1], 'r')!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                return NULL;
            }else{
                return fp;
            }
        }else if (strcmp(mode, "w") == 0){
            if(close(p[0]) < 0){
                printf("Error occured at close(p[0])!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                return NULL;
            }
            
            FILE* fp = fdopen(p[1], "w");
            if(fp == NULL){
                printf("Error occured at fdopen(p[1], 'w')!\n");
                //close() might set errno --> ask Galla
                printf("errno: %d\n", errno);
                return NULL;
            }else{
                return fp;
            }

        }
    }
    return NULL;
}

int mypclose(FILE *stream){

    pid_t child_pid = 0;
    pid_t wait_pid;
    int pstatus;
    //int waitreturn = 0;

    if(fclose(stream) != 0){
        printf("Error occured at fclose()!\n");
        //fclose() might set errno --> ask Galla
        printf("errno: %d\n", errno);
        return EXIT_FAILURE;
    }

    while((wait_pid = waitpid(child_pid, &pstatus,0)) != child_pid) 
    {
        if(wait_pid == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            printf("Error occured at waitpid()! Check error number below!\n");
            //waitpid() might set errno --> ask Galla
            printf("errno: %d = %s\n", errno, strerror(errno));
            return RETURN_FAILURE;
        }else{
            if(WIFEXITED(pstatus))
            {
                //printf("exited, status=%d\n", WEXITSTATUS(pstatus));
                return WEXITSTATUS(pstatus);
            }else{
                //printf("Error idk \n");
                return RETURN_FAILURE;
            }
        }
    }

    return RETURN_FAILURE;
}
