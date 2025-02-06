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
void deleter(Node* table[], int deleteID);
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
    lasts.push_back(nameText);
    nameText = "";
  }
  //cout << lasts[29] << endl;
  LastsFile.close();

  for (int a = 1; a < 6; a++) {
    Node* newStudent = genStudent(firsts, lasts, a);
    int hashSlot = hashFunc(newStudent, tblSize);
    table[hashSlot] = newStudent;
    cout << hashSlot << ": " << table[hashSlot]->getStudent()->getFirst() << endl;
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
        deleter(table, deleteID);
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
    
void printer(Node* table[], int tblSize) {
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
  
void deleter(Node* table[], int deleteID) {
  /*if (head->getStudent()->getID() == deleteID) { //if HEAD is the one to be deleted, special case
    Node* temp = head;
    head = head->getNext();
    cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
    delete temp;
    return;
  }
  if (head == nullptr) { //check for if the list is empty now (ie head was the only one)
    return;
  }
  Node* current = head;
  if (current->getNext()->getStudent()->getID() == deleteID) {
    //check if next's ID is the one we want, since we need to be able to reassign this node's pointer
    Node* toDelete = current->getNext();
    Node* newNext = current->getNext()->getNext();
    current->setNext(newNext); //skip the to be deleted node
    cout << "Deleted student " << toDelete->getStudent()->getFirst() << endl;
    delete toDelete; //and now delete it, like it was never there...
  }
  else { //walk through
    Node* temp = current->getNext();
    deleter(temp, deleteID); //recursion
    }*/
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
