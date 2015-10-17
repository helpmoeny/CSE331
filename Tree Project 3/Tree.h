//
// Name :         Tree.h
// Description :  all implementation of binary search tree methods
//

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
      Node *node = new Node(t);
      Curr = m_root;
      
      //for when the root is not present yet
      if( m_root == NULL ){
		m_root = node;
      }
		//if (Find(t) != NULL){ Curr = NULL; }	//this creates the multiple twenties
		
		// walk through the tree until we reach its end
		while(Curr != NULL){
			//cout << "test3" << endl;
			//if the item is less than the current item, move down the left leaf
			if( t < Curr->Data() ){
				if(Curr->m_ll == NULL){
					Curr->m_ll = node;
					break; 
				}
				else{	//There is a node there
					Curr = Curr->m_ll;
				}
			}
			//if the item is more than the current item, move down the right leaf
			if( t > Curr->Data() ){
				//check
				if( Curr->m_rl == NULL ){
					Curr->m_rl = node;
					//perform insert
					break;
				}
				else{	//There is a node there
					//move along
					Curr = Curr->m_rl;
				}
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
      PreNode(Node, p_str);
    }
    
    void PreNode(Node *Node, std::ostream &p_str)
    { 
      //cout << "recPre1" << endl;
      //cout<< Node->Data() << endl;
      p_str<< Node->Data()<< " ";
      //cout << "recPre2" << endl;
      if (Node->m_ll != NULL){
		//cout << "recPre3" << endl;
		PreNode(Node->m_ll, p_str);
      }
      //cout << "recPre4" << endl;
      if (Node->m_rl != NULL){
		//cout << "recPre5" << endl;
		PreNode(Node->m_rl, p_str);
      }
    }
    
    int Depth() 
    {
      //cout << "Depth" << endl;
      Node *Node = m_root;
      int Dep = 0;
      int D;
      int currD = 0;
      
      D = DepNode(Node);
      //cout << "D:" << D << endl;
      return D;
    }
    
    int DepNode( Node *Node )
    {
	  if (Node == NULL){
        return 0;
      }
      if (DepNode(Node->m_ll) > DepNode(Node->m_rl)){
        return 1 + DepNode(Node->m_ll);
      }
      else{
        return 1 + DepNode(Node->m_rl);
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
      while(Curr != NULL){
		//otherwise (if it is equal), yield the node found
		if( t == Curr->Data()){
			return Curr;
		}
		//if the item is less than the current item, move down the left leaf
		if( t < Curr->m_number ){
			Curr = Curr->m_ll;
		}
		//if the item is more than the current item, move down the right leaf
		else if( t > Curr->m_number ){
			Curr = Curr->m_rl;
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
      while(Curr!=NULL){
		//if the item is less than the current item, move down the left leaf
		if( t < Curr->Data() ){
			//check
			if (Curr->m_ll != NULL){Curr = Curr->m_ll;}
			else{break;}
		}
	
		//if the item is more than the current item, move down the right leaf
		else if( t > Curr->Data() ){
			//check;
			if(Curr->m_rl != NULL){Curr = Curr->m_rl;}
			else{break;}
		}
		//otherwise (if it is equal), yield the node found
		else{
			//cout << "Find2-6" << endl;
			return Curr;
		}
	}
    return nullptr;	//NULL?
    }
    
    /**********************************************
    * Name: Delete                                *
    * Purpose: Delete an item in the tree         *
    * Recieves: an item for deletion              *
    * Output: None, deletes the item              *
    **********************************************/
    void Delete(const T &t)
    {
		Node *Prev = NULL;
		Node *Curr = new Node();
		Curr = m_root;
        
        while (Curr != NULL){
            if (Curr->m_number == t){break;}
            else{
                if (t < Curr->m_number){
                    Prev = Curr;
                    Curr = Curr->m_ll; //Proceed left down tree
                }
                else if (t > Curr->m_number){
                    Prev = Curr;
                    Curr = Curr->m_rl; //Proceed right down tree
                }
            }
            if (Curr == NULL){	//DON"T MOVE THIS GUY
                return;
            }
        }
        
        //Remove Node with no children
        if (Curr->m_ll == NULL && Curr->m_rl == NULL){
            if (Prev != NULL){
                if (Curr == Prev->m_ll){
                    Prev->m_ll = NULL; //Remove pointer to Curr
                    delete Curr;
                }
                else if (Curr == Prev->m_rl){
                    Prev->m_rl = NULL; //Remove pointer to Curr
                    delete Curr;
                }
            }
            else{
                m_root = NULL; //Root node no longer exists
                delete Curr;
            }
        }
        
        //Delete Node with only left leaf
        if (Curr->m_ll != NULL && Curr->m_rl == NULL){
            if (Prev != NULL){
                if (Curr == Prev->m_ll){
                    Prev->m_ll = Curr->m_ll; //Replace pointer to Curr with its leaf
                }
                else if (Curr == Prev->m_rl){
                    Prev->m_rl = Curr->m_ll; //Replace pointer to Curr with its leaf
                }
            }
            else{
                m_root = m_root->m_ll; //Set root node to left leaf
            }
        }
        
        //Delete Node with only right leaf
        if (Curr->m_ll == NULL && Curr->m_rl != NULL){
            if (Prev != NULL){
                if (Curr == Prev->m_ll){
                    Prev->m_ll = Curr->m_rl; //Replace pointer to Curr with its leaf
                }
                else if (Curr == Prev->m_rl){
                    Prev->m_rl = Curr->m_rl; //Replace pointer to Curr with its leaf
                }
            }
            else{
                m_root = m_root->m_rl; //Set root node to right leaf
            }
        }
        
        //Delete Node with left and right leaf
        if (Curr->m_ll != NULL && Curr->m_rl != NULL){
            Prev = Curr; //Prev becomes the node to be deleted
            Curr = Curr->m_rl; //Curr becomes its right leaf
            if (Curr->m_ll == NULL && Curr->m_rl == NULL){
                 Prev->m_number = Curr->m_number; //Move the data from Curr into Prev's position
                 delete Curr; //Delete Curr
                 Prev->m_rl = NULL; //Remove the pointer to Curr
            }
            else if (Curr->m_ll != NULL){
                Node *ptr = Curr->m_ll; //Creates a pointer to the new left leaf of Curr
                
                while (ptr->m_ll != NULL){
                    Curr = ptr;
                    ptr = ptr->m_ll;
                }
                Prev->m_number = ptr->m_number; //Moves ptr's data to Prev's position
                delete ptr; //Deletes ptr
                Curr->m_ll = NULL; //Removes the pointer to ptr
            }
            else{
                Node *ptr = Curr->m_rl; //Creates a pointer to the new right leaf of Curr
                
                while (ptr->m_rl != NULL){
                    Curr = ptr;
                    ptr = ptr->m_rl;
                }
                
                Prev->m_number = ptr->m_number; //Moves ptr's data to Prev's position
                delete ptr; //Deletes ptr
                Curr->m_rl = NULL; //Removes the pointer to ptr
            }
        }
    }
    
private:
    Node *m_root;
    Node *Prev;
    int D;

};


#endif
