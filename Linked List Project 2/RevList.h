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
      m_head = NULL;
      m_tail = NULL;
      reversed = false;
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
      Node *itr = m_head;
      
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
      
      m_head = NULL;
      m_tail = NULL;
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {
      Node *itr = b->m_head;
      
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
      Node *itr = m_head;
      
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
      
      m_head = NULL;
      m_tail = NULL;
      
      
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
      if (m_head == NULL && m_tail == NULL)	//||?
      {
          return true;
      }
      
      return false;
  }

  //methods to add data to the front or the back of the list
  void PushFront(const T &t)
  {
      /* Node *new_node = new Node(t); //Pushback original
      
	  if (m_first == false)
      {
		  n = new Node();
		  n ->m_payload = t;
		  n ->m_next = n;
		  n ->m_prev = n;
		  n -> m_next = m_head;
          m_head = n;
          m_tail = n;
		  m_first = true;
		  return;
      }
		  n = new Node();
		  n ->m_payload = t;
		  n -> m_prev = m_tail;
		  m_tail -> m_next = n;
		  m_head -> m_prev = n;
		  n -> m_next = m_head;
          m_head = n;
          m_tail = n; */
		  
  }
  
  void PushBack(const T &t)
  {
      /* Node *node = new Node(t);
      if(IsEmpty())
	  {
		  m_head.m_next = node;
		  node -> m_next = m_head.m_next;
		  node -> m_prev = m_head.m_next;
	  }
	  else if(!IsEmpty){
		  Begin()-> p_prev-> m_next = node;
		  node -> m_prev = End();
		  node -> m_next = Begin();
		  Begin() -> m_prev = node;
	  }
	  m_size++; */
	  
	  Node *node = new Node(t);
      if(IsEmpty())
	  {
		  m_head -> m_next = node;
		  node -> m_next = m_head -> m_next;
		  node -> m_prev = m_head -> m_next;
	  }
	  else if(!IsEmpty()){
		  Begin()-> m_prev-> m_next = node;
		  node -> m_prev = End();
		  node -> m_next = Begin();
		  Begin() -> m_prev = node;
	  }
	  
      /* if (m_first == false)
      {
		  n = new Node(t);
		  //n ->m_payload = t;
		  n ->m_next = n;
		  n ->m_prev = n;
		  n -> m_next = m_head;
          m_head = n;
          m_tail = n;
		  m_first = true;
		  return;
      }
		  n = new Node();
		  n -> m_prev = m_tail;
		  m_tail -> m_next = n;
		  m_tail = n; */

  }
  
  void PopFront()
  {
     Node *second = Next(Begin());
	 Delete(Begin());
	 m_head -> m_next = second;	//m_head.m_next = second;
  }
  
  void PopBack()
  {
	 Delete(End());
  }

  //Get a pointer to the first node in the list
  const Node *Begin() const{return m_head;}	//return m_head.m_next;
  Node *Begin(){return m_head;}				//same...

  //get a pointer to the last node in the list
  const Node *End() const{return m_tail;}	//return m_head.m_next->m_prev;
  Node *End(){return m_tail;}

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const
  {
      if (!IsReversed())	//!reverse!reversed
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
          return n->m_next; //Don't know if we need the Return in front of these
      }

      else
      {
          return n->m_prev; //Don't know if we need the Return in front of these
      }
  }

  //Find a node with the specified key
  const Node *Find(const T &t) const
  {
      Node *itr = m_head;
      
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
      
      Node *itr = m_head;
      
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
	  if(n == nullptr){return;}
	  if(n == m_head){
		if(n->m_next == n){
			m_head = nullptr;
			m_tail = nullptr;
		}
		else{
			if(reversed){
				m_head = n->m_prev;
			}
			else{
				m_head = n->m_next;
			}
		}
	  }
	  if(n == m_tail){
		if(n->m_prev == n){
			m_tail = nullptr;
			m_head = nullptr;
		}
		else{
			if(reversed){
				m_tail = n->m_next;
			}
			else{
				m_tail = n->m_prev;
			}
		}
	  }
      n->m_prev->m_next = n->m_next;
      n->m_next->m_prev = n->m_prev;
	  
      delete n;
  }

  //Reverse the list in O(1) time
  void Reverse()
  {
      /* Node *temp = m_head;
      m_head = m_tail;
      m_tail = temp;
      reversed = !reversed; */
	  Node *temp = m_head;
	  Node *nextnode;
	  Node *head = m_head;
	  
	  nextnode = head -> m_next;
	  temp = head -> m_prev;
	  head -> m_prev = head -> m_next;
	  head -> m_next = temp;
	  head = nextnode;
	  
	  while(head != m_head){
		nextnode = head -> m_next;
		temp = head -> m_prev;
		head -> m_prev = head -> m_next;
		head = nextnode;
	  }
  }
  
  bool IsReversed()
  {
      return reversed;
  }

  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  Node   *m_head;            // Front node
  Node   *m_tail;            // Back node
  bool   reversed;           // Tracks current direction of list
  bool	 m_first;
  Node   *n;
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{
    Node *itr = b->m_head;
      
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