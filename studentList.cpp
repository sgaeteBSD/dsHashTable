/*
 * Data Structures Hash Table
 * ADD and DELETE students to your Student List.
 * Program will keep track of student names, ID, and GPA.
 * ADD, PRINT, DELETE, QUIT
 * 2/7/2025
 * Santiago Gaete
 */

#include "Student.h"
#include "Node.h"
#include <iostream>
#include <cstring>
#include <iomanip>

#include <vector>
#include <fstream>

using namespace std;

void adder(Student* newStu, Node** table, int tblSize);
void printer(Node** table, int tblSize);
void deleter(Node** table, int deleteID, int tblSize);
void quitter(bool &input);
Node* genStudent(vector<string> firsts, vector<string> lasts, int idCount);
int hashFunc(Node* node, int tblSize);
void rehash(Node** &table, int &tblSize);

int main()
{
  int tblSize = 101;
  Node* tableOrig[tblSize]; 
  Node** table = tableOrig;

  for (int a = 0; a < (sizeof(tableOrig) / sizeof(tableOrig[0])); a++) {
    table[a] = NULL;
  }
  cout << "Initialized 101-table nodes to null." << endl;

  string nameText;
  
  vector<string> firsts;
  fstream FirstsFile("first-names.txt");
  for (int a = 0; a < 300; a++) {
    FirstsFile >> nameText;
    FirstsFile.ignore();
    firsts.push_back(nameText);
    nameText = "";
  }
  FirstsFile.close();

  vector<string> lasts;
  fstream LastsFile("last-names.txt");
  for (int a = 0; a < 300; a++) {
    LastsFile >> nameText;
    LastsFile.ignore();
    lasts.push_back(nameText);
    nameText = "";
  }
  LastsFile.close();

  cout << "How many students would you like to randomly generate?" << endl;
  int studentNum;
  cin >> studentNum;

  bool rehashed = false;
  for (int a = 1; a < studentNum; a++) { //STUDENT GENERATOR
    if (rehashed == false) {
    Node* newStudent = genStudent(firsts, lasts, a);
    int hashSlot = hashFunc(newStudent, tblSize);
    /*if (rehashed == true) {
      cout << a << endl;
      cout << "BLARG" << hashSlot << endl;
    }*/
    if (table[hashSlot] == NULL) {
      table[hashSlot] = newStudent;
    }
    else if (table[hashSlot]->getNext() == NULL) {
      table[hashSlot]->setNext(newStudent);
    }
    else if (table[hashSlot]->getNext()->getNext() == NULL) {
      table[hashSlot]->getNext()->setNext(newStudent);
    }
    else {
      cout << "GOTTA REHASH" << hashSlot << endl;
      rehash(table, tblSize);
      cout << "we're back!" << endl;
      int hashSlot = hashFunc(newStudent, tblSize);
      if (table[hashSlot] == NULL) {
	table[hashSlot] = newStudent;
	cout << table[hashSlot]->getStudent()->getFirst() << endl;
      }
      else if (table[hashSlot]->getNext() == NULL) {
	table[hashSlot]->setNext(newStudent);
      	cout << table[hashSlot]->getNext()->getStudent()->getFirst() << "2" << endl;
      }
      else if (table[hashSlot]->getNext()->getNext() == NULL) {
	table[hashSlot]->getNext()->setNext(newStudent);
      	cout << table[hashSlot]->getNext()->getStudent()->getFirst() << "3" << endl;
      }
      cout << "hello" << hashSlot << endl;
      rehashed = true;
    }
  }
    //hash slot, colon, space, first, *last*
    //cout << hashSlot << ": " << table[hashSlot]->getStudent()->getFirst() << " " << table[hashSlot]->getStudent()->getLast() << endl;
    //cout << endl;
  }

  //cout << table[3]->getStudent()->getFirst() << endl;

  bool input = true;
  while (input == true) {
    cout << "Your commands are ADD, PRINT, DELETE, and QUIT." << endl;
    cout << endl;
    cout << "Input a command." << endl;
    char command[8] = ""; //make sure to fit 7 chars + 1 terminating

    cin >> command; 
    cin.ignore();
    if (strcmp(command, "ADD") == 0) {
      Student* newStu = new Student(true); //create new student (constructor will prompt input)
      adder(newStu, table, tblSize);
    }
    else if (strcmp(command, "PRINT") == 0) {
      printer(table, tblSize);
    }
    else if (strcmp(command, "DELETE") == 0) {
	int deleteID; //get ID to look for
        cout << "Enter the ID of the student to be deleted: ";
        cin >> deleteID;
        deleter(table, deleteID, tblSize);
    }
    else if (strcmp(command, "QUIT") == 0) {
      quitter(input);
    }
    else {
      cout << "Invalid input! Try again." << endl;
    }
  }
}

void adder(Student* newStu, Node** table, int tblSize) {
  Node* newNode = new Node(newStu);
  int hashSlot = hashFunc(newNode, tblSize);
  if (table[hashSlot] == NULL) {
    table[hashSlot] = newNode;
    cout << newStu->getFirst() << " has been added." << endl;
  }
  //work on collisions/chaining here
  else { //if head needs to be replaced with a greater ID
    if (table[hashSlot]->getNext() == nullptr) {
      Node* head = table[hashSlot];
      head->setNext(newNode);
    }
    else if (table[hashSlot]->getNext()->getNext() == nullptr) {
      Node* temp = table[hashSlot]->getNext();
      temp->setNext(newNode);
    }
    else { //rehash
      rehash(table, tblSize);
    }
  }
}
    
void printer(Node** table, int tblSize) { //PRINT BY HASH TABLE
  for (int a = 0; a < tblSize; a++) {
    if (table[a] != NULL) {
      cout << a << ": " << table[a]->getStudent()->getFirst() << " " << table[a]->getStudent()->getLast() << ", "
	<< table[a]->getStudent()->getID() << ", " << fixed << setprecision(2) << table[a]->getStudent()->getGPA()
	<< endl;
	
      if (table[a]->getNext() != NULL) {
	cout << a << " (2): " << table[a]->getNext()->getStudent()->getFirst() << " "
	     << table[a]->getNext()->getStudent()->getLast() << ", "
	     << table[a]->getNext()->getStudent()->getID() << ", " << fixed << setprecision(2)
	     << table[a]->getNext()->getStudent()->getGPA()
	     << endl;
	if (table[a]->getNext()->getNext() != NULL) {
	  cout << a << " (3): " << table[a]->getNext()->getNext()->getStudent()->getFirst() << " "
	       << table[a]->getNext()->getNext()->getStudent()->getLast() << ", "
	       << table[a]->getNext()->getNext()->getStudent()->getID() << ", " << fixed << setprecision(2)
	       << table[a]->getNext()->getNext()->getStudent()->getGPA()
	     << endl;
	}
      }
    }
  }
}
  
void deleter(Node** table, int deleteID, int tblSize) {
  Student* delFinder = new Student(false);
  delFinder->setID(deleteID);
  Node* deleteFinder = new Node(delFinder);
  int hashSlot = hashFunc(deleteFinder, tblSize);
  if (table[hashSlot]->getStudent()->getID() == deleteID) {
    if (table[hashSlot]->getNext() != NULL) {
      Node* temp = table[hashSlot];
      table[hashSlot] = temp->getNext();
      cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
      delete temp;
    }
    else {
      Node* temp = table[hashSlot];
      table[hashSlot] = NULL;
      cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
      delete temp;
    }
  }
  else if (table[hashSlot]->getNext()->getStudent()->getID() == deleteID) {
    if (table[hashSlot]->getNext() != NULL) {
      Node* temp = table[hashSlot]->getNext();
      table[hashSlot]->setNext(temp->getNext());
      cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
      delete temp;
    }
  }
  else if (table[hashSlot]->getNext()->getNext()->getStudent()->getID() == deleteID) {
    Node* temp = table[hashSlot]->getNext()->getNext();
    table[hashSlot]->getNext()->setNext(NULL);
    cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
    delete temp;
  }
}

void quitter(bool &input) {
  cout << "Goodbye!" << endl;
  input = false;
}

Node* genStudent(vector<string> firsts, vector<string> lasts, int idCount) {
  int randVal = (rand() % 25);
  
  string newFirst;
  newFirst = firsts[randVal];
  
  string newLast;
  newLast = lasts[randVal];

  float newGPA = ((rand() % 501) / 100.0);
  
  Student* newStu = new Student(false);

  newStu->setFirst(newFirst);
  newStu->setLast(newLast);
  newStu->setGPA(newGPA);
  newStu->setID(idCount);
  Node* returnNode = new Node(newStu);
  return returnNode;
}

int hashFunc(Node* node, int tblSize) {
  //hash
  int stuID = node->getStudent()->getID();
  int hashNum = (((6 * stuID + 17) % 647) % tblSize);
  //cout << hashNum << endl;
  return hashNum;
}

void rehash(Node** &table, int &tblSize) {
  int oldSize = tblSize;
  tblSize = (tblSize*2)+1;
  Node* tableNew[tblSize]; 
  //Node** table = tableNew;

  for (int a = 0; a < (tblSize); a++) {
    tableNew[a] = NULL;
  }
  int a = 0;
  bool stillHash = true;
  while (a < oldSize && stillHash == true) {
    int hashSlot = hashFunc(table[a], tblSize);
    if (tableNew[hashSlot] == NULL) {
      tableNew[hashSlot] = table[a];
    }
    else if (tableNew[hashSlot]->getNext() == NULL) {
      tableNew[hashSlot]->setNext(table[a]);
    }
    else if (tableNew[hashSlot]->getNext()->getNext() == NULL) {
      tableNew[hashSlot]->getNext()->setNext(table[a]);
    }
    else {
      stillHash = false;
      rehash(table, tblSize);
    }
    a++;
  }
  cout << "hello?" << endl;
  stillHash = false;
  //Node** temp = table;
  table = tableNew;
  //cout << tableNew[105]->getStudent()->getLast() << endl;
  //delete temp;
  cout << "Rehashing complete! New table size: " << tblSize << endl;
}
