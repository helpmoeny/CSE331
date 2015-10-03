#include <iostream>
#include <strstream>
#include <stdlib.h>
#include "RevList.h" //reversable doubly linked list
#include "random.h" //random number generator


using namespace std;

int main(int argc, char* argv[]){

  if(argc != 3){
    cerr << "Incorrect number of command line arguments." << endl;
    cerr << "\t[Prompt] <hotpotato> <number of players> <number of passes - or random number seed if negative>" << endl;
  }

  int 
    i_n = atoi(argv[1]), // number of players
    i_m = atoi(argv[2]); // number of passes, -1 for a random pass each turn 

  //random number generator - borrowed from Avida - written by CA OFRIA and modified by J STEDWICK - based on RNG from Numerical Recipes in C: The Art of Scientific Computing (Flannery et al.)
  RandomNumberGenerator rng;

  //are we using a random number for m? if so seed with the absolute value of m
  if(i_m < 0) rng.ResetSeed(i_m * -1); 

  //reversible linked list that will hold the players
  CRevList<unsigned> ll_players;

  //set up the players
  for(unsigned i = 0; i < i_n; i++){
    ll_players.PushBack(i);
  }

  //set up the game
  unsigned u_steps = i_m;

  CRevList<unsigned>::Node *curr = ll_players.Begin();
  CRevList<unsigned>::Node *old = NULL;

  vector<unsigned> v_order;
  
  //play the game
  while(!ll_players.IsEmpty()){
    //i_m = number of passes, i_n = number of players
    if(i_m < 0) u_steps = rng.GetUInt(1,i_n+1);
    
    for(int i = 0; i < u_steps; i++){
      old = curr;
      curr = ll_players.Next(curr);
    }
	
    v_order.push_back(curr->Data());
    ll_players.Delete(curr);
    
    if(!ll_players.IsEmpty()){
      curr = ll_players.Next(old);
      ll_players.Reverse();
    }
  }

  //output the order
  cout << "Final Order: ";
  for(unsigned i = 0; i < i_n; i++){
    cout << v_order.at(i) << " ";
  }
  cout << endl;
}