#include<stdio.h>
#include <stdlib.h> 
#include<pthread.h>
#include <string.h>

#define max 10

//A buffer that is used to lock the data to prevent race conditions.
struct BoundedBuffer 
{
    pthread_t readThread;
    pthread_mutex_t mutexBuffer;
} buffer2;

//Arguments passed to merge_sort
struct tArgs 
{
	struct BoundedBuffer b;
	int arr1[max];  
	int arr2[max];
	int l;
	int h;
};

//global variables
int numthreads;

void * merge_sort(void *args);

int main()
{
	numthreads = 0;
    int i;
	struct tArgs init; 
	init.l = 0;
	init.h = max-1;
	init.b = buffer2;

    for(i=0;i < max;i++)
    {
        scanf("%d",&init.arr1[i]);
    }
	printf("\n");
	printf("Unsorted array:"); 
    for(i=0;i < max;i++)
    {
        printf("%d ",init.arr1[i]);
    }
	printf("\n");

    merge_sort(&init);
  
	printf("\n");
    printf("Sorted array:"); 
    for(i=0;i < max;i++)
    {
        printf("%d ",init.arr1[i]);
    }
    return 0;
}

void  *merge_sort(void *args)
{
	
	printf("\n");
	numthreads++;
	printf("%i", numthreads);
	int i = 0;
	

	struct tArgs *a = args;
	printf("\n");
    printf("Sorted array:"); 
    for(i=0;i < max;i++)
    {
        printf("%d ",a->arr1[i]);
    }
	printf("\n");

	struct tArgs arg = *a;
	int low;
    low = arg.l;
	int high;
    high = arg.h;

    size_t s = sizeof(pthread_t);
    pthread_t *tid = malloc(2 * s);
    if(low < high) 
    {
		int mid, temp;
        mid = (low + high)/2;

		temp = arg.h;
		arg.h = mid;
		
        //pthread_create( &a->b.readThread, NULL, merge_sort, &arg);
		merge_sort(&arg);

		arg.h = temp;
		arg.l = mid + 1;
		merge_sort(&arg);
        //pthread_create( &a->b.readThread, NULL, merge_sort, &arg);
		
        
		pthread_mutex_lock(&a->b.mutexBuffer);

		int a1[max],a2[max];  
		int n1,n2,i,j,k;
		n1=mid-low+1;
		n2=high-mid;

		for(i=0; i<n1; i++)
			a1[i]=a->arr1[low+i];
		for(j=0; j<n2; j++)
			a2[j]=a->arr1[mid+j+1];

		a1[i]=9999;  // To mark the end of each temporary array
		a2[j]=9999;

		
		i=0;
		j=0;
		for(k=low; k<=high; k++) 
		{ //process of combining two sorted arrays
			if(a1[i]<=a2[j])
				a->arr1[k]=a1[i++];
			else
				a->arr1[k]=a2[j++];
		}

		pthread_mutex_unlock(&a->b.mutexBuffer);

		//pthread_join(a->b.readThread, NULL);
        //pthread_join( tid[0], NULL );
        //pthread_join( tid[1], NULL );
		free(tid);
    }
}

