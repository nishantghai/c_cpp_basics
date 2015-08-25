#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node* next;
}Node;


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

void remove_duplicates_sorted( Node* ptrHead )
{
    Node *curr = NULL, *next_node = NULL;
    
    if( ptrHead == NULL )
    {
        return;
    }

    curr = ptrHead;
    next_node = curr->next;

    while( next_node != NULL )
    {
        if( curr->data == next_node->data )
        {
            Node* save = next_node;
            curr->next = next_node->next;
            free( save );
            next_node = curr->next;
        }
        else
        {
            curr = curr->next;
            next_node = next_node->next;
        }
    }
}


int main(void)
{
    Node *head = NULL;

    int sorted_arr[] =  {1,3,3,8,10};//{ 122, 122, 122, 122, 122, 200 };
    int sorted_arr_size = ( sizeof( sorted_arr ) / sizeof(int) );

    create_list( &head, sorted_arr, sorted_arr_size );

    printf("\nOriginal sorted linked list:\n");
    print_linked_list( head );

    remove_duplicates_sorted( head );

    printf("\n\nNew linked list:\n");
    print_linked_list( head );

    printf("\n\n");
    return 0;
}

//end of file
