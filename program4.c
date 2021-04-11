#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

unsigned COMPCOUNT;

void SWAP(int arr[],int indexOne,int indexTwo){
  // given an int array, swap item at indexOne with item at indexTwo
    int temp = arr[indexOne];
    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = temp;
}
void printArray(int arr[], int n){
  //given an array arr, and it's length n, print array
  int i;
  for (i=0; i<n; i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}
int myrandom(int lowerBound, int upperBound){
  // return random integer in between lower bound and upper bound
    int i, num;
    for (i=0; i<1;i++){
        num = (rand() % (upperBound - lowerBound +1))+ lowerBound;
    }
    return num;
}
int *push(int arr[],int n, int elem){
  // int i;
  printf("Pushing %d\n",elem);
  //increase arr size by 1 int, put n in last place
  const int *temp = arr;//create const char* to original arr
  // printf("Printing temp:\n");
  // printArray((int*)temp,n);
  // printf("Array before push:\n");
  // printArray(arr,n);
  int *newmem = malloc(sizeof(int)*(n+1));//allocate mem for n+1 array
  // for(i=0;i<n;i++){
  //
  // }
  memcpy(newmem,temp,sizeof(int)*n);//copy original array to allocated arr
  newmem[n]=elem;//add elem to new arr
  // printf("Array after push:\n");
  // printArray(newmem,(n+1));
  // free(arr);//free original Array
  arr=newmem;
  // printf("resulting arr:\n");
  // printArray(arr,(n+1));
  return arr;
}

bool COMPARE(int x, int y,int op){ //returns 1 if True 0 if false
    COMPCOUNT++;
    int c=op; // this is the operation, 0: >, 1: < , 2: ==, 3: >=, 4: <=,
    switch(c) {
        case 0:
            return ((x > y) ? true:false);
        case 1:
            return ((x < y) ? true:false);
        case 2:
            return ((x == y) ? true:false);
        case 3:
            return ((x >= y) ? true:false);
        case 4:
            return ((x <= y) ? true:false);
        default:
            return false;
    }
}

//Start insertionSort
bool SMALLER(int arr[],int key,int j){
  COMPCOUNT++;
  if (j>= 0 && key < arr[j]){
    return true;
}
  else{
    return false;
}
}
void insertionSort(int arr[], int n){
  COMPCOUNT = 0;
  int i, key, j;
  for(i=1;i<n;i++){
    key = arr[i];
    j = i-1;
    bool keyComparison = SMALLER(arr,key,j);
    while (keyComparison){
      arr[j+1] = arr[j];
      j = j-1;
      keyComparison = SMALLER(arr,key,j);
    }
    arr[j+1] = key;
  }
}
//end insertion_sort

//Start QUICKSORT
void cQuickSort(int arr[],int left, int right){
    if(left >= right){
        return;
    }
    int k = myrandom(left,right); // init random pivot index
    int pivot = arr[k]; // find the value at pivot
    SWAP(arr,arr[left],arr[right]);
    int l=left+1;
    int r = right;
    //inward scan to partition
    while (l <= r){
        while (l<=r && COMPARE(arr[l],pivot,4)){
            l=l+1;
        }
        while(l<=r && COMPARE(arr[r],pivot,0)){
            r=r-1;
        }
        if(l<r){
            SWAP(arr,arr[l],arr[r]);
            l=l+1;r=r-1;
        }
    }
    SWAP(arr,arr[left],arr[r]);
    cQuickSort(arr,left,r-1);
    cQuickSort(arr,r+1,right);
}
//end QuickSort



int *randomArray(int n, int arr[]){
  //create a random array size n, store in int array arr
    srand((unsigned)time(NULL));
    for (int i=0;i<n;i++){
        arr[i] = (rand() %n);
    }
    return arr; /* returns integer pointer to first value in array */
}
int *bestCase(int n, int arr[]){
  // create a sorted array size n, store in int array arr
    for(int i=0;i<n;i++){
        arr[i] = i;
    }
    return arr;
}
int *worstCase(int n, int arr[]){
  // create an unsorted array of size n, store in int array arr
    for(int i=0;i<n;i++){
        arr[i] = n-i;
    }
    return arr;
}

void SELECT1(int arr[], int n, int k){
  // select the kth smallest element in arr of size n
  // quicksort arr, return kth smallest item
  int select;
  cQuickSort(arr,0, n-1);// 1. Sort using QuickSort
  select = arr[k-1];// get kth smallest element
  printf("Algorithm SELECT1: %d, %d, %d, %u\n",n,k,select,COMPCOUNT);//output to file
}
void SELECT2(int arr[], int n, int k){
  //quickselect
  //if n<25, sort array using insertion sort, return kth smallest element
  printf("Running SELECT2\n");
  printArray(arr,n);
  int select;
  if(n<25){
    insertionSort(arr,n);
    select = arr[k-1];
    printf("Finishing Algorithm SELECT2: %d, %d, %d, %u\n",n,k,select,COMPCOUNT);//output to file
    // return select;
  }
  else{
    srand((unsigned)time(NULL));
    int i,n1=0,n2=0,n3=0,pivot,V;
    int *L = malloc(sizeof(int)*1);
    int *E = malloc(sizeof(int)*1);
    int *G = malloc(sizeof(int)*1);
    pivot = rand() %n; // pivot = random number in span of n
    V = arr[pivot];
    printf("V: %d\n",V);

    for(i=0;i<n-1;i++){
      if(COMPARE(V,arr[i],1)){
        // printf("Adding to G: %d\n",arr[i]);
        if(n3==0){
          //dont push, array is big enough to hold arr[i]
          G[0]=arr[i];
          // printArray(G,1);
        } else {
          //add arr[i] to G
          //Push arr[i] to G, n3 = len of G
          G = push(G,n3,arr[i]);
          // printf("Push ended, resulting arr: \n");
          // printArray(G,n3+1);
        }
        // G[i]=arr[i];
        n3++;
        // printArray(G,n-1);
      }
      else if(COMPARE(V,arr[i],0)){
        //add arr[i] to L
        // printf("Adding to L: %d\n",arr[i]);
        if (n1==0){
          L[0]=arr[i];
          // printArray(L,1);
        } else {
          L = push(L,n1,arr[i]);
          // printf("Push ended, resulting arr: \n");
          // printArray(L,n1+1);
        }
        // L[i]=arr[i];
        n1++;
        // printArray(L,n-1);
      } else {
        //add arr[i] to E
        // printf("Adding to E: %d\n",arr[i]);
        if (n2==0){
          E[0]=arr[i];
          // printArray(E,1);
        } else {
          E= push(E,n2,arr[i]);
          // printf("Push ended, resulting arr: \n");
          // printArray(E,n2+1);
        }
        // E[i]=arr[i];
        n2++;
        // printArray(E,n);
      }
    }
    //recursive start
    if(k<n1){
      k=n1/2;
      SELECT2(L,n1,k);
    }
    else if(k<n1+n2){
      printf("Returning V: %d\n",V);
      // return(V);
    }
    else{
      k=n3/2;
      SELECT2(G,n3,k-n1-n2);
    }
    // recursive end
    free(L);
    free(E);
    free(G);
  }
}
void selectRun(int *p,int n, int op){
  //given a pointer to int array, of size n, and an op code signifying which operation to run
    double cpuTimeUsed;
    clock_t start,end;
    int k;
    COMPCOUNT=0;
    k=n/2;
    if(op==1){
        //run Select1
        int temp;
        printf("Running (SELECT 1)\n");
        start=clock();
        cQuickSort(p,0,n-1);
        temp = p[k-1];
        end=clock();
        cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("Algorithm SELECT1: %d, %d, %d, %u\n",n,k,temp,COMPCOUNT);//output to file
        printf("Total Runtime: %lf \n\n",cpuTimeUsed);
    }
    else if(op==2){
      //run quickselect (SELECT2)
      // int temp;
      SELECT2(p,n,k);
      // printf("SELECT 2 RESULTS: %d",temp);
    }
    // if(op == 0){
    //     //run mergesort
    //     printf("Running Merge-sort: \n");
    //     start=clock();
    //     mergeSort(p,0,n-1);
    //     end=clock();
    //     cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
    //     printf("Total Runtime: %lf \n",cpuTimeUsed);
    //     printf("Total Comparisons: %d \n",COMPCOUNT);
    // }
    // else if(op==1){
    //     //run quicksort
    //     printf("Running Quicksort: \n");
    //     start=clock();
    //     cQuickSort(p,0,n-1);
    //     end=clock();
    //     cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
    //     printf("Total Runtime: %lf \n",cpuTimeUsed);
    //     printf("Total Comparisons: %d \n",COMPCOUNT);
    // }
    // else{
    //     //run heapsort
    //     printf("Running Heapsort: \n");
    //     start=clock();
    //     myheapsort(p,n);
    //     end=clock();
    //     cpuTimeUsed = ((double) (end-start))/CLOCKS_PER_SEC;
    //     printf("Total Runtime: %lf \n",cpuTimeUsed);
    //     printf("Total Comparisons: %d \n",COMPCOUNT);
    // }
    if(n<1000){
        printArray(p,n);//print sorted array if n<1024
    }
}
void analyzeFunction(int n,int op){
    int *arr = malloc(sizeof(int)*n); //malloc int array size n
    int *p;
    //init random (0), bestCase (1), or worstCase(2) arrays
    if (op==0){ // 0= random variables
        printf("Random Array: n= %d \n",n);
        p=randomArray(n,arr); //init array of random vars
    }
    else if (op==1){
        printf("Best Case Array: n = %d \n",n);
        p=bestCase(n,arr); //init array of best case scenario
    }
    else{
        printf("Worst Case Array: n = %d \n",n);
        p=worstCase(n,arr); //init array of worst case scenario
    }
    //end init array

    //print init array if n is small
    if(n<1000){
        printArray(p,n);//print unsorted array if n<1000
    }

    // run all select algos on this array
    // for(int i=0;i<3;i++){
    //     selectRun(p,n,i);
    // }

    //test selectRun on op=1
    // selectRun(p,n,1);
    selectRun(p,n,2);

    //free maloc arr
    // free(arr);
}
void analyzeFunctions(int n){
    // if (n<=32){
    //     for(int i=0;i<3;i++){
    //         analyzeFunction(n,i);
    //     }
    // }
    // else{
        analyzeFunction(n,0);
    // }
}

int main(int argc, char *argv[]){
  // run on n = 10,000 ; 100,000 ; 1000000
  // for each n, generate random Array
  // use each of 3 methods to find kth smallest element for k=n/2
  // one line return: Algorithm X: n,k,A[k], Number of Key-Comparisons
  // output to text file for submission
    int n = 100000; // initialize array size 32
    printf("Running analysis on n=32...\n");
    analyzeFunctions(n);
    //
    // printf("Running analysis on n=100,000...\n");
    // n=100000;
    // analyzeFunctions(n);
    //
    // printf("Running analysis on n=1000000...\n");
    // n=1000000;
    // analyzeFunctions(n);
    // return 0;
}
