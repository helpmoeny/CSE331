//
// Name :         Tree.h
// Description :  Simple binary search tree.
// Created By : 
//

#ifndef CTREE_H
#define CTREE_H

#include <iostream>

using namespace std;

template<class T> class CTree
{
public:
    CTree() //Constructor for tree
    {
        m_root = 0; //Set the root node to empty
        size = 0; //Set the tree's size to 0
    }
    
    ~CTree() //Destructor for tree
    {
        delete m_root; //Delete the root node
    }

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;}
        Node(const T &t) {m_number = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_number;}
        const T &Data() const {return m_number;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_number;

    };

    void Insert(const T &t) //Insert a value into the tree
    {
        if (size == 0) //The tree is empty
        {
            m_root = new Node(t); //Create the root node with the given value
        }
        
        else //If the tree is not empty
        {
            Node *itr = m_root; //Create an iterator node pointer
            
            while (itr != nullptr) //Search until the end of the tree is reached
            {
                if (t < itr->m_number) //If the value being inserted is less than the current value
                {
                    if (itr->m_ll != nullptr) //If the current node has a left leaf
                    {
                        itr = itr->m_ll; //Proceed left down the tree
                    }
                    
                    else //if the current node does not have a left leaf
                    {
                        itr->m_ll = new Node(t); //Create a new node and insert it as the left leaf
                        break;
                    }
                }
                        
                else if (t > itr->m_number) //If the value being inserted is greater than the current value
                {
                    if (itr->m_rl != nullptr) //If the current node has a right leaf
                    {
                        itr = itr->m_rl; //Proceed right down the tree
                    }
                    
                    else //If the current node does not have a right leaf
                    {
                        itr->m_rl = new Node(t); //Create a new node and insert it as the right leaf
                        break;
                    }
                }
            }
        }
        
        size++;
    }
    
    void Preorder(std::ostream &p_str) //Output the preorder traversal of the tree
    {
        GetPreorder(p_str, m_root); //Call the preorder function
    }
    
    int Depth() //Return the depth of the tree
    {
        return GetDepth(m_root); //Call depth-calculating function
    }

    const Node *Find(const T &t) const //Find a node in the tree
    {
        return FindNode(t); //Call find function
    }
    
    Node *Find(const T &t) //Find a node in the tree
    {
        return FindNode(t); //Call find function
    }

    void Delete(const T &t) //Delete a given value from the tree
    {
        DeleteNode(m_root, t); //Call delete function
        size--; //Decrement size of tree
    }


private:
    Node *m_root;
    long size;
    
    
    int GetDepth(Node *n) //Get the depth of the tree
    {
        if (n == nullptr) //Tree is empty
        {
            return -1;
        }
        
        if (n->m_ll == nullptr && n->m_rl == nullptr) //Tree has root but no leaves
        {
            return 0;
        }
        
        else if (n->m_ll != nullptr && n->m_rl == nullptr) //Proceed left down tree if only left leaf exists
        {
            return GetDepth(n->m_ll) + 1;
        }
        
        else if (n->m_ll == nullptr && n->m_rl != nullptr) //Proceed right down tree if only left leaf exists
        {
            return GetDepth(n->m_rl) + 1;
        }
        
        else if (n->m_ll != nullptr && n->m_rl != nullptr) //Both leaves exist
        {
            int left = GetDepth(n->m_ll), right = GetDepth(n->m_rl); //Proceed down both sides of tree
            if (left > right) //Return whichever side is deeper
            {
                return left + 1;
            }
            
            else
            {
                return right + 1;
            }
        }
    }
    
    Node *FindNode(const T &t) //Find and return a node in the tree
    {
        Node *itr = m_root; //Begin searching with root node
        
        while (itr != nullptr)
        {
            if (itr->m_number == t) //Value has been found
            {
                return itr;
            }

            if (t < itr->m_number) //Current value is less than what is being searched for
            {
                itr = itr->m_ll; //Proceed left down tree
            }

            else if (t > itr->m_number) //Current value is greater than what is being searched for
            {
                itr = itr->m_rl; //Proceed right down tree
            }
        }
    }
    
    void GetPreorder(std::ostream &p_str, Node *n) //Output the preorder traversal of the tree
    {
        p_str<<n->m_number<<"  "; //Output root node
        
        if (n->m_ll != nullptr) //If left leaf exists
        {
            GetPreorder(p_str, n->m_ll); //Begin preorder on left leaf
        }
        
        if (n->m_rl != nullptr) //If right leaf exists
        {
            GetPreorder(p_str, n->m_rl); //Begin preorder on right leaf
        }
    }
    
    void DeleteNode(Node *n, const T &t) //Remove a node from the tree
    {
        Node *parent = nullptr; //Parent of node to be deleted
        Node *to_delete = n; //Node to be deleted
        
        while (to_delete != nullptr) //Until end of tree is reached
        {
            if (to_delete->m_number == t) //Node to be deleted has been located
            {
                break;
            }
            
            else
            {
                if (t < to_delete->m_number) //Value being searched for is less than current value
                {
                    parent = to_delete;
                    to_delete = to_delete->m_ll; //Proceed left down tree
                }

                else if (t > to_delete->m_number) //Value being searched for is greater than current value
                {
                    parent = to_delete;
                    to_delete = to_delete->m_rl; //Proceed right down tree
                }
            }
            
            if (to_delete == nullptr) //Value was not found in tree
            {
                return;
            }
        }
        
        //Remove Node with no children
        
        if (to_delete->m_ll == nullptr && to_delete->m_rl == nullptr)
        {
            if (parent != nullptr) //to_delete is not the root node
            {
                if (to_delete == parent->m_ll) //Deleting a left leaf
                {
                    parent->m_ll = nullptr; //Remove pointer to to_delete
                    delete to_delete;
                }

                else if (to_delete == parent->m_rl) //Deleting a right leaf
                {
                    parent->m_rl = nullptr; //Remove pointer to to_delete
                    delete to_delete;
                }
            }
            
            else //to_delete is the root node
            {
                m_root = nullptr; //Root node no longer exists
                delete to_delete;
            }
        }
        
        //Delete Node with only left leaf
        
        else if (to_delete->m_ll != nullptr && to_delete->m_rl == nullptr)
        {
            if (parent != nullptr) //to_delete is not the root node
            {
                if (to_delete == parent->m_ll) //Deleting a left leaf
                {
                    parent->m_ll = to_delete->m_ll; //Replace pointer to to_delete with its leaf
                }

                else if (to_delete == parent->m_rl) //Deleting a right leaf
                {
                    parent->m_rl = to_delete->m_ll; //Replace pointer to to_delete with its leaf
                }
            }
            
            else //to_delete is the root node
            {
                m_root = m_root->m_ll; //Set root node to left leaf
            }
        }
        
        //Delete Node with only right leaf
        else if (to_delete->m_ll == nullptr && to_delete->m_rl != nullptr)
        {
            if (parent != nullptr) //to_delete is not the root node
            {
                if (to_delete == parent->m_ll) //Deleting a left leaf
                {
                    parent->m_ll = to_delete->m_rl; //Replace pointer to to_delete with its leaf
                }

                else if (to_delete == parent->m_rl) //Deleting a right leaf
                {
                    parent->m_rl = to_delete->m_rl; //Replace pointer to to_delete with its leaf
                }
            }
            
            else //to_delete is the root node
            {
                m_root = m_root->m_rl; //Set root node to right leaf
            }
        }
        
        
        //Delete Node with left and right leaf
        
        else if (to_delete->m_ll != nullptr && to_delete->m_rl != nullptr)
        {
            parent = to_delete; //parent becomes the node to be deleted
            to_delete = to_delete->m_rl; //to_delete becomes its right leaf
            
            if (to_delete->m_ll == nullptr && to_delete->m_rl == nullptr) //The right leaf has no leaves
            {
                 parent->m_number = to_delete->m_number; //Move the data from to_delete into parent's position
                 delete to_delete; //Delete to_delete
                 parent->m_rl = nullptr; //Remove the pointer to to_delete
            }
            
            else if (to_delete->m_ll != nullptr) //If the right leaf has a left leaf
            {
                Node *new_leaf = to_delete->m_ll; //Creates a pointer to the new left leaf of to_delete
                
                while (new_leaf->m_ll != nullptr) //Proceeds down the tree and to the left, moving all of the leaves up by one slot
                {
                    to_delete = new_leaf;
                    new_leaf = new_leaf->m_ll;
                }
                
                parent->m_number = new_leaf->m_number; //Moves new_leaf's data to parent's position
                delete new_leaf; //Deletes new_leaf
                to_delete->m_ll = nullptr; //Removes the pointer to new_leaf
            }
            
            else //The right leaf has a right leaf
            {
                Node *new_leaf = to_delete->m_rl; //Creates a pointer to the new right leaf of to_delete
                
                while (new_leaf->m_rl != nullptr) //Proceeds down the tree and to the right, moving all of the leaves up by one slot
                {
                    to_delete = new_leaf;
                    new_leaf = new_leaf->m_rl;
                }
                
                parent->m_number = new_leaf->m_number; //Moves new_leaf's data to parent's position
                delete new_leaf; //Deletes new_leaf
                to_delete->m_rl = nullptr; //Removes the pointer to new_leaf
            }
        }
    }
    
};


#endif
