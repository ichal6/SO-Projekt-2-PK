#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#define rowsSize 2
#define colsSize 10

int sumFirstRow, sumSecondRow;
int tableToCalc[rowsSize][colsSize];

void *thread1() {
    for(int i=0; i < colsSize; i++)
        sumFirstRow += tableToCalc[0][i];
    printf("Sum of first row of table = %d\n", sumFirstRow);
    pthread_exit(0);
}

void *thread2(){
    for(int i=0; i < colsSize; i++)
        sumSecondRow += tableToCalc[1][i];
    printf("Sum of second row of table = %d\n", sumSecondRow);
    pthread_exit(0);
}

void fillArray(){
    srand(time(NULL));
    for(int i = 0; i < rowsSize; i++)
        for(int j=0; j<colsSize; j++)
            tableToCalc[i][j]=rand()%50;
}

int main() {
    int finalSum, result;
    pthread_t threadId1, threadId2;

    fillArray();

    result = pthread_create(&threadId1, NULL, thread1, NULL);
    if(result == -1) {
        perror("Cannot create the first thread!");
        exit(1);
    }

    result = pthread_create(&threadId2, NULL, thread2, NULL);
    if(result==-1) {
        perror("Cannot create the second thread!");
        exit(1);
    }

    result = pthread_join(threadId1,NULL);
    if(result == -1) {
        perror("Problem with join the first thread!");
        exit(2);
    }

    result = pthread_join(threadId2,NULL);
    if(result == -1) {
        perror("Problem with join the second thread!");
        exit(2);
    }

    result = pthread_detach(threadId1);
    if(result == -1){
        perror("Problem with detach the first thread!");
        exit(3);
    }

    result = pthread_detach(threadId2);
    if(result == -1){
        perror("Problem with detach the second thread!");
        exit(3);
    }

    finalSum = sumFirstRow + sumSecondRow;

    printf("Sum of all table = %d\n", finalSum);

    return 0;
}
