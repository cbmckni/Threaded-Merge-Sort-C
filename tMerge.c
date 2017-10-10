/**
  * Name: Cole McKnight
  * Class: CPSC3220
  * File: tMerge.c
  * Last Modified: 10/9/17          
  * Description: A threaded merge sort in C.
  * To Compile: gcc tMerge.c -lpthread        
  **/


#include<stdio.h>
#include <stdlib.h> 
#include<pthread.h>
#include <string.h>

//The number of integers being entered.
#define max 100000
/**
  * IMPORTANT - MAKE SURE MAX IS SET TO THE CORRECT VALUE          
  **/

//Arguments passed to merge_sort
struct tArgs 
{
	int l;
	int h;
	int *data;
};

//Merge Sort: a merge sort function that has been adapted for multithreading.
void  *merge_sort(void *args)
{
    //Assigns the parameter "args" to a pointer, which can then be assigned to a tArgs struct.
	struct tArgs *a = args;
	struct tArgs arg = *a;
	int low;
    low = arg.l;
	int high;
    high = arg.h;
	int mid, temp;
    mid = (low + high)/2;

	//Allocates memory for the two child threads, then creates them. Each thread is joined once
    // it is finished, and the updated array is merged. The thread then exits.
    if(low < high) 
    {
		
		size_t s = sizeof(pthread_t);
    	pthread_t *tid = malloc(2 * s);
		
		temp = arg.h;
		arg.h = mid;
		printf("Creating thread for left half of list index %i-%i \n",arg.l,arg.h);
        pthread_create(&tid[0], NULL, merge_sort, &arg);
		
  		pthread_join( tid[0], NULL );

		arg.h = temp;
		arg.l = mid + 1;
		printf("Creating thread for right half of list index %i-%i \n",arg.l,arg.h);
        pthread_create(&tid[1], NULL, merge_sort, &arg);

        pthread_join( tid[1], NULL );
		
		int a1[max],a2[max];  
		int n1,n2,i,j,k;
		n1=mid-low+1;
		n2=high-mid;

		for(i=0; i<n1; i++)
			a1[i]=arg.data[low+i];
		for(j=0; j<n2; j++)
			a2[j]=arg.data[mid+j+1];

		a1[i]=9999;  // To mark the end of each temporary array
		a2[j]=9999;

		
		i=0;
		j=0;
		for(k=low; k<=high; k++) 
		{ //process of combining two sorted arrays
			if(a1[i]<=a2[j])
				arg.data[k]=a1[i++];
			else
				arg.data[k]=a2[j++];
		}
		
		
		
		free(tid);
		printf("Exiting thread for index %i-%i \n",arg.l,arg.h);
		pthread_exit(&arg);
    }
}

//The main function. Populates array with stdin, calls merge sort, then prints array to stdout
int main()
{
    int i;
	int d[max];
	struct tArgs init; 
	init.l = 0;
	init.h = max-1;
	init.data = d;

    for(i=0;i < max;i++)
    {
        scanf("%d",&init.data[i]);
    }
	printf("\n");
	printf("Unsorted array:\n");
	printf("==========================\n"); 
    for(i=0;i < max;i++)
    {
        printf("%d\n",init.data[i]);
    }
	printf("==========================\n");

	size_t s = sizeof(pthread_t);
    pthread_t *tid = malloc(s);
	printf("Creating initial sorting thread of index %i-%i \n",init.l,init.h);
    pthread_create(&tid[0], NULL, merge_sort, &init);
	pthread_join( tid[0], NULL );
	printf("Joined final thread of index %i-%i \n",init.l,init.h);

	printf("\n");
    printf("Sorted array:\n"); 
	printf("==========================\n");
    for(i=0;i < max;i++)
    {
        printf("%d\n",init.data[i]);
    }
	printf("==========================\n");

    return 0;
}

