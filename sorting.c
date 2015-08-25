/*
filename : sorting.c
author   : Nishant Ghai
*/

// common header files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void swap( int* ptr1 , int* ptr2 )
{
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}


void print_array(int arr[], int arr_size)
{
    int i = 0;
    printf("\n");
    for(i = 0 ; i < arr_size; i++)
    {
        printf("%d ",arr[i]); // leave extra space
    }
    printf("\n");
}

void generate_random_array( int arr[], int arr_size )
{
    int output = 0;
    int counter = 0;

    srand ( (unsigned int)time(NULL) );

    for( counter = 0; counter < arr_size; counter++ )
    {
        arr[counter] = rand() % 1000;
    }
}


/* ================================================ BUBBLE SORT ======================================================= /
/*
In bubble sort we keep comparing two consecutive consecutive array elements and swap the two adjacent nos. if they are out of order
After 1st iteration the larget no. will be at the end.
Keep repeating one size less each time.

For further optimization, keep a flag to check if the array is already sorted in between the quit from the loop.
*/

void bubble_sort(int arr[], int arr_size)
{
    int i = 0 , j = 0;
    int flag_swap_happened = 0;

    for( i = 0 ; i < arr_size-1 ; i++ )  // NOTE "arr_size-1"
    {
        flag_swap_happened = 0;

        for( j = 0; j < arr_size-i-1 ; j++) // NOTE "arr_size-i-1" , last ith element reaches its correct position
        {
            if( arr[j] > arr[j+1])
            {
                swap( &arr[j] , &arr[j+1] );
                flag_swap_happened = 1;
            }
        }

        if( !flag_swap_happened ) //if we come out of any one iteration without making any swap, this means array is already sorted, so break!
            break;
    }
}


/* ================================================ SELECTION SORT ======================================================= */
void selection_sort(int arr[], int arr_size)
{
    int i = 0 , j = 0,  min_index = 0;

    for(i = 0; i < arr_size-1; i++ )
    {
        //find the minimum element in array and bring it to begining of the list
        //keep finding the minimum elements are keep swapping them at position 0,1,2.....arr_size-1

        //find the minimum no of from index i to arr_size-1
        min_index = i;
        for( j = i+1; j < arr_size; j++ )
        {
            if( arr[j] < arr[min_index] )
            {
                min_index = j;
            }
        }


        if( i != min_index)  //swap only if i and min_index are different
            swap( &arr[i], &arr[min_index] );
    }
}

/* ================================================ INSERTION SORT ======================================================= */
void insertion_sort(int arr[], int arr_size)
{
    int i = 0, j = 0, key = 0, temp = 0, min_index = 0 , counter = 0;

    //printf("\nArray in between sorting iterations:\n");

    for( key = 1; key <= arr_size-1; key++)
    {

        min_index = -1;

        //check from arr[0] to arr[key-1], the first element which is greater than key element
        for( i = 0 ; i<=key-1; i++ )
        {
            if( arr[i] > arr[key] )
            {
                min_index = i;
                break;
            }
        }

        if( min_index != -1 )
        {
            //move all the element from min_index to key-1 to one position right
            temp = arr[key];

            for( j = key-1 ; j >= min_index ; j-- )
            {
                arr[j+1] = arr[j];
            }

            arr[min_index] = temp;
        }

        //print_array( arr , arr_size );
    }

}



/* ================================================ COMBO OF SELECTION & INSERTION SORT ======================================================= */
void combo_selection_insertion_sort(int arr[], int arr_size)
{
    int i = 0 , j = 0, counter = 0, min_index = 0, temp = 0;

    //printf("\nArray in between sorting iterations:\n");

    for(i = 0; i < arr_size-1; i++ )
    {
        //find the minimum element in array and move the array to one position right
        //to insert the minimum no. at the beginning

        //find the minimum no of from index i to arr_size-1
        min_index = i;
        for( j = i+1; j < arr_size; j++ )
        {
            if( arr[j] < arr[min_index] )
            {
                min_index = j;
            }
        }


        if( i != min_index)  //move elements only if i and min_index are different
        {
            //save the minimum no.
            temp = arr[min_index];

            //move the array elements from index i to min_index-1 one position to the right
            for(counter = min_index-1 ; counter >= i ; counter-- )
            {
                arr[counter+1] = arr[counter];
            }

            arr[i] = temp;
        }

        //print_array( arr , arr_size );
    }
}


/* ================================================ MERGESORT ======================================================= */

// merge the left and Right arrays back by over-writing into arr
void merge( int arr[] , int L[], int leftArraySize, int R[], int rightArraySize )
{
    int i = 0; // index of sub array L
    int j = 0; // index of sub array R
    int k = 0; // index of array arr

    while( i<leftArraySize && j< rightArraySize)
    {
        if(L[i]  < R[j]) 
        {
                arr[k] = L[i];
                i++;
        }
        else
        {
                arr[k] = R[j];
                j++;
        }
        k++;
    }

    //merge the rest of the remaining left array
    while(i < leftArraySize)
    {
        arr[k] = L[i];
        k++;
        i++;
    }

    //merge the rest of the remaining right array
    while( j < rightArraySize )
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}



void mergesort(int arr[], int arr_size)
{
    int mid = 0, i = 0, *L = NULL, *R = NULL;
    int size_left_arr = 0, size_right_arr = 0;

    if( arr_size < 2 )
    {
        return; // exit condition from recursion, if array has less than 2 elements, i.e. only one element, the array is sorted already.
    }
    else
    {
        mid = arr_size / 2;

        size_left_arr = mid;
        size_right_arr = arr_size-mid;

        L = (int*) calloc( size_left_arr , sizeof(int) );
        R = (int*) calloc( size_right_arr , sizeof(int) );


        for( i=0; i<size_left_arr ; i++)
            L[i] = arr[i];

        for(i=0; i< size_right_arr; i++)
            R[i] = arr[mid+i];

        //printf("\nLeft array : ");
        //print_array( L , mid );

        //printf("\nRight array : ");
        //print_array( R ,  (arr_size-mid)  );

        mergesort( L, size_left_arr); //sort the left sub-array
        mergesort( R, size_right_arr ); //sort the left sub-array
        merge( arr , L, size_left_arr, R, size_right_arr ); //merge the left and right sorted arrays into the main list

        free( L );
        L=NULL;
        free( R );
        R=NULL;
    }
}




/* ================================================ main() ======================================================= */
int main(int argc, char* argv[])
{

    int *arr = NULL;
    int default_array_size = 9;
    int arr_size = 0;
    int result = -1;

    if( argc >1 )
    {
        //There is some command argument, try to interpret it, try argv[1] , as argv[0] is the program name
        result = atoi( argv[1] );
        if( !result )
        {
            printf("\nAs command arguments were invalid, assuming array size to be %d.\n", default_array_size);
            arr_size = default_array_size;
        }
        else
        {
            printf("\nUsing array size as in command arguments: %d\n", result);
            arr_size = result;
        }
    }
    else
    {
        //there is no command argument
        printf("\nAs command arguments were not entered, assuming array size to be %d.\n", default_array_size);
        arr_size = default_array_size;
    }


    arr = (int*)calloc( arr_size, sizeof(int) );
    generate_random_array( arr , arr_size);

    printf("\nArray before sorting:\n");
    print_array( arr , arr_size );


    //bubble_sort( arr , arr_size );
    //selection_sort( arr, arr_size );
    //combo_selection_insertion_sort( arr, arr_size );
    //insertion_sort( arr , arr_size );
    mergesort( arr , arr_size );

    printf("\nArray after sorting:\n");
    print_array( arr , arr_size );

    free(arr);
    arr = NULL;


    printf("\n\n");
    return 0;
}

//end of file

