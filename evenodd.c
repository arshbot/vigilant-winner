#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int check1,len,tmp,maxthread;
void sort(void *param,pthread_t threads[]);
void *compare_exchange(void *arg);
void printArr(int *nums);

int main(int argc, char *argv[]){
    tmp = 0;
    check1 = 0;
	int x = 0;
    struct timeval stop, start;
    if(argc!=3){
        printf("You have to enter 1 file and the size of numbers\n");
        return -1;
    }
    len = atoi(argv[2]);
    maxthread = (int)(len+1)/2;
    pthread_t threads[maxthread];
    int numArray[len];
    
    FILE *infile;
    infile = fopen(argv[1], "r");
    if(infile==NULL){
        printf("Error opening file %s!\n",argv[1]);
        return -1;
    }
    else{printf("Opening file %s!\n",argv[1]);
    }
//______read files and input into array______________________________
    while(!feof(infile))
    {
        fscanf(infile,"%d",&numArray[x]);
	x++;
    }
    fclose(infile);
    
    //printArr(numArray);
    gettimeofday(&start, NULL);
    sort(numArray,threads);
    gettimeofday(&stop, NULL);

    printf("----Finished sorting----\n");
    //printArr(numArray);
    double secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Sorting time is %f seconds\n",secs);

return 0;
}


void sort(void *params, pthread_t threads[]){
int *nums = (int *)params;
    int i, j;
    for (i = 1; i <= len; i++) {
        check1=0;
        // Odd step
        if (i % 2 == 1) {
            tmp = 0;
            
            // Creating threads
            for (j = 0; j < maxthread; j++)
                pthread_create(&threads[j], NULL, compare_exchange, nums);
            
            // joining threads i.e. waiting
            // for all the threads to complete
            for (j = 0; j < maxthread; j++)
                pthread_join(threads[j], NULL);
        }
        
        // Even step
        else {
            tmp = 1;
            
            // Creating threads
            for (j = 0; j < maxthread - 1; j++)
                pthread_create(&threads[j], NULL, compare_exchange, nums);
            
            // joining threads i.e. waiting
            // for all the threads to complete
            for (j = 0; j < maxthread - 1; j++)
                pthread_join(threads[j], NULL);
        }
        if(check1==1){
            //printf("Did not pass the sort check\n");
        }
        else{printf("Passed the sort check\n");
	break;}
    }
    }


//compare and swap method
void *compare_exchange(void *arg){
    int index = tmp;
    tmp = tmp + 2;
    int *nums = (int *)arg;
    if ((nums[index] > nums[index + 1]) && (index + 1 < len)) {
        int temp = nums[index];
        nums[index] = nums[index + 1];
        nums[index + 1] = temp;
        check1 =1;
        
    }
   pthread_exit(0);
    
}
//print array
void printArr(int *nums){
    for(int x=0;x<len;x++){
        printf("%d ",nums[x]);
        printf("\n");
    }
}


