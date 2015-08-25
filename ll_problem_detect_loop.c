#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

/*This function return 0 if there is no loop, it returns 1 if a loop is detected*/
int detect_loop(Node* ptrHead )
{
    Node* slow = ptrHead;
    Node* fast = ptrHead;

    while( slow != NULL && fast!=NULL )
    {
        slow = slow->next;
        fast = fast->next->next;
        if( slow == fast )
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int result = -1;
    Node *head = NULL;
    Node node1, node2, node3, node4;
    
    node1.data = 11;
    node1.next = &node2;

    node2.data = 22;
    node2.next = &node3;

    node3.data = 33;
    node3.next = &node4;

    node4.data = 44;
    node4.next = NULL;//&node2;

    head = &node1;

    result = detect_loop( head );

    switch( result )
    {
    case 0:
        {
            printf("\nLoop is NOT detected in the given linked list.\n");
        }
        break;
    case 1:
        {
            printf("\nLoop is detected in the given linked list.\n");
        }
        break;

    default:
        {
            printf("\nInvalid result...\n");
        }
    };


    printf("\n\n");
    return 0;
}

//end of file
