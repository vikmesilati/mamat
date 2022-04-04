#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAYA_MONEY 43.94
#define MAX_TOYS 14
#define NUM_OF_TOYS 21
/*Function will use backtracking to locate a list of 13 toys to spend 
all her money
*/
void printHist(int histogram[21],double toys[21]){
    for(int i = 0; i < 21; i++){
        if(histogram[i] == 1){
            printf("%.2lf ",toys[i]);
        }
    }
    printf("\n");

}
void find_toys_list_for_maya(double toys[21],int histogram[21],double expSum, double currentSum,int number,int i){
    if(number == MAX_TOYS){
        if(currentSum == expSum){
            printf("found\n");
            printHist(histogram,toys);
        }
        else{
            return;
        }
    }
    if(currentSum > expSum){
        return;
    }
    if(i == NUM_OF_TOYS){
        return;
    }
    if(histogram[i] == 0){
        histogram[i] = 1;
        find_toys_list_for_maya(toys,histogram,expSum,currentSum + toys[i] ,number+1,i+1);
        histogram[i] = 0;
    }
    find_toys_list_for_maya(toys,histogram,expSum,currentSum,number,i+1);

}

void find_toys_list_for_maya_multi(double toys[21],double expSum, double currentSum,int number,int i,int cnt[1]){
    if(number == MAX_TOYS){
        if(currentSum == expSum){
            // printf("found\n");
            cnt[0]++;
            printf("%lf %d\n",toys[i],cnt[0]);
        }
        return;
    }
    if(currentSum > expSum){
        return;
    }
    if(i == NUM_OF_TOYS){
        // printf("end");
        return;
    }
    // printf("%lf\n",currentSum);
    while(i < 21 && cnt[0] < 10000){
        find_toys_list_for_maya_multi(toys,expSum,currentSum + toys[i],number+1,i,cnt);
        i++;
    }
}

int main(){
    int histogram[NUM_OF_TOYS] = {0};
    double toys[NUM_OF_TOYS] = {1.22,2.75,1.85,5.97,6.47,2.16,7.13,4.57,1.46,
    5.18,3.16,4.89,7.11,6.45,4.77,8.04,6.71,2.31,6.21,0.98,0.87};
    double expSum = MAYA_MONEY;
    double currentSum = 0;
    int i = 0;
    int cnt[1] = {0};
    // find_toys_list_for_maya(toys,histogram,expSum,currentSum,0,i);
    find_toys_list_for_maya_multi(toys,expSum,currentSum,0,i,cnt);
}
