/*
 * C++ Linked Student List
 * ADD and DELETE students to your Student List.
 * Program will keep track of student names, ID, and GPA.
 * ADD, PRINT, DELETE, QUIT, AVERAGE
 * 1/16/2025
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

void adder(Student* newStu, Node* table[], int tblSize);
void printer(Node* table[], int tblSize);
void deleter(Node* table[], int deleteID, int tblSize);
void quitter(Node* head, bool &input);
Node* genStudent(vector<string> firsts, vector<string> lasts, int idCount);
int hashFunc(Node* node, int tblSize);

int main()
{
  int tblSize = 101;
  Node* table[tblSize];
  for (int a = 0; a < (sizeof(table) / sizeof(table[0])); a++) {
    table[a] = nullptr;
  }
  cout << "Initialized 101-table nodes to null." << endl;

  Node* head = nullptr;

  string nameText;
  
  vector<string> firsts;
  fstream FirstsFile("first-names.txt");
  for (int a = 0; a < 30; a++) {
    getline(FirstsFile, nameText);
    FirstsFile.ignore(256, '\n');
    firsts.push_back(nameText);
    nameText = "";
  }
  //srand(time(NULL)); //random seed  
  //cout << firsts[rand() % 25] << endl;
  FirstsFile.close();

  vector<string> lasts;
  fstream LastsFile("last-names.txt");
  for (int a = 0; a < 30; a++) {
    getline(LastsFile, nameText);
    LastsFile.ignore(256, '\n');
    lasts.push_back(nameText);
    nameText = "";
  }
  //cout << lasts[29] << endl;
  LastsFile.close();

  for (int a = 1; a < 6; a++) { //STUDENT GENERATOR
    Node* newStudent = genStudent(firsts, lasts, a);
    int hashSlot = hashFunc(newStudent, tblSize);
    table[hashSlot] = newStudent;
    cout << hashSlot << ": " << endl;
    cout << table[hashSlot]->getStudent()->getFirst() << endl; //first
    cout << "last name: " << table[hashSlot]->getStudent()->getLast() << endl; //last
    cout << table[hashSlot]->getStudent()->getFirst() << "last name: " << table[hashSlot]->getStudent()->getLast() << endl; //BUGGED
    //hash slot, colon, space, first, *last*
    cout << hashSlot << ": " << table[hashSlot]->getStudent()->getFirst() << " " << table[hashSlot]->getStudent()->getLast() << endl;
    cout << endl;
  }

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
      quitter(head, input);
    }
    else {
      cout << "Invalid input! Try again." << endl;
    }
  }
}

void adder(Student* newStu, Node* table[], int tblSize) {
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
      //rehash
    }
  }
}
    
void printer(Node* table[], int tblSize) { //PRINT BY HASH TABLE
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
  
void deleter(Node* table[], int deleteID, int tblSize) {
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

void quitter(Node* head, bool &input) {
  cout << "Goodbye!" << endl;
  input = false;
}

Node* genStudent(vector<string> firsts, vector<string> lasts, int idCount) {
  int randVal = (rand() % 25);
  
  string newFirst;
  newFirst = firsts[randVal];
  
  string newLast;
  newLast = lasts[randVal];

  float newGPA = ((rand() % 501) / 100);
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
