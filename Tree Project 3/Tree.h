using namespace std;
#ifndef CTREE_H
#define CTREE_H

#include <iostream>

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;m_active = true;}
        Node(const T &t) {m_payload = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_payload;}
        const T &Data() const {return m_payload;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_payload;

	bool m_active;
    };
    /**********************************************
    * Name: Insert                                *
    * Purpose: Insert an item in the tree         *
    * Recieves: an item for insertion             *
    * Output: None, inserts the item              *
    **********************************************/
    void Insert(const T &t) 
    {
      //cout << "Insert" << endl;
      //declare new node to keep track of current node in traversal
      Node *Curr;
      Node *Ins = new Node(t);
      Curr = m_root;
      
      //for when the root is not present yet
      if( m_root == 0 )
      {
		m_root = Ins;
      }
      //if (Find(t) != NULL){ Curr = NULL; }	//this creates the multiple twenties
	  
      // walk through the tree until we reach its end
      while(Curr != NULL)
      {
		//cout << "test3" << endl;
		//if the item is less than the current item, move down the left leaf
		if( t < Curr->Data() )
		{
			if(Curr->m_ll == NULL)
			{
				Curr->m_ll = Ins;
				Ins->m_payload = t;
				break; 
			}
			else
			{
				Curr = Curr->m_ll;
			}
	    
		}
		//if the item is more than the current item, move down the right leaf
		if( t > Curr->Data() )
		{
			//check
			if( Curr->m_rl == NULL )
			{
				Curr->m_rl = Ins;
				//perform insert
				Ins->m_payload = t;
				break;
			}
			else
			{
				//move along
				Curr = Curr->m_rl;
			}
		}
		
		//otherwise (if it is equal), no case for equal so exit the traversal
		if( (t > Curr->Data()) == false && (t < Curr->Data()) == false )
		{
			break;
		}
	  }
    }
    
    /**********************************************
    * Name: Preorder                              *
    * Purpose: Output items in preorder         *
    * Recieves: the out stream                   *
    * Output: the items in preorder             *
    **********************************************/
    void Preorder(std::ostream &p_str) 
    {
      Node *Node = m_root;
      //cout << "Preorder" << endl;
      recPre(Node, p_str);
    }
    
    void recPre(Node *Node, std::ostream &p_str)
    { 
      //cout << "recPre1" << endl;
      //cout<< Node->Data() << endl;
      p_str<< Node->Data()<< endl;
      //cout << "recPre2" << endl;
      if (Node->m_ll != NULL)
      {
		//cout << "recPre3" << endl;
		recPre(Node->m_ll, p_str);
      }
      //cout << "recPre4" << endl;
      if (Node->m_rl != NULL)
      {
		//cout << "recPre5" << endl;
		recPre(Node->m_rl, p_str);
      }
    }
    
    int Depth() 
    {
      //cout << "Depth" << endl;
      Node * Node = m_root;
      int Dep = 0;
      int D;
      int currD = 0;
      
      D = recDep(Node);
      //cout << "D:" << D << endl;
      return D;
    }
    
    int recDep( Node *Node )
    {
      if (Node == NULL)
      {
        return 0;
      }

      int left = recDep(Node->m_ll);
      int right = recDep(Node->m_rl); 

      if (left > right)
      {
        return 1 + left;
      }
      else
      {
        return 1 + right;
      }
    }
    
    /**********************************************
    * Name: Find                                  *
    * Purpose: Find an item in the tree           *
    * Recieves: An item to find                   *
    * Output: The node found                      *
    **********************************************/
    const Node *Find(const T &t) const 
    {
      //cout << "Find1"<< endl;
      Node *Curr = new Node();
      Curr = m_root;
      // walk through the tree until we reach its end
      while(Curr != NULL)
      {
		//if the item is less than the current item, move down the left leaf
		if( t < Curr->m_payload )
		{
			Curr = Curr->m_ll;
		}
		//if the item is more than the current item, move down the right leaf
		if( t > Curr->m_payload )
		{
			Curr = Curr->m_rl;
		}
		//otherwise (if it is equal), yield the node found
		if( t = Curr->Data())
		{
			return Curr;
		}
      }
    }
    
    /**********************************************
    * Name: Find                                  *
    * Purpose: Find an item in the tree           *
    * Recieves: An item to find                   *
    * Output: The node found                      *
    **********************************************/
    Node *Find(const T &t) 
    {
      //cout << "Find2" << endl; 
      Node *Curr;
      //cout << "Find2-1" << endl;
      Curr = m_root;
      //cout << "Find2-2" << endl;
      if(m_root != NULL){cout << Curr->Data() << endl;}
      //walk through the tree until we reach its end
	  
      while(Curr!=NULL)
      {
		//if the item is less than the current item, move down the left leaf
		if( t < Curr->Data() )
		{
			//check
			if (Curr->m_ll != NULL){Curr = Curr->m_ll;}
			else{break;}
		}
	
		//if the item is more than the current item, move down the right leaf
		else if( t > Curr->Data() )
		{
			//check;
			if(Curr->m_rl != NULL){Curr = Curr->m_rl;}
			else{break;}
		}
		//otherwise (if it is equal), yield the node found
		else//if(t == Curr->Data())
		{
			//cout << "Find2-6" << endl;
			return Curr;
		}
      }
      return NULL;
    
    }
    
    /**********************************************
    * Name: Delete                                *
    * Purpose: Delete an item in the tree         *
    * Recieves: an item for deletion              *
    * Output: None, deletes the item              *
    **********************************************/
    void Delete(const T &t)
    { 
      if (Find(t) != NULL)
      {
		//cout << "Delete1" << endl;
		Node *Curr = new Node();
		//cout << "Delete2" << endl;
		Curr = m_root;
		//cout << "Delete3" << endl;
		Node *Prev = new Node();
		//cout << "Delete4" << endl;
		// walk through the tree until we reach its end
		//cout << "T:"<< t << endl;
		while(Curr != NULL && t != Curr->Data())
		{
	
			//cout << "Delete5" << endl;
			//if the item is less than the current item, move down the left leaf
			if( t < Curr->Data() )
			{
				//cout << "Delete6" << endl;
				Prev = Curr;
				//cout << "Delete7" << endl;
				if (Curr->m_ll!=NULL){Curr = Curr->m_ll;}
				else{break;}
				//cout << "Delete8" << endl;
			}
			//if the item is more than the current item, move down the right leaf
			if( t > Curr->Data() )
			{
				//cout << "Delete9" << endl;
				Prev = Curr;
				//cout << "Delete10" << endl;
				if(Curr->m_rl!=NULL){Curr = Curr->m_rl;}
				else{break;}
				//cout << "Delete11" << endl;
			}
			if( t == Curr->Data() )
			{
				continue;
			}
	 
		}
		//cout << Curr->Data() << "will be deleted" << endl;  
		if( Curr->m_ll == NULL && Curr->m_rl == NULL )
		{
			//check direction
			if (Prev->m_ll == Curr)
			{
				//move pointers and delete
				cout << Curr->Data() << endl;
				delete Curr;
				Prev->m_ll = NULL;
			}
		if (Prev->m_rl == Curr)
		{
			//move pointers and delete
			cout << Curr->Data() << endl;
			delete Curr;
			Prev->m_rl = NULL;
		}
		}
		if( Curr->m_ll != NULL && Curr->m_rl == NULL )
		{
			//check direction
			if ( Prev->m_ll = Curr )
			{
				//move pointer
				Prev->m_ll = Curr->m_ll;
			}
	  
			if ( Prev->m_rl = Curr )
			{
				//move pointer
				Prev->m_rl = Curr->m_ll;
			}
			delete Curr;
		}
		if( Curr->m_ll == NULL && Curr->m_rl != NULL )
		{
			//check direction
			if ( Prev->m_rl == Curr )
			{
				//move pointer
				Prev->m_rl = Curr->m_rl;
			}
			if (Prev->m_ll == Curr )
			{
				//move pointer
				Prev->m_ll = Curr->m_rl;
			}
			delete Curr;
		}
		if ( Curr->m_ll != NULL && Curr->m_rl != NULL )
		{
			//check direction
			if ( Prev->m_ll == Curr )
			{
				//move pointers
				Prev->m_ll = Curr->m_rl;
				(Curr->m_rl)->m_ll = Curr->m_ll;
			}
			if ( Prev->m_rl == Curr )
			{
				//move pointers
				Prev->m_rl = Curr->m_ll;
				(Curr->m_ll)->m_rl = Curr->m_rl;
			}
			//delete
			delete Curr;
		}
      }
    }
      /*
      if(Find(t)==NULL)
      {
	return;
      }
      else if (t<Node->Data())
      {
	Delete(Node->m_ll,t);
      }
      else if (t> Node->Data())
      {
	Delete(Node->m_rl, t);
      }
      else
      {
	if(Find(Node->m_ll)==NULL)
	{
	  Node=Node->m_rl;
	}
	else if(Find(Node->m_rl)==NULL)
	{
	  Node= Node->m_ll;
	}
	else
	{
	  y=recDel(Node->m_rl);
	  Node->Data()=y;
	}
      }
    }
    int recDel(Node *Node)
    {
      if (Find(Node)==NULL)
      {
	return NULL;
      }
      else if(Find(Node->m_ll)==NULL)
      {
	t=Node->Data();
      }
      else
      {
	t=recDel(Node->m_ll);
      }
      return (t);
    }
    */
     


private:
    Node *m_root;
    Node *Prev;
    int D;

};


#endif
