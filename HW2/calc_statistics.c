#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 10
#define PASS_GRADE 55

/*@brief The function reads grades from file and
 * prints statistics on the data
 * @param argc the number of arguments
 * @param argv array with the arguments
 * @return nothing, writes to new file
*/ 
int main(int argc, char *argv[]) {
    	int totalGrades = atoi(argv[2]);	
	FILE *fd = fopen(argv[1],"r");
	int histogram[10][10] = {0};
	double sumGrades = 0;
	double passCourse = 0;
	int grades[totalGrades];
	int max = 0;
	int min = 100;
	int i = 0;
	char* line = malloc(line_size);
	while(fgets(line, LINE_SIZE, fd) != NULL){
		int temp = atoi(line);
		grades[i] = temp;
		sumGrades += temp;
		if(temp >= PASS_GRADE){
			passCourse += 1;
		}
		if(temp > max){
			max = temp;
		}
		if(temp < min){
			min = temp;
		}
		int col = temp % 10;
		int row = temp / 10;
		histogram[row][col]++;
		i++;
	}
	fclose(fd);
	free(line);
	int median = grades[(totalGrades+1)/2];
	double pass = (passCourse / totalGrades)*100;
	FILE *stat;
	
	stat = fopen(argv[3],"w");
	fprintf(stat,"num of students = %d\n",totalGrades);
	fprintf(stat,"avg = %.2f \n",(sumGrades / totalGrades));
	fprintf(stat,"the median is - %d\n",median);
	fprintf(stat,"max grade = %d, ",max);
	fprintf(stat,"min grade = %d \n",min);
	fprintf(stat,"pass rate = %.2f \n",pass);
	for(int j = 0; j < 10; j++){
		for(int k = 0; k < 10; k++){
			fprintf(stat,"%d ",histogram[j][k]);
		}
		fprintf(stat,"\n");
	}
	fclose(stat);
	return 0;
}
