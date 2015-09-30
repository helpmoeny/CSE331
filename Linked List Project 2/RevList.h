//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H
#include <iostream>

template<class T> class CRevList{

	public:
	// Constructor.  Sets to an empty list.
	CRevList()
	{
		
	}

	// Destructor.  Deletes everything in the list.
	~CRevList(){
		
	}


	// Copy constructor.  Copies another list.
	CRevList(const CRevList &b){
		
	}

	// Assignment operator.  Copies another list.
	void operator=(const CRevList &b);

	// Clear the list.
	void Clear(){
	Node *temp = m_head;
		while (temp != NULL){
			m_head = m_head.m_next;
			Delete(temp);
			temp = m_head;
		}
		m_head, m_tail = NULL;
	}


	//
	// class Node
	// The nested node class for objects in our linked list.
	//
	// YOU MAY NOT MODIFY THIS CLASS!
	class Node{
		public:
		friend class CRevList;

		Node() { m_next = 0;  m_prev = 0; }
		Node(const T &t) { m_payload = t;  m_next = 0;  m_prev = 0; }

		T Data() { return m_payload; }
		const T Data() const { return m_payload; }

		private:
		Node    *m_next;
		Node    *m_prev;
		T       m_payload;
	};

	// Determines if the list is empty
	bool IsEmpty() const { return (size == 0) ? true : false; }

	//methods to add data to the front or the back of the list
	void PushFront(const T &t) {
		Node *temp = new Node(t);
		cout << t << endl;

		if (size > 0){
			temp->m_next = &m_head;
			temp->m_prev = m_head.m_prev;
			m_head.m_prev->m_next = temp;
			m_head.m_prev = temp;
			m_head = *temp;
		}
		else{
			m_head = *temp;
			temp->m_next = &m_head;
			temp->m_prev = &m_head;
		}
		size++;
	}

	void PushBack(const T &t) {
		Node *temp = new Node(t);
		cout << t << endl;

		if (size > 0){
			temp->m_next = &m_head;
			temp->m_prev = m_head.m_prev;
			m_head.m_prev->m_next = temp; //ISSUE IS HERE TRYING TO SET OLD TAIL.NEXT TO NEW TAIL.
			m_head.m_prev = temp;
		}
		else{
			m_head = *temp;
			temp->m_next = &m_head;
			temp->m_prev = &m_head;
		}
		size++;
	}

	void PopFront() {
		*m_head.m_prev->m_next = m_head.m_next;
		*m_head.m_next->m_prev = m_head.m_prev;
		Node temp = m_head;
		m_head = m_head->m_next;
		Delete(temp);
		size--;
	}

	void PopBack() {
		Node m_tail = m_head->m_prev;
		*m_head.m_prev = m_tail.m_prev;
		*m_tail.m_prev->m_next = m_head;
		Delete(m_tail);
		size--;
	}

	//Get a pointer to the first node in the list
	const Node *Begin() const { return IsEmpty() ? NULL : &m_head; }
	Node *Begin() { return IsEmpty() ? NULL : &m_head; }

	//get a pointer to the last node in the list
	const Node *End() const { return IsEmpty() ? NULL : &m_tail; }
	Node *End() { return IsEmpty() ? NULL : &m_tail; }

	//get a pointer to node next in the list
	const Node *Next(const Node *n) const { return &n.m_next; }
	Node *Next(const Node *n) { return &n.m_next; }

	//Find a node with the specified key
	const Node *Find(const T &t) const { return (t == m_payload) ? &this : Find(*m_next->m_payload); }
	Node *Find(const T &t) { return (t == m_payload) ? &this : Find(*m_next->m_payload); }

	//Delete the given node
	void Delete(Node *n){
		delete n;
	}


	//Reverse the list in O(1) time
	void Reverse() {

	}

		private:
		//NOTE: you may add any private member variables or 
		//      methods you need to complete the implementation
		Node m_head = 0;             // Head node
		int size = 0;

};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b){
	
	
}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}



#endif