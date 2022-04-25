//file0.c
#include <stdio.h>
#include <stdlib.h>
#include "file0.h"
#include "file1.h"
#include "file2.h"
#include "file3.h"
#include "file4.h"
int file0_function(){
	printf("This is file0_function()\n");
	file1_function();
	file2_function();
	file3_function();
	file4_function();
	return 0;
}
