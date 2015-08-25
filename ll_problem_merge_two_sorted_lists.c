#include <stdio.h>
#include <stdlib.h>

/*
This is a solution to merging two sorted linked lists, by creating a new linked list.
Original lists are not modified.
Duplicates in the new list are avoided.
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
    Node *temp = NULL, *end = NULL;

    *ptrNewlist = NULL;

    while( list1 !=NULL && list2 !=NULL )
    {
        /*START : logic to skip duplicates from source list and new list*/
        if( end != NULL )
        {
            while( (list1 != NULL) && (end->data == list1->data ) )
            {
                list1 = list1->next;
            }

            while( (list2 != NULL ) && (end->data == list2->data) )
            {
                list2 = list2->next;
            }
        }

        if( list1 == NULL || list2 == NULL )
        {
            break;
        }
        /*END : logic to skip duplicates from source list and new list*/

        temp = (Node*)malloc(sizeof(Node));

        if( list1->data < list2 ->data )
        {
            temp->data = list1->data;
            list1 = list1->next;
        }
        else 
        {
            temp->data = list2->data;
            list2 = list2->next;
        }
        temp->next = NULL;

        if( *ptrNewlist == NULL )
        {
            *ptrNewlist = temp;
            end = temp;
        }
        else
        {
            end->next = temp;
            end = temp;
        }
    }

    if( list1 == NULL )
    {
        //copy rest of list2 to new_list
        while( list2 !=NULL )
        {
            if( end->data == list2->data )
            {
                list2 = list2->next;
            }
            else
            {
                temp = (Node*) malloc(sizeof (Node));
                temp->data = list2->data;
                temp->next = NULL;
                
                if( *ptrNewlist == NULL )
                {
                    *ptrNewlist = temp;
                    end = temp;
                }
                else
                {
                    end->next = temp;
                    end = temp;
                }

                list2 = list2->next;
            }
        }
    }

    if( list2 == NULL )
    {
        //copy reset of list1 to new_list

        while( list1 !=NULL )
        {
            if( end->data == list1->data )
            {
                list1 = list1->next;
            }
            else
            {
                temp = (Node*) malloc(sizeof (Node));
                temp->data = list1->data;
                temp->next = NULL;

                if( *ptrNewlist == NULL )
                {
                    *ptrNewlist = temp;
                    end = temp;
                }
                else
                {
                    end->next = temp;
                    end = temp;
                }


                list1 = list1->next;
            }
        }
    }
}


int main(void)
{
    Node *head1 = NULL, *head2 = NULL , *new_list = NULL;

    int sorted_arr1[] =  {80};//{6,6,6}; //{ 11,17,25,29,31,59,102, 115, 167 };
    int sorted_arr2[] = { 6,17,29,45,59,59,59 };

    int sorted_arr1_size = ( sizeof( sorted_arr1 ) / sizeof(int) );
    int sorted_arr2_size = ( sizeof( sorted_arr2 ) / sizeof(int) );

    create_list( &head1, sorted_arr1, sorted_arr1_size );
    create_list( &head2, sorted_arr2, sorted_arr2_size );

    merge_sorted_lists( &new_list , head1 , head2 );

    printf("\nThe sorted linked list-1 is : \n");
    print_linked_list( head1);
    
    printf("\n\nThe sorted linked list-2 is : \n");
    print_linked_list( head2);

    printf("\n\nThe merged list is : \n");
    print_linked_list( new_list );

    printf("\n\n");
    return 0;
}
//end of file
