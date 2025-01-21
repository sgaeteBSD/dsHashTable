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

using namespace std;

void adder(Node* &head, Student* newStu);
void printer(Node* head, Node* next);
void deleter(Node* &head, int deleteID);
void quitter(Node* head, bool &input);
void averager(Node* head, Node* next, float total, int count);

int main()
{
  Node* head = nullptr;
  bool input = true;
  while (input == true) {
    
    cout << "Input a command." << endl;
    char command[8] = ""; //make sure to fit 7 chars + 1 terminating
    //(i spent an hour on a bug and then i realized this was screwing up my memory... never again)

    cin >> command; 
    cin.ignore();
    if (strcmp(command, "ADD") == 0) {
      Student* newStu = new Student; //create new student (constructor will prompt input)
      adder(head, newStu);
    }
    else if (strcmp(command, "PRINT") == 0) {
      printer(head, head);
    }
    else if (strcmp(command, "DELETE") == 0) {
      if (head != nullptr) { //check for empty list 
	int deleteID; //get ID to look for
        cout << "Enter the ID of the student to be deleted: ";
        cin >> deleteID;
        deleter(head, deleteID);
      }
      else {
	cout << "Your list is empty." << endl;
      }
    }
    else if (strcmp(command, "QUIT") == 0) {
      quitter(head, input);
    }
    else if (strcmp(command, "AVERAGE") == 0) {
      float total = 0; //added up gpas
      int count = 0; //divisor
      averager(head, head, total, count);
    }
    else {
      cout << "Invalid input! Try again." << endl;
    }
  }
}

void adder(Node* &head, Student* newStu) {
  Node* current = head;
  Node* temp = head;
  if (current == nullptr) {
    head = new Node(newStu); //apply to head
    cout << newStu->getFirst() << " has been added." << endl;
  }
  else if (newStu->getID() < head->getStudent()->getID()) { //if head needs to be replaced with a greater ID
    temp = head;
    head = new Node(newStu);
    head->setNext(temp);
  }
  else {
    if (current->getNext() == nullptr) { //if end has been reached
      current->setNext(new Node(newStu)); //create a new node at the end of the list
      cout << newStu->getFirst() << " has been added." << endl;
    }
    else if (newStu->getID() < current->getNext()->getStudent()->getID()) { //place node in ID ordered spot
      temp = current->getNext(); //store old next
      current->setNext(new Node(newStu)); //place new next
      current->getNext()->setNext(temp); //give old next to new next
    }
    else { //keep walking
      Node* temp = current->getNext(); //passer node* for recur
      adder(temp, newStu); //recursion
    }
  }
}
    
void printer(Node* head, Node* next) {
  if (next == head) { //print "studentlist:" to start
    cout << "Student List:" << endl;
  }
  if (next != nullptr) { //if this is a valid element, print it
    cout << next->getStudent()->getFirst() << " " << next->getStudent()->getLast() << ", "
         << next->getStudent()->getID() << ", " << fixed << setprecision(2) << next->getStudent()->getGPA() << endl;
    printer(head, next->getNext()); //recursion
  }
}

void deleter(Node* &head, int deleteID) {
  if (head->getStudent()->getID() == deleteID) { //if HEAD is the one to be deleted, special case
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
  }
}

void quitter(Node* head, bool &input) {
  cout << "Goodbye!" << endl;
  input = false;
}

void averager(Node* head, Node* next, float total, int count) {
  if (next != nullptr) {
    total += next->getStudent()->getGPA();
    count++;
    averager(head, next->getNext(), total, count); //recursion
  } else {
    float average = total/count; //find average
    cout << "Average GPA: " << fixed << setprecision(2) << average << endl;
  }
}
