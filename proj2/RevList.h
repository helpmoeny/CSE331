//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H

//#include <iostream>

template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  {
      m_front = NULL;
      m_back = NULL;
      reversed = false;
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
      Node *itr = m_front;
      
      while (itr != NULL)
      {
          Node *temp = itr;
          
          if (!reversed)
          {
              itr = itr->m_next;
          }
          
          else
          {
              itr = itr->m_prev;
          }
          
          delete temp;
      }
      
      m_front = NULL;
      m_back = NULL;
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {
      Node *itr = b->m_front;
      
      while (itr != NULL)
      {
          PushBack(itr->m_payload);
          
          if (!b.IsReversed())
          {
              itr = itr->m_next;
          }
          
          else
          {
              itr = itr->m_prev;
          }
      }
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  {
      Node *itr = m_front;
      
      while (itr != NULL)
      {
          Node *temp = itr;
          
          if (!reversed)
          {
             itr = itr->m_next;
          }
          
          else
          {
             itr = itr->m_prev;
          }
          
          delete temp;
      }
      
      m_front = NULL;
      m_back = NULL;
      
      
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };
  
  // Determines if the list is empty
  bool IsEmpty() const
  {
      if (m_front == NULL || m_back == NULL)
      {
          return true;
      }
      
      return false;
  }

  //methods to add data to the front or the back of the list
  void PushFront(const T &t)
  {
      Node *new_node = new Node(t);
      
      if (m_front == NULL)
      {
          m_front = new_node;
          m_back = new_node;
      }
      
      else
      {
          if (!reversed)
          {
              m_front->m_prev = new_node;
              new_node->m_next = m_front;
              new_node->m_prev = NULL;
              m_front = new_node;
          }
          
          else
          {
              m_front->m_next = new_node;
              new_node->m_prev = m_front;
              new_node->m_next = NULL;
              m_front = new_node;
          }
      }
  }
  
  void PushBack(const T &t)
  {
      Node *new_node = new Node(t);
      
      if (m_back == NULL)
      {
          m_front = new_node;
          m_back = new_node;
      }
      
      else
      {
          if (!reversed)
          {
              m_back->m_next = new_node;
              new_node->m_prev = m_back;
              new_node->m_next = NULL;
              m_back = new_node;
          }
          
          else
          {
              m_back->m_prev = new_node;
              new_node->m_next = m_back;
              new_node->m_prev = NULL;
              m_back = new_node;
          }
      }
  }
  
  void PopFront()
  {
      if (!reversed)
      {
          m_front->m_next->m_prev = NULL;
          m_front = m_front->m_next;
      }
      
      else
      {
          m_front->m_prev->m_next = NULL;
          m_front = m_front->m_prev;
      }
     
  }
  
  void PopBack()
  {
      if (!reversed)
      {
          m_back->m_prev->m_next = NULL;
          m_back = m_back->m_prev;
      }
      
      else
      {
          m_back->m_next->m_prev = NULL;
          m_back = m_back->m_next;
      }
  }

  //Get a pointer to the first node in the list
  const Node *Begin() const
  {
      return m_front;
  }
  
  Node *Begin()
  {
      return m_front;
  }

  //get a pointer to the last node in the list
  const Node *End() const
  {
      return m_back;
  }
  
  Node *End()
  {
      return m_back;
  }

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const
  {
      if (!reversed)
      {
          return n->m_next;
      }

      else
      {
          return n->m_prev;
      }
      
  }
  
  Node *Next(const Node *n)
  {
      if (!reversed)
      {
          return n->m_next;
      }

      else
      {
          return n->m_prev;
      }
  }

  //Find a node with the specified key
  const Node *Find(const T &t) const
  {
      Node *itr = m_front;
      
      while (itr != NULL)
      {
          if (t == itr->m_payload)
          {
              return itr;
          }
          
          if (!reversed)
          {
              itr = itr->m_next;
          }
          
          else
          {
              itr = itr->m_prev;
          }
      }
      
      return NULL;
  }
  
  Node *Find(const T &t)
  {
      
      Node *itr = m_front;
      
      while (itr != NULL)
      {
          if (t == itr->m_payload)
          {
              return itr;
          }
          
          if (!reversed)
          {
              itr = itr->m_next;
          }
          
          else
          {
              itr = itr->m_prev;
          }
      }
      
      return NULL;
  }

  //Delete the given node
  void Delete(Node *n)
  {
      n->m_prev->m_next = n->m_next;
      n->m_next->m_prev = n->m_prev;
      delete n;
  }

  //Reverse the list in O(1) time
  void Reverse()
  {
      Node *temp = m_front;
      m_front = m_back;
      m_back = temp;
      reversed = !reversed;
  }
  
  bool IsReversed()
  {
      return reversed;
  }

  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  Node   *m_front;            // Front node
  Node   *m_back;             // Back node
  bool    reversed;           // Tracks current direction of list
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{
    Node *itr = b->m_front;
      
    while (itr != NULL)
    {
        PushBack(itr->m_payload);
        
        if (!b.IsReversed())
        {
            itr = itr->m_next;
        }
        
        else
        {
            itr = itr->m_prev;
        }
    }
}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif