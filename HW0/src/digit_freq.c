#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define HIST_LEN 10
#define STR_LEN 1000
// this function prints the number of times a number is in a string
int main() {
    char input[STR_LEN];
    int histogram[HIST_LEN];

    for(int i = 0; i < HIST_LEN; i++){
        histogram[i] = 0;
    }
    scanf("%s", input);
    for(int i = 0; i < strlen(input); i++){
        if((input[i] >= '0') && (input[i] <= '9')){
            histogram[input[i]-'0']++;
        }
    }
    for(int i = 0; i < HIST_LEN; i++){
        printf("%d ",histogram[i]);
    }
    printf("\n");
    return 0;
}


