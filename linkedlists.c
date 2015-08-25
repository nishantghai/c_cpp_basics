/*
filename : linkedlists.c
author : Nishant Ghai
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;


//get a random number less than 1000
int generate_random_Num()
{
    int random_num = 0;
    
    random_num = rand() % 1000;
    return random_num;
}

/************** create a random linked list of given size ******************/
void create_random_linked_list(Node** ptrHead, int nSize)
{
    int i = 0;

    if( nSize < 1 )
    {
        printf("\nInvalid list size\n");
        *ptrHead = NULL;
        return;
    }


    for( i = 0; i < nSize; i++ )
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = generate_random_Num();
        if( i > 0 )
        {
            temp->next = *ptrHead;
        }
        else
        {
            temp->next = NULL;
        }
        *ptrHead = temp;
    }
}

/************** Reverse a linked list using recursion************************/
/****** This function reverses a linked list using recursion ****/
void reverse_linked_list_recursion(Node** ptrHead )
{
    if( *ptrHead == NULL )
    {
        return;
    }
    else
    {
        Node* curr = *ptrHead;
        Node* rest = curr->next;

        if( rest != NULL )
        {
            reverse_linked_list_recursion( &rest );
            curr->next->next = curr;
            curr->next = NULL;
            *ptrHead = rest;
        }
    }
}


/************** Reverse a linked list ************************/
/****** This function reverses a linked list iteratively ****/
void reverse_linked_list(Node** ptrHead)
{
    if( *ptrHead == NULL )
    {
        printf("\nThe linked list is empty.\n");
    }
    else
    {
        Node *curr = NULL, *save = NULL, *new_list = NULL;
        curr = *ptrHead;
        while( curr != NULL )
        {
            save = curr->next;
            curr->next = new_list;
            new_list = curr;
            curr = save;
        }
        *ptrHead = new_list;
    }
}

/************** print elements of a linked list in reverse order ******************/
/*This list only prints in reverse order, does not actually reverse the linked list */
void print_linked_list_in_reverse_order( Node* ptrHead )
{
    if( ptrHead == NULL)
    {
        return;
    }
    else
    {
        print_linked_list_in_reverse_order( ptrHead->next );
        printf("%d\t", ptrHead->data);
    }
}


/************** print elements of a linked list using recursion ******************/
void print_linked_list_using_recursion( Node* ptrHead )
{
    if( ptrHead == NULL)
    {
        return;
    }
    else
    {
        printf("%d\t", ptrHead->data);
        print_linked_list_using_recursion( ptrHead->next );
    }
}



/************** Add a node to start of a linked list ******************/
void add_node_start( Node** ptrHead , int data )
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    if( *ptrHead == NULL )
    {
        //linked list is currently empty
        temp->next = NULL;
    }
    else
    {
        temp->next = *ptrHead;
    }
    *ptrHead = temp;
}

/************** Add a node to the end of the linked list ******************/
void add_node_end( Node** ptrHead , int data )
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    if( *ptrHead == NULL )
    {
        //linked list is currently empty
        *ptrHead = temp;
    }
    else
    {
        Node* temp2 = *ptrHead;
        while( temp2->next != NULL )
            temp2 = temp2->next;

        //now, temp2->next is NULL and is last element in the list
        temp2->next = temp;
    }
}

/************** Delete a node from the nth index of the linked list ******************/
int delete_node_nth_pos( Node** ptrHead , int pos, int* deleted_data )
{
    int count = 0;
    Node  *temp = NULL , *save = NULL;

    //check if the list is already empty
    if( *ptrHead == NULL )
    {
        printf("\nList is already empty.\n");
        return -1;
    }

    if( pos < 0 )
    {
        printf("\nInvalid / negative index %d\n",pos);
        return -1;
    }
    else if( pos == 0 )
    {
        temp = (*ptrHead);
        (*ptrHead) = (*ptrHead)->next;

        *deleted_data = temp->data;
        free( temp );
        return 0;
    }
    else
    {
        temp = (*ptrHead);
        save = (*ptrHead);
        for( count=0; count<pos; count++ )
        {
            save = temp;
            temp = temp->next;

            if( temp == NULL )
            {
                //if we have reached the end of the list, the pos provided was invalid for the given list
                printf("\nInvalid position %d provided for the given list\n",pos);
                return -1;
            }

        }

        //now count is same as "pos"
        save->next = temp->next;

        *deleted_data = temp->data;
        free( temp );
        return 0;
    }
}

/************** Add a node to the nth index of the linked list ******************/
int add_node_nth_pos( Node** ptrHead , int data , int pos )
{
    if( pos < 0 )
    {
        printf("\nInvalid / negative index %d\n",pos);
        return -1;
    }
    else if( pos == 0 )
    {
        //same as adding a new node to the start of the linked list
        
        //create the new node
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = data;

        temp->next = *ptrHead;
        *ptrHead = temp; //assign the head of the list to point to new node

        return 0; // return 0 to indicate success
    }
    else
    {
        //insert a new node to the nth index , other than the start ( i.e. index 0 )
        int i = 0;
        Node* temp = *ptrHead , *new_node = NULL;

        if( *ptrHead == NULL && pos > 0 )
        {
            printf("\nInvalid position %d for given empty list. Only valid position is 0\n",pos);
            return -1;
        }
        
        //move to the node one node prior
        for(i=0; i<pos-1; i++)
        {
            temp = temp->next;
            if( temp == NULL )
            {
                printf("\nPosition %d is invalid for given list.\n",pos);
                return -1;
            }
        }

        new_node = (Node*) malloc(sizeof(Node));
        new_node->data = data;

        new_node->next = temp->next;
        temp->next = new_node;
        return 0;
    }
}

/************** Reverse a linked list ******************/
void printLinkedList(Node* ptrHead)
{
    if( ptrHead == NULL )
    {
        printf("\nThe linked list is empty.\n");
    }
    else
    {
        Node* temp = ptrHead;
        int count = 0;
        while( temp != NULL )
        {
            printf("%d\t",temp->data );
            temp = temp->next;
            count++;
        }

        printf("===> COUNT : %d\n",count);
    }
}

int main(void)
{
    int tempNum = 0;
    int pos = -1;
    int result = -1;
    Node* head = NULL; // list is empty

    srand ( (unsigned int)time(NULL) );

    /************** create a random linked list of given size ******************/
    create_random_linked_list( &head , 5 );

    printf("\n\nLinked list is:\n");
    printLinkedList(head);
    /*******************************************************/

    /************** Add a node to start of a linked list ******************/
    tempNum = 59;
    add_node_start( &head , tempNum );
    
    printf("\n\nOn adding node with data %d to start of linked list:\n", tempNum);
    printLinkedList(head);
    /*******************************************************/


    /************** Add a node to the end of the linked list ******************/
    tempNum = 761;
    add_node_end( &head , tempNum );
    
    printf("\n\nOn adding node with data %d to the end of linked list:\n", tempNum );
    printLinkedList(head);
    /*******************************************************/


    /************** Add a node to the nth index of the linked list ******************/
    tempNum = 586;
    pos = 3;
    printf("\n\nOn adding node with data %d at index %d in the linked list:", tempNum , pos );
    result = add_node_nth_pos( &head , tempNum , pos );

    if( !result ) //if success
    {
        printf("\n");
        printLinkedList(head);
    }
    /*******************************************************/


    /************** Delete a node from the nth index of the linked list ******************/
    pos = 2;  //test for  negative, 0  ,valid value, invalid value
    tempNum = -1; //delete function will return the data of delete node in tempNum
    printf("\n\nOn deleting node at index %d in the linked list:", pos );
    result = delete_node_nth_pos( &head , pos , &tempNum );

    if( !result ) //if success
    {
        printf("\nData of deleted node is : %d\n", tempNum);
        printLinkedList(head);
    }
    /*******************************************************/


    /************** print elements of a linked list using recursion ******************/
    printf("\n\nThe linked list elements printed using recursion is as follows:\n");
    print_linked_list_using_recursion( head );


    /************** print elements of a linked list in reverse order ******************/
    /*This list only prints in reverse order, does not actually reverse the linked list */
    printf("\n\nThe linked list printed in reverse order ( not actually reversed ) is as follows:\n");
    print_linked_list_in_reverse_order( head );
    printf("\n\n");


    /************** Reverse a linked list iteratively ******************/
    reverse_linked_list( &head );
    
    printf("\n\nReversed Linked list is:\n");
    printLinkedList(head);
    /*******************************************************/

    /************** Reverse a linked list using recursion******************/
    reverse_linked_list_recursion(  &head );
    
    printf("\n\nLinked list after reversal ( using  recursion) is as follows:\n");
    printLinkedList(head);
    /*******************************************************/

    printf("\n\n");
    return 0;
}


//end of file
