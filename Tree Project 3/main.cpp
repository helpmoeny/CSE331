// Name :        main.cpp
// Description : Main program that uses a randomly generated vector to build a binary search tree
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "Tree.h"                // Edit your code for BST implementation in this file

using namespace std;


int main() {
    // load vector from file
    ifstream is("numbers_small.txt");
    istream_iterator<int> start(is), end;
    vector<int> x(start, end);
    cout << "Read " << x.size() << " numbers" << endl;

    // print the numbers to stdout
   cout << "numbers read in:\n";
    copy(x.begin(), x.end(),
    ostream_iterator<int>(cout, " "));
    cout << endl;

    CTree<int> tree;
    srand (time(0));
    bool result = 1;

    for (int i=0; i<x.size(); i++){
        tree.Insert(x[i]);       // edit your insert code in Tree.h
    }

    tree.Preorder(cout);         // edit your preorder traversal code in Tree.h

    cout << endl;

    cout << tree.Depth() << endl;  // edit your depth code in Tree.h

    for (int i=0; i<x.size(); i++){
        if(i%2 == 0){
            tree.Delete(i);      // edit your deletion code in Tree.h
        }
    }

    cout << tree.Depth() << endl;

    cout << endl;

    tree.Preorder(cout);        // edit your preorder traversal code in Tree.h

    cout << endl;

    return 0;
}
