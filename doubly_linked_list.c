/* 
filename : doubly_linked_list.c
author : Nishant Ghai
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
}Node;


void print_linked_list( Node *ptrHead )
{
    if( ptrHead == NULL )
    {
        printf("\nThe linked list is empty.\n");
    }
    else
    {
        Node *temp = ptrHead;
        while( temp != NULL )
        {
            printf("%d\t",temp->data);
            temp = temp->next;
        }
    }
}

void print_linked_list_reverse( Node* ptrHead )
{
    if( ptrHead == NULL )
    {
        printf("\nThe linked list is empty.\n");
    }
    else
    {
        Node* temp = ptrHead;
        while( temp->next != NULL )
        {
            temp = temp->next;
        }

        //now "temp" points to last node, now traverse backwards
        while( temp != NULL )
        {
            printf("%d\t",temp->data);
            temp = temp->prev;
        }
    }
}

void add_node_to_start( Node** ptrHead, int data )
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->prev = NULL;
    if( *ptrHead == NULL )
    {
        //list is currently empty
        temp->next = NULL;
    }
    else
    {
        temp->next = *ptrHead;
        (*ptrHead)->prev = temp;
    }
    (*ptrHead) = temp;
}

void add_node_to_end( Node** ptrHead, int data )
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    if( *ptrHead == NULL )
    {
        *ptrHead = temp;
    }
    else
    {
        Node* curr = *ptrHead;
        while( curr->next != NULL )
        {
            curr = curr->next;
        }
        temp->prev = curr;
        curr->next = temp;
    }
}

void add_node_to_pos( Node** ptrHead, int data, int pos )
{
    if( pos < 0 )
    {
        printf("\nThe position %d is invalid.\n", pos);
    }
    else if( pos == 0 )
    {
        //same as add_node_to_start()

        Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->prev = NULL;
        if( *ptrHead == NULL )
        {
            //list is currently empty
            temp->next = NULL;
        }
        else
        {
            temp->next = *ptrHead;
            (*ptrHead)->prev = temp;
        }
        (*ptrHead) = temp;
    }
    else
    {
        int i = 0;
        Node *temp = NULL , *new_node = NULL;
        if( *ptrHead == NULL )
        {
            printf("\nInvalid pos %d for empty list.\n",pos);
            return;
        }

        temp = (*ptrHead);
        for( i = 0; i < pos-1 ; i++)
        {
            if( temp->next == NULL ) //if we have reached the end of the list
            {
                if( pos-i > 1 )
                {
                    printf("\nInvalid position %d for the given list.\n",pos);
                    return;
                }
                else
                {
                    break;//temp
                }
            }

            temp = temp->next;
        }

        //temp is pointing to node after which we have to insert the new node

        new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->prev = temp;
        new_node->next = temp->next;
        if( temp->next != NULL )
        {
            temp->next->prev = new_node;
        }
        temp->next = new_node;
    }
}


int main(void)
{
    Node *head = NULL;

    add_node_to_start( &head , 33 );

    add_node_to_start( &head , 22 );
    add_node_to_start( &head , 11 );
    add_node_to_end( &head, 100 );

    add_node_to_pos( &head, 200, 1 );

    printf("\nThe linked list is:\n");
    print_linked_list( head );

    printf("\n\nThe linked list printed in reverse is:\n");
    print_linked_list_reverse( head );

    printf("\n\n");
    return 0;
}

//end of file
