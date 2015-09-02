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

int nodeExists( Node* root, int data )
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
        return nodeExists( root->left, data );
    }
    else 
    {
        //look in the right sub-tree
        return nodeExists( root->right, data );
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

int isEveryNodeLess( Node* root, int data )
{
    if( root == NULL )
    {
        return 1;
    }
    else
    {
        if(     (data > root->data ) && 
                isEveryNodeLess( root->left , data ) &&
                isEveryNodeLess( root->right , data )
            )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int isEveryNodeGreater( Node* root, int data )
{
    if( root == NULL )
    {
        return 1;
    }
    else
    {
        if(     (data < root->data ) && 
                isEveryNodeGreater( root->left , data ) &&
                isEveryNodeGreater( root->right , data )
            )
        {
            return 1;
        }
        else
        {
            printf("\nErorr! : Given tree is not a binary search tree\n");
            printf("\nCurrent node data = %d\n",root->data);
            return 0;
        }
    }
}



int isBinaryTreeBST( Node* root )
{
    if( root == NULL )
    {
        return 1;
    }
    else
    {
        if(  isBinaryTreeBST( root->left)  &&
             isBinaryTreeBST( root->right) &&
             isEveryNodeLess( root->left , root->data ) &&
             isEveryNodeGreater( root->right , root->data )
          )
        {
            return 1;
        }
        else
        {
            printf("\nErorr! : Given tree is not a binary search tree\n");
            printf("\nCurrent node data = %d\n",root->data);
            return 0;
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

Node* findNode( Node* root, int data )
{
    if( root == NULL )
    {
        return NULL;
    }
    
    if ( data == root->data )
    {
        return root;
    }
    else if( data < root->data )
    {
        return findNode( root->left, data );
    }
    else
    {
        return findNode( root->right, data );
    }
}


Node* getInorderSuccessor( Node* root, int data )
{
    if( root == NULL )
    {
        return NULL;
    }
    else
    {
        /*find the node in the binary search tree which has node with "data"*/
        Node* curr_node = findNode( root, data );

        if( curr_node->right != NULL )
        {
            /*
            case 1: if a node has right subtree, then in-order successor is the left most ( minimum ) node in its right subtree
            */
            Node* temp = curr_node->right;
            while( temp->left != NULL )
            {
                temp = temp->left;
            }
            return temp;
        }
        else
        {
        /*
        case 2: if a node has no right subtree, then to find in-order successor, start from root, 
        Travel down the tree, if a node’s data is greater than root’s data then go right side, otherwise go to left side.
        */

            Node* ancestor = root;
            Node* successor = NULL;
            
            while( ancestor != curr_node )
            {
                if( curr_node->data < ancestor->data )
                {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else
                {
                    ancestor = ancestor->right;
                }
            }
            return successor;
        }
    }
}

int main()
{
    int temp_data = 0 , result = 0;
    Node* root = NULL , *tempNode = NULL;;

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

    if(  isBinaryTreeBST(root) == 1 )
    {
        printf("\nThe given tree is a binary search tree.\n");
    }
    else
    {
        printf("\nThe given tree is not a binary search tree.\n");
    }

    temp_data = 10;
    printf("\n\nNow deleting %d from this tree.",temp_data);
    delete_node( &root, temp_data );


    if(  isBinaryTreeBST(root) == 1 )
    {
        printf("\nThe given tree is a binary search tree.\n");
    }
    else
    {
        printf("\nThe given tree is not a binary search tree.\n");
    }

    printf("\n\nThe in-order traversal of this tree is:\n");
    inorder_traversal( root );


    temp_data = 30;
    result = nodeExists( root, temp_data );
    if( result == 0 )
    {
        printf("\n\n%d is NOT found in the given binary search tree.\n",temp_data);
    }
    else
    {
        printf("\n\n%d is found in the given binary search tree.\n",temp_data);
    }


    temp_data = 16;
    tempNode = getInorderSuccessor( root, temp_data);
    if( tempNode != NULL )
    {
        printf("\n\nIn-order successor of %d is %d.",temp_data , tempNode->data);
    }
    else
    {
        printf("\n\nThere is no in-order successor of node with data %d.",temp_data);
    }



    printf("\n\n");
    return 0;
}


//end of file
