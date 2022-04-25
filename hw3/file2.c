//file2.c
#include <stdio.h>
#include <stdlib.h>
#include "file2.h"
#include "file1.h"
#include "file3.h"
int file2_function(){
	printf("This is file2_function()\n");
	file1_function();
	file3_function();
	return 0;
}
