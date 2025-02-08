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
  int tblSize = 101; //initial table size
  Node** table = new Node*[tblSize]; //double ptr to table

  for (int a = 0; a < (tblSize); a++) { //init table slots to null
    table[a] = NULL;
  }
  cout << "Initialized 101-table nodes to null." << endl;

  string nameText; //for grabbing names
  
  vector<string> firsts;
  fstream FirstsFile("first-names.txt"); //read from file
  for (int a = 0; a < 300; a++) {
    FirstsFile >> nameText;
    FirstsFile.ignore();
    firsts.push_back(nameText); //add to vector
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

  for (int a = 1; a < studentNum; a++) { //STUDENT GENERATOR
    Node* newStudent = genStudent(firsts, lasts, a);
    int hashSlot = hashFunc(newStudent, tblSize);
    
    if (table[hashSlot] == NULL) { //check if table slot open
      table[hashSlot] = newStudent;
    }
    else if (table[hashSlot]->getNext() == NULL) { //check if second node is open
      table[hashSlot]->setNext(newStudent);
    }
    else if (table[hashSlot]->getNext()->getNext() == NULL) { //check if third node is open
      table[hashSlot]->getNext()->setNext(newStudent);
    }
    else { //else, rehash
      rehash(table, tblSize);
      //rerun code to hash in the student who previously failed and caused rehash
      int hashSlot = hashFunc(newStudent, tblSize);
      if (table[hashSlot] == NULL) {
	table[hashSlot] = newStudent;
      }
      else if (table[hashSlot]->getNext() == NULL) {
	table[hashSlot]->setNext(newStudent);
      }
      else if (table[hashSlot]->getNext()->getNext() == NULL) {
	table[hashSlot]->getNext()->setNext(newStudent);
      }
    }
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
  if (table[hashSlot] == NULL) { //if free slot
    table[hashSlot] = newNode;
    cout << newStu->getFirst() << " has been added." << endl;
  }
  //chaining here
  else {
    if (table[hashSlot]->getNext() == nullptr) { //linked slot 2
      Node* head = table[hashSlot];
      head->setNext(newNode);
    }
    else if (table[hashSlot]->getNext()->getNext() == nullptr) { //linked slot 3
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
      cout << "Hash " << a << ": " << table[a]->getStudent()->getFirst() << " " << table[a]->getStudent()->getLast() << ", "
	<< table[a]->getStudent()->getID() << ", " << fixed << setprecision(2) << table[a]->getStudent()->getGPA()
	<< endl;
	
      if (table[a]->getNext() != NULL) {
	cout << "Hash " << a << " (2): " << table[a]->getNext()->getStudent()->getFirst() << " "
	     << table[a]->getNext()->getStudent()->getLast() << ", "
	     << table[a]->getNext()->getStudent()->getID() << ", " << fixed << setprecision(2)
	     << table[a]->getNext()->getStudent()->getGPA()
	     << endl;
	if (table[a]->getNext()->getNext() != NULL) {
	  cout << "Hash " << a << " (3): " << table[a]->getNext()->getNext()->getStudent()->getFirst() << " "
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
  //create node to hash and find where this student should be stored in the table
  Student* delFinder = new Student(false);
  delFinder->setID(deleteID);
  Node* deleteFinder = new Node(delFinder);
  int hashSlot = hashFunc(deleteFinder, tblSize);

  if (table[hashSlot]->getStudent()->getID() == deleteID) { //check 1st
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
  else if (table[hashSlot]->getNext()->getStudent()->getID() == deleteID) { //check 2nd
    if (table[hashSlot]->getNext() != NULL) {
      Node* temp = table[hashSlot]->getNext();
      table[hashSlot]->setNext(temp->getNext());
      cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
      delete temp;
    }
  }
  else if (table[hashSlot]->getNext()->getNext()->getStudent()->getID() == deleteID) { //check 3rd
    Node* temp = table[hashSlot]->getNext()->getNext();
    table[hashSlot]->getNext()->setNext(NULL);
    cout << "Deleted student " << temp->getStudent()->getFirst() << endl;
    delete temp;
  }
}

void quitter(bool &input) { //quit
  cout << "Goodbye!" << endl;
  input = false;
}

Node* genStudent(vector<string> firsts, vector<string> lasts, int idCount) {
  int randVal = (rand() % 295);
  
  string newFirst;
  newFirst = firsts[randVal];
  
  string newLast;
  newLast = lasts[randVal];

  float newGPA = ((rand() % 501) / 100.0);
  
  Student* newStu = new Student(false); //create new student without prompting user

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
  int hashNum = (((6 * stuID + 17) % 647) % tblSize); //simple hash that grows with tblSize
  //cout << hashNum << endl;
  return hashNum;
}

void rehash(Node** &table, int &tblSize) {
    int oldSize = tblSize;
    tblSize = (tblSize * 2) + 1; //expand size
    Node** tableNew = new Node*[tblSize];

    for (int i = 0; i < tblSize; i++) { //init new table to null
        tableNew[i] = NULL;
    }

    bool needsRehash = false; //check if rehashing is needed again

    for (int a = 0; a < oldSize; a++) {
        Node* current = table[a];
        while (current != nullptr) {
            Node* nextNode = current->getNext(); //save next node before rehashing
            int newSlot = hashFunc(current, tblSize);
	    
            //insert at new slot (handling chaining)
            if (tableNew[newSlot] == nullptr) {
                tableNew[newSlot] = current;
                current->setNext(nullptr);
            } 
            else if (tableNew[newSlot]->getNext() == nullptr) {
                tableNew[newSlot]->setNext(current);
                current->setNext(nullptr);
            } 
            else if (tableNew[newSlot]->getNext()->getNext() == nullptr) {
                tableNew[newSlot]->getNext()->setNext(current);
                current->setNext(nullptr);
            } 
            else {
                //we must rehash again
                needsRehash = true;
            }

            current = nextNode; //move to next node in the old list
        }
    }

    //free old table memory
    delete[] table;

    //assign new table
    table = tableNew;

    cout << "Rehashing complete! New table size: " << tblSize << endl;

    //if any chain exceeded 3 nodes, rehash again
    if (needsRehash) {
        cout << "Chain exceeded length of 3, rehashing again..." << endl;
        rehash(table, tblSize);
    }
}

