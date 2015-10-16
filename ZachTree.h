#ifndef CTREE_H
#define CTREE_H

#include <iostream>

using namespace std;

template<class T> class CTree
{
public:
    CTree()
    {
        m_root = 0;
        size = 0;
    }
    
    ~CTree()
    {
        delete m_root;
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

    void Insert(const T &t)
    {
        if (size == 0)
        {
            m_root = new Node(t);
        }
        
        else
        {
            Node *itr = m_root;
            
            while (itr != nullptr)
            {
                if (t < itr->m_number)
                {
                    if (itr->m_ll != nullptr)
                    {
                        itr = itr->m_ll;
                    }
                    
                    else
                    {
                        itr->m_ll = new Node(t);
                        break;
                    }
                }
                        
                else if (t > itr->m_number)
                {
                    if (itr->m_rl != nullptr)
                    {
                        itr = itr->m_rl;
                    }
                    
                    else
                    {
                        itr->m_rl = new Node(t);
                        break;
                    }
                }
            }
        }
        
        size++;
    }
    
    void Preorder(std::ostream &p_str)
    {
        //p_str<<"[Preorder Goes Here]";
        Node *n = m_root;
        GetPreorder(p_str, n);
    }
    
    int Depth()
    {
        return GetDepth(m_root);
    }

    const Node *Find(const T &t) const
    {
        return FindNode(t);
    }
    Node *Find(const T &t)
    {
        return FindNode(t);
    }

    void Delete(const T &t)
    {
        DeleteNode(m_root, t);
        size--;
    }


private:
    Node *m_root;
    long size;
    
    
    int GetDepth(Node *n)
    {
        if (n->m_ll == nullptr && n->m_rl == nullptr)
        {
            return 0;
        }
        
        else if (n->m_ll != nullptr && n->m_rl == nullptr)
        {
            return GetDepth(n->m_ll) + 1;
        }
        
        else if (n->m_ll == nullptr && n->m_rl != nullptr)
        {
            return GetDepth(n->m_rl) + 1;
        }
        
        else if (n->m_ll != nullptr && n->m_rl != nullptr)
        {
            int left = GetDepth(n->m_ll), right = GetDepth(n->m_rl);
            if (left > right)
            {
                return left + 1;
            }
            
            else
            {
                return right + 1;
            }
        }
    }
    
    Node *FindNode(const T &t)
    {
        Node *itr = m_root;
        
        while (itr != nullptr)
        {
            if (itr->m_number == t)
            {
                return itr;
            }

            if (t < itr->m_number)
            {
                itr = itr->m_ll;
            }

            else if (t > itr->m_number)
            {
                itr = itr->m_rl;
            }
        }
    }
    
    void GetPreorder(std::ostream &p_str, Node *n)
    {
        p_str<<n->m_number<<"  ";
        
        if (n->m_ll != nullptr)
        {
            GetPreorder(p_str, n->m_ll);
        }
        
        if (n->m_rl != nullptr)
        {
            GetPreorder(p_str, n->m_rl);
        }
    }
    
    void DeleteNode(Node *n, const T &t)
    {
        Node *parent = nullptr;
        Node *to_delete = n;
        
        while (to_delete != nullptr)
        {
            if (to_delete->m_number == t)
            {
                break;
            }
            
            else
            {
                if (t < to_delete->m_number)
                {
                    parent = to_delete;
                    to_delete = to_delete->m_ll;
                }

                else if (t > to_delete->m_number)
                {
                    parent = to_delete;
                    to_delete = to_delete->m_rl;
                }
            }
            
            if (to_delete == nullptr)
            {
                return;
            }
        }
        
        //Remove Node with no children
        
        if (to_delete->m_ll == nullptr && to_delete->m_rl == nullptr)
        {
            if (parent != nullptr)
            {
                if (to_delete == parent->m_ll)
                {
                    parent->m_ll = nullptr;
                    delete to_delete;
                }

                else if (to_delete == parent->m_rl)
                {
                    parent->m_rl = nullptr;
                    delete to_delete;
                }
            }
            
            else
            {
                delete to_delete;
            }
        }
        
        //Delete Node with only left leaf
        else if (to_delete->m_ll != nullptr && to_delete->m_rl == nullptr)
        {
            if (parent != nullptr)
            {
                if (to_delete->m_number == parent->m_ll->m_number)
                {
                    parent->m_ll = to_delete->m_ll;
                    delete to_delete;
                }

                else if (to_delete->m_number == parent->m_rl->m_number)
                {
                    parent->m_rl = to_delete->m_ll;
                    delete to_delete;
                }
            }
            
            else
            {
                delete to_delete;
            }
        }
        
        
        //Delete Node with only right leaf
        else if (to_delete->m_ll == nullptr && to_delete->m_rl != nullptr)
        {
            if (parent != nullptr)
            {
                if (to_delete->m_number == parent->m_ll->m_number)
                {
                    parent->m_ll = to_delete->m_rl;
                    delete to_delete;
                }

                else if (to_delete->m_number == parent->m_rl->m_number)
                {
                    parent->m_rl = to_delete->m_rl;
                    delete to_delete;
                }
            }
            
            else
            {
                delete to_delete;
            }
        }
        
        //Delete Node with left and right leaf
        else if (to_delete->m_ll != nullptr && to_delete->m_rl != nullptr)
        {
            
        }
    }
    
};


#endif