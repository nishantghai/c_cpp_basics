/*
filename : problem_02_find_all_pairs_with_sum_k.c
author : Nishant Ghai
Problem :  Given a sorted array of numbers, print all pairs of numbers that have sum a given value 'k'

Solution: Here, we iterate through the sorted array, check for pair from left and right simultaneously.
move the left and right ends accordingly

Here the runtime complexity of the algorithm is O(n)

*/

#include <stdio.h>


int main()
{
    int arr[] = { 2,5,8,13,17,28,89 };
    int k =  30; 
    int i = 0 , arr_size = 0 , sum = 0;
    int left = 0, right = 0;


    arr_size = ( sizeof( arr ) / sizeof ( int ) );
    
    printf("\nInput sorted array is:\n");
    for( i=0 ; i<=arr_size-1; i++)
    {
        printf("%d\t",arr[i]);
    }


    printf("\n\nFollowing are the pairs of numbers in given sorted array sum %d\n", k);
    
    left = 0;
    right = arr_size-1;

    while( left < right )
    {
        sum =  arr[left] + arr[right];
        if( sum == k )
        {
            printf("%d and %d\n",arr[left],arr[right]);
            left++;
            right--;
        }
        else if( sum < k )
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    printf("\n\n");
    return 0;
}


//end of file
