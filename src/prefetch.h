
#ifndef __PREFETCH_H
#define __PREFETCH_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <glob.h>
#include <string>
#include <iostream>


void start_PrefetchSmallFiles(const char *filename);
void * main_PrefetchSmallFiles(void * data);


#endif
