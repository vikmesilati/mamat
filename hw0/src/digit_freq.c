#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define HIST_LEN 10
#define STR_LEN 1000
int main() {
    char str1[STR_LEN];
    int histogram[HIST_LEN];

    for(int i = 0; i < HIST_LEN; i++){
        histogram[i] = 0;
    }
    scanf("%s", str1);
    for(int i = 0; i < strlen(str1); i++){
        if((str1[i] >= '0') && (str1[i] <= '9')){
            histogram[str1[i]-'0']++;
        }
    }
    for(int i = 0; i < HIST_LEN; i++){
        printf("%d ",histogram[i]);
    }
    printf("\n");
    return 0;
}


