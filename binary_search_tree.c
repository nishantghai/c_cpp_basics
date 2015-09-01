/*
filename    : binary_search_tree.c
author      : Nishant Ghai
description : implementation and basic operations on a binary search tree
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
}Node;


Node* getNewNode( int data )
{
    Node* temp = (Node*)malloc( sizeof( Node) );
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

int find_node( Node* root, int data )
{
    if( root == NULL )
    {
        // no node with "data" found
        return 0;
    }
    
    if( data == root->data )
    {
        return 1;
    }
    else if( data < root->data )
    {
        //look in the left sub-tree
        return find_node( root->left, data );
    }
    else 
    {
        //look in the right sub-tree
        return find_node( root->right, data );
    }
}


void add_node(Node** ptrRoot, int data )
{
    if( *ptrRoot == NULL )
    {
        (*ptrRoot) = getNewNode( data );
    }
    else if( data < (*ptrRoot)->data )
    {
        // if data of new node to be created is less than root node's data
        // add the new node to the left subtree
        add_node( &((*ptrRoot)->left) , data );
    }
    else if( data > (*ptrRoot)->data )
    {
        // if data of new node to be created is greater than root node's data
        // add the new node to the right subtree
        add_node( &((*ptrRoot)->right) , data );
    }
    else
    {
        //data is already present in the tree
        return;
    }
}


Node* findMinNode( Node* root )
{
    Node* temp = root;

    if( temp == NULL )
    {
        return NULL;
    }

    while( temp->left != NULL )
    {
        temp = temp->left;
    }

    //now temp->left == NULL  i.e has no left child
    return temp;
}

/*recursive algorithm to delete a node from a Binary search tree*/
void delete_node( Node** ptrRoot , int data )
{
    Node* curr_Root = (*ptrRoot); //Node to be deleted

    if( curr_Root == NULL )
    {
        return;
    }

    if( data < curr_Root->data )
    {
        //if data to be deleted is smaller than the data of the root, try to search and delete the node with that data in the left sub-tree
        delete_node( &(curr_Root->left), data );
    }
    else if( data > curr_Root->data )
    {
        //if data to be deleted is larger than the data of the root, try to search and delete the node with that data in the right sub-tree
        delete_node( &(curr_Root->right), data );
    }
    else
    {
        // curr_Root is the node to be deleted i.e. 
        assert( curr_Root->data == data );

        if( curr_Root->left == NULL && curr_Root->right == NULL )
        {
            //node to be deleted is a leaf node.
            free( curr_Root );
            (*ptrRoot) = NULL; //set NULL in the pointer to the current node
        }
        else if( curr_Root->left != NULL && curr_Root->right == NULL )
        {
            //node to be deleted has only left child
            (*ptrRoot) = curr_Root->left;
            free( curr_Root );
        }
        else if( curr_Root->left == NULL && curr_Root->right != NULL )
        {
            //node to be deleted has only right child
            (*ptrRoot) = curr_Root->right;
            free( curr_Root );
        }
        else
        {
            //node to be deleted has two children

            // 3-step process

            // (1) find the minimum element from the right subtree
            Node* min_node = findMinNode( curr_Root->right );

            // (2) copy the data of minimum element from right subtree into current node
            assert( min_node != NULL );
            curr_Root->data = min_node->data;
            
            // (3) delete that node , using recursion as it would be having at most 1 child.
            delete_node(  &(curr_Root->right) , min_node->data);
        }
    }
}

void inorder_traversal( Node* root )
{
    if( root == NULL )
    {
        return;
    }

    inorder_traversal( root->left );
    printf("%d\t",root->data);
    inorder_traversal( root->right );
}

int main()
{
    int temp_data = 0 , result = 0;
    Node* root = NULL;

    add_node( &root, 12 );
    add_node( &root, 10 );
    add_node( &root, 30 );
    add_node( &root, 6 );
    add_node( &root, 11 );
    add_node( &root, 15 );
    add_node( &root, 35 );
    add_node( &root, 3 );
    add_node( &root, 7 );
    add_node( &root, 13 );
    add_node( &root, 16 );
    add_node( &root, 33 );
    add_node( &root, 38 );
    add_node( &root, 4 );

    printf("\nThe in-order traversal of this tree is:\n");
    inorder_traversal( root );


    temp_data = 10;
    printf("\n\nNow deleting %d from this tree.",temp_data);
    delete_node( &root, temp_data );

    printf("\n\nThe in-order traversal of this tree is:\n");
    inorder_traversal( root );


    temp_data = 30;
    result = find_node( root, temp_data );
    if( result == 0 )
    {
        printf("\n\n%d is NOT found in the given binary search tree.\n",temp_data);
    }
    else
    {
        printf("\n\n%d is found in the given binary search tree.\n",temp_data);
    }

    printf("\n\n");
    return 0;
}


//end of file
