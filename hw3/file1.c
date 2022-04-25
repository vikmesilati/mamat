//file1.c
#include <stdio.h>
#include <stdlib.h>
#include "file1.h"
#include "file0.h"
int file1_function(){
	printf("This is file1_function()\n");
	file0_function();
	return 0;
}
