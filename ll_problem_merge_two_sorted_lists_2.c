#include <stdio.h>
#include <stdlib.h>

/*
This is a solution to merging two sorted linked lists, without creating new nodes.
Original lists get modified.
Duplicates are not avoided.
*/

typedef struct Node
{
    int data;
    struct Node* next;
}Node;


void create_list( Node** ptrHead, int arr[], int arr_size )
{
    int i=0;
    Node* temp = NULL;

    if( arr_size < 1) //invalid array size
    {
        printf("\nInvalid array size %d\n",arr_size);
        return;
    }

    for( i=arr_size-1; i>=0; i-- )
    {
        temp = (Node*)malloc(sizeof(Node));
        temp->data = arr[i];
        temp->next = (*ptrHead);
        (*ptrHead) = temp;
    }
}


void print_linked_list( Node* head )
{
    if( head == NULL )
    {
        return;
    }
    else
    {
        printf("%d\t",head->data);
        print_linked_list( head->next );
    }
}


void merge_sorted_lists(Node** ptrNewlist, Node* list1, Node* list2 )
{
    Node *last = NULL;
    
    (*ptrNewlist) = NULL;

    while( list1 != NULL && list2 != NULL )
    {
        if( list1->data < list2->data  )
        {
            if(*ptrNewlist == NULL)
            {
                *ptrNewlist = list1;
                last = *ptrNewlist;
            }
            else
            {
                last->next = list1;
                last = list1;
            }
            list1 = list1->next;
            last->next = NULL;
        }
        else
        {
            if(*ptrNewlist == NULL)
            {
                *ptrNewlist = list2;
                last = *ptrNewlist;
            }
            else
            {
                last->next = list2;
                last = list2;
            }
            list2 = list2->next;
            last->next = NULL;
        }
    }

    if( list1 == NULL && list2 != NULL )
    {
        if( *ptrNewlist == NULL )
        {
            *ptrNewlist = list2;
        }
        else
        {
            last->next = list2;
        }
    }
    
    if( list2 == NULL && list1 != NULL )
    {
        if( *ptrNewlist == NULL )
        {
            *ptrNewlist = list1;
        }
        else
        {
            last->next = list1;
        }
    }
}




int main(void)
{
    Node *head1 = NULL, *head2 = NULL , *new_list = NULL;

    int sorted_arr2[] = {8};//{80}; //{ 10,20,30,40,50 };  //{80};//{6,6,6};
    int sorted_arr1[] = { 15,25,50,50,60 };

    int sorted_arr1_size = ( sizeof( sorted_arr1 ) / sizeof(int) );
    int sorted_arr2_size = ( sizeof( sorted_arr2 ) / sizeof(int) );

    create_list( &head1, sorted_arr1, sorted_arr1_size );
    create_list( &head2, sorted_arr2, sorted_arr2_size );

    printf("\nThe sorted linked list-1 is : \n");
    print_linked_list( head1);
    
    printf("\n\nThe sorted linked list-2 is : \n");
    print_linked_list( head2);

    // merge sorted lists list1 and list2
    // do not create new nodes for new list
    merge_sorted_lists( &new_list , NULL , head2 );

    printf("\n\nThe merged list is : \n");
    print_linked_list( new_list );

    printf("\n\n");
    return 0;
}
//end of file
