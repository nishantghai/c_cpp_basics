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

/*
 The main idea of the solution is, while traversing from top to bottom, 
 the first node n we encounter with value between n1 and n2, i.e., n1 < n < n2 
 or same as one of the n1 or n2, is LCA of n1 and n2 (assuming that n1 < n2)
*/
Node* getLCABST( Node* root, int data1 , int data2)
{
    if( root == NULL )
    {
        return NULL;
    }

    //if root->data is greater than both data1 and data2
    //look for LCA in the left subtree
    if( (root->data > data1)  && (root->data  > data2 ) )
    {
        return getLCABST( root->left , data1 , data2 );
    }

    //if root->data is smaller than both data1 and data2
    //look for LCA in the right subtree
    if( (root->data < data1) && (root->data < data2 ) )
    {
        return getLCABST( root->right, data1, data2);
    }

    return root; //this is the case when root->data lies in between data1 and data2
}


Node* getLowestCommonAncestor( Node* root, int data1 , int data2)
{
    Node* node1 = NULL, *node2 = NULL;

    if( data1 > data2 )
    {
        //swap data1 and data2
        int temp = data1;
        data1 = data2;
        data2 = temp;
    }

    //check if data1 is present in the binary search tree
    node1 = findNode( root, data1 );
    if( node1 == NULL )
    {
        printf("\n\nThere is no node in the BST with data %d", data1);
        return NULL;
    }

    //check if data2 is present in the binary search tree
    node2 = findNode( root, data2 );
    if( node2 == NULL )
    {
        printf("\n\nThere is no node in the BST with data %d", data2);
        return NULL;
    }

    //now call recursive function getLCA()
    return getLCABST( root, data1, data2 );
}

/*
floor(x) ==> largest integer not greater than x
*/
Node* floorInBST( Node* root, int x )
{
    if( root == NULL )
    {
        return NULL;
    }


    if( root->data > x )
    {
        //look for node from BST which is smaller than x in the left subtree
        return floorInBST( root->left , x );
    }
    else if( root->data < x )
    {
        // either current root is floor value or there is some value larger value than it which is still smaller than x

        //look for larger value in the right subtree
        Node* temp = floorInBST( root->right , x );
        if( temp != NULL )
        {
            if ( temp->data  > root->data  )
            {
                return temp;
            }
            else
            {
                return root;
            }
        }
        else
        {
            return root;
        }
    }
    else // root->data == x
    {
        return root;
    }
}

/*
ceiling(x) ==> smallest integer not less than x
*/
Node* ceilingInBST( Node* root, int x )
{
    if( root == NULL )
    {
        return NULL;
    }

    if( root->data < x )
    {
        //look for ceiling value in the right subtree
        return ceilingInBST( root->right , x);
    }
    else if( root->data > x )
    {
        //current root value is greater than x
        //either the current root is the ceiling or there is some value smaller than it which is still larger than x
        //look for it left subtree
        Node* temp = ceilingInBST( root->left , x );
        
        if( temp != NULL )
        {
            if( temp->data < root->data )
            {
                return temp;
            }
            else
            {
                return root;
            }
        }
        else
        {
            return root;
        }
    }
    else
    {
        return root;
    }

}




int main()
{
    int temp_data = 0 , result = 0 ,  data1 =0, data2 = 0;
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

    //temp_data = 10;
    //printf("\n\nNow deleting %d from this tree.",temp_data);
    //delete_node( &root, temp_data );


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


    //find lowest common ancestor
    data1 = 4;
    data2 = 7;
    tempNode = getLowestCommonAncestor( root, data1, data2 );
    if( tempNode == NULL )
    {
        printf("\n\nThere is no lowest common ancestor for %d and %d in the given BST.",data1, data2);
    }
    else
    {
        printf("\n\nThe lowest common ancestor for %d and %d in the given BST is %d.",data1, data2, tempNode->data);
    }

    temp_data = 17;
    tempNode = ceilingInBST( root, temp_data );
    if( tempNode != NULL )
    {
        printf("\n\nCeiling value for %d from given BST is %d", temp_data , tempNode->data );
    }
    else
    {
        printf("\n\nThere is no ceiling value for %d in given BST.",temp_data);
    }


    temp_data = 26;
    tempNode = floorInBST( root, temp_data );
    if( tempNode != NULL )
    {
        printf("\n\nFloor value for %d from given BST is %d", temp_data , tempNode->data );
    }
    else
    {
        printf("\n\nThere is no floor value for %d in given BST.",temp_data);
    }

    printf("\n\n");
    return 0;
}


//end of file
