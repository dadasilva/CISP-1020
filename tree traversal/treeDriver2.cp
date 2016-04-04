//treeDriver.cpp
//Author: David DaSilva
//Date: 03/29/2016
// this program reads in a file containing information about different people into a tree. it then allows
// the user to search the tree using binary tree traversal methods from the the tree.h file. the tree sets the
// root based on the first set of data and places the next person structures the to the side of the tree
// accordingly. the nature of the program allows the user to repeatedly traverse the tree with options to
// view new or previous field selections. have fun.

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "tree.h"
#include "traversal.h"

using namespace std;

//main
// main creates the tree and contact array used througout the program. the program begins by asking
// the user for the file name in the loadData function. when a data file is successfully aquired the contact
// array is passed to the tree structure. important values passed to the tree are the names and the 'i'
// values passed through the loop. this is critical to the whole program in that the 'i' values are passed to
// each traversal method and used to print the contact structures.
int main(){
  contact x[100];
  tree<string> myTree;
  int num = loadData(x); // num is the amount of times a line is read into the tokenize function.
                         // critical for reading in proper amount of data to the tree.

  cout << endl;
  cout << "*** Welcome to the NSA POI System ***" << endl;
  cout << " In order to search our database," << endl;
  cout << " choose data traversal method:   " << endl;

  //places the lastName node value into the 
  //tree as well as the array position arP in tree.h
  for(int i = 0; i < num; i++){
    myTree.insert(x[i].lastName, i);
  }

 int check = menu(myTree, x);

  if(check == 0)
      return(0);
}
  
//loadData
// load data asks the user for the file and checks if the file exists
// also returns the array of contact structures to be passed to the tree in
// main.
// parameters:
//  contact structure - needed to construct proper fields for each person
// returns the contact structure array needed for the insert function.
int loadData(contact x[]){
  ifstream input;
  string line[100];
  int i = 0;
  do{
    cout << "Please enter filename:";
    char filename[100];
    cin >> filename;
    input.open(filename);
    if(!input.is_open())
    cout << "file cannot be opened..." << endl;
  }while(!input.is_open());
  if(!input.eof()){
     while(getline(input, line[i])){
     //getline(input, line[i]);
     string buffer = line[i];
     tokenize(buffer, x[i]);
     i++;
    }
  }
  return(i); 
}

// tokenize
// the nature of the data requires the extraction of each line to suit the contact structures.
// This deals with one contact at a time using strtok functions.
// parameters:
//  buffer - a string of words from a single line in the data
//  contact array - needed to build each contact node
// returns an individual contact node to the array
void tokenize(string buffer, contact &x){
  char input[100];
  strcpy(input, buffer.c_str());
  char *token = strtok(input , ",");
	x.firstName = token;
        token = strtok(NULL, ", ");
        x.lastName = token;
        token = strtok(NULL, ",");
        x.streetAddress = token;
   	    token = strtok(NULL, ",");
        x.city = token;
        token = strtok(NULL, ",");
        x.state = token;
        token = strtok(NULL, ",");
        x.zip = token;
}


//menu
// menu is called from main giving the user the ability to choose a traversal routine.
// the routine selection is chosen from a switch and passed to that methods function.
// Before routine begins the user chooses fields from the submenu.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//  contact array - the structure holding the contact information
int menu(tree<string> myTree, contact x[]){
    cout << "(1) Pre-order traversal" << endl;
    cout << "(2) In-order traversal " << endl;
    cout << "(3) Post-order traversal" << endl;
    cout << "(4) Breadth-first traversal" << endl;
    cout << "(5) Search for a name" << endl;
    cout << "(6) Exit "<< endl;
    int choice; // variable to choose a routine
    cin >> choice;
    int go[6]; // variable to choose a selection field
  switch (choice){
    case (1):
      submenu(go);
      mypreOrder(myTree, x, go);
      break;
    case(2):
      submenu(go);
      myinOrder(myTree, x, go);
      break;
    case(3):
      submenu(go);
      mypostOrder(myTree, x, go);
      break;
    case(4):
      submenu(go);
      myBreadth(myTree, x,go);
      break;
    case(5):
      submenu(go);
      cout << "Enter a last name" << endl;
      mySearch (myTree, x, go);
      break;
    case(6):
      return(0);
      break;
    default:
      cout << "invalid choice..." << endl;
    }
return(false);
}
//submenu
// submenu gives the user the ability to choose what fields they wish to see. The logic
// behind the submenu suggests that the choices fill a selection array to be passed to each routine
// through a 6 figure loop.
// parameters:
//  go -  the selection array that is returned to the main menu and passed to a routine
int submenu(int go[]){
  cout << endl << "Choose information fields that " << endl;
  cout << "you wish to see (choose 0 to disregard a field):" << endl;
  int choice;
  cout << "  (1) Firstname" << endl;
  cout << "  (2) Lastname" << endl;
  cout << "  (3) Address" << endl;
  cout << "  (4) City" << endl;
  cout << "  (5) State" << endl;
  cout << "  (6) Zipcode" << endl;
  for(int i = 0; i < 6; i++){
    cin >> choice;
    if(choice > -1 && choice < 7)
      go[i] = choice;
    else{
      while(choice < -1 && choice > 7){
        cout << "!!!Must choose integer from 0 - 6, lets not get feisty!!!\n";
        cin >> choice;
        cout << "...malfeasance = surveillance...\n";
      }
    }
    go[i] = choice;
    
  }
return(false);
} 

//mypreOrder
// this function creates a vector to hold array positions from the tree function preOrder and fills
// the vector according to the tree.h logic.  when the vector is filled, the information:
// contact structure array, the filled vector, and the tree are passed to the printer.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
//  go - needed to fulfill the fields selection requirements in the print function.
void mypreOrder(tree<string> myTree, contact x[], int go[]){
  vector<int> PREVector;
  cout << "*** preorder ***" << endl << endl;
  myTree.preOrder(myTree.root, PREVector);
  print(x, go, PREVector, myTree);
  //menu(myTree, x);
}

//mypostOrder
// this function creates a vector to hold array positions from the tree function postOrder and fills
// the vector according to the tree.h logic.  when the vector is filled, the information:
// contact structure array, the filled vector, and the tree are passed to the printer.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
//  go - needed to fulfill the fields selection requirements in the print function.
void mypostOrder(tree<string>  myTree, contact x[], int go[]){
  vector<int> PSTVector;
  cout << "*** postOrder ***"<< endl <<  endl;
  myTree.postOrder(myTree.root, PSTVector);
  print(x, go, PSTVector, myTree);
  //menu(myTree, x);
}

//myinOrder
// this function creates a vector to hold array positions from the tree function inOrder and fills
// the vector according to the tree.h logic.  when the vector is filled, the information:
// contact structure array, the filled vector, and the tree are passed to the printer.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
//  go - needed to fulfill the fields selection requirements in the print function.
void myinOrder(tree<string>  myTree, contact x[], int go[]){
  vector<int> INVector;
  cout << "*** inOrder ***"<< endl << endl;
  myTree.inOrder(myTree.root, INVector);
  print(x, go, INVector, myTree);
  //menu(myTree, x);
}

//mySearch
// this function creates a vector to hold one position from the tree function search and fills
// the vector according to the tree.h logic. Before doing so the function asks for a string
// corresponding to the menu output. when the vector is filled, the information:
// contact structure array, the filled vector, and the tree are passed to the printer.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
//  go - needed to fulfill the fields selection requirements in the print function.
void mySearch(tree<string> myTree, contact x[], int go[]){
   vector<int> searchVector;
   cout << "*** Search ***" << endl << endl;
   string temp;
   cin >> temp;
   myTree.search(temp, searchVector);
   print(x, go, searchVector, myTree);
   //menu(myTree, x);
}

//myBreadth
// this function creates a vector to hold array positions from the tree function breadth and fills
// the vector according to the tree.h logic.  when the vector is filled, the information:
// contact structure array, the filled vector, and the tree are passed to the printer.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
//  go - needed to fulfill the fields selection requirements in the print function.

void myBreadth(tree<string> myTree, contact x[], int go[]){
   vector<int> breadthVector;
   myTree.breadth(myTree.root, breadthVector);
   print(x, go, breadthVector, myTree);
   //menu(myTree, x);
}

//print
// the print function takes the selection array from go and checks for values that correspond
// to a loop. when the submenu takes in data properly, 'go' should pass values of zero to five to a print
// array. That print array than matches with values in a vector loop printing Field values
// the user chooses from submenu.
// parameters:
//   contact array - needed to print information for each person.
//   go - needed to fulfill the fields selection requirements in the print function and translate
//    to the print array.
//   sort - contains the routine vector containing array positions preOrder, postOrder, etc.
//   myTree -the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
// after this function is called, it calls the repeat_choice function passing the selections if needed
// as well as the myTree object and the contact array data.
void print(contact x[], int go[], vector<int> sort, tree<string> myTree){
 
   int i = 0;
   int print[6];

   for(i = 0; i < 6; i++){
       if(go[i] == i+1){
           print[i] = i; // zero means go to print
       }
   }
  
   for(vector<int>::iterator it = sort.begin() ; it != sort.end(); ++it){ 
       if(print[0] == 0)
         cout << x[*it].firstName << " ";
       if(print[1] == 1)
         cout << x[*it].lastName << endl;
       if(print[2] == 2)
         cout << x[*it].streetAddress;
       if(print[3] == 3)
         cout <<" " << endl << x[*it].city;
       if(print[4] == 4)
         cout << x[*it].state;
       if(print[5] == 5)
         cout  << " " << x[*it].zip;
         cout  << endl <<"-------------------------\n";
   }
   cout << endl;
   repeatChoice(go, myTree, x);
}

//repeatChoice
// repeatChoice asks the user to reuse the selections from the last submenu instance and passes it to either
// the orginal menu if new fields are wanted or otherwise - to the repeat menu using the selections.
// parameters:
//  go - needed to fulfill the fields selection requirements in the repeat_menu function and translate
//  to the print array.
//  myTree -the tree structure created from the insertion routine holding nodes with array positions
//           it is needed to call the preorder function from the tree.h file.
//  contact array - needed to print information for each person.
// this function takes the user three ways: the original menu, the repeat_selection menu or repeats the
// repeat_choice output.
void repeatChoice(int go[], tree<string> myTree, contact x[]){
  cout << "Do you want to see use the same fields\n";
  cout << "for your next search (y/n)?  ";
  char choice;
    int check;
  cin >> choice;
  if(choice == 'y' || choice == 'Y')
    check = repeat_menu(myTree, x, go);
    if(check == 0)
        return;
  else if(choice == 'n' || choice == 'N')
    menu(myTree, x);
  else 
    cout << "Choice invalid...\n";
    repeatChoice(go, myTree, x);
}
      
//repeat_menu
// repeat_menu is called from repeat_choice giving the user the ability to reuse selections .
// the routine selection is chosen from a switch - the same as it shows in
// the main menu - and passed to that methods function.
// Before routine begins the user chooses fields from the submenu.
// parameters:
//  myTree - the tree structure created from the insertion routine holding nodes with array positions
//  contact array - the structure holding the contact information
int repeat_menu(tree<string> myTree, contact x[], int go[]){
    cout << "(1) Pre-order traversal" << endl;
    cout << "(2) In-order traversal " << endl;
    cout << "(3) Post-order traversal" << endl;
    cout << "(4) Breadth-first traversal" << endl;
    cout << "(5) Search for a name" << endl;
    cout << "(6) Exit "<< endl;
    int choice;
    cin >> choice;
  switch (choice){
    case (1):
      mypreOrder(myTree, x, go);
      break;
    case(2):
      myinOrder(myTree, x, go);
      break;
    case(3):
      mypostOrder(myTree, x, go);
      break;
    case(4):
      myBreadth(myTree, x,go);
      break;
    case(5):
      cout << "Enter a last name" << endl;
      mySearch (myTree, x, go);
      break;
    case(6):
      return(0);
      break;
    default:
      cout << "invalid choice..." << endl;
    }
    return(false);
}

