/*
filename : problem_01_find_all_pairs_with_sum_k.c
author : Nishant Ghai
Problem :  Given a sorted array of numbers, print all pairs of numbers that have sum a given value 'k'

Solution: Here, we iterate through the array, check for remainder pair in rest of the array using binary search
The runtime complexity of this solution is O(nlogn)

*/

#include <stdio.h>

int binary_search( int arr[], int low, int high, int x )
{
    int result = -1;
    int mid = low + (( high - low )/2);

    if( low > high )
    {
        return -1;
    }
    
    if( x == arr[mid] )
    {
        return mid;
    }
    else if( x < arr[mid])
    {
        return binary_search( arr, low, mid-1, x);
    }
    else
    {
        return binary_search( arr, mid+1, high, x);
    }
}

int main()
{
    int arr[] = { 2,5,8,13,17,28,89 };
    int k =  7; 
    int i = 0 , arr_size = 0 , result = -1;


    arr_size = ( sizeof( arr ) / sizeof ( int ) );
    
    printf("\nInput sorted array is:\n");
    for( i=0 ; i<=arr_size-1; i++)
    {
        printf("%d\t",arr[i]);
    }


    printf("\n\nFollowing are the pairs of numbers in given sorted array sum %d\n", k);
    
    for( i=0 ; i<=arr_size-2; i++)  //NOTE: "arr_size-2" because, we have to search rest of the array so array size of atleast 1, when second last element is entered
    {
        if( arr[i] > k )
        {
            //if individual element is more than "k" , no more pairs of numbers in the rest of the array
            break;
        }

        result = binary_search( arr, i+1, arr_size-1, (k-arr[i]) );
        if( result != -1 )
        {
            printf("\n%d and %d",arr[i],arr[result]);
        }
    }


    printf("\n\n");
    return 0;
}


//end of file
