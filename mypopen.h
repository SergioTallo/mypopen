#ifndef MYPOPEN_H
#define MYPOPEN_H

#include <stdio.h>

extern FILE *mypopen(const char *command, const char *mode);
extern int mypclose(FILE *stream);

#endif