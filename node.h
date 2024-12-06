// Santiago Gaete
// 12/5/24

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "Student.h"

using namespace std;

class Node {
 private:
  Student* stu;
  Node* next;
 public:
  Node(Student* newStu); //constructor
  ~Node(); //destructor

  void setStudent(Student* newStu);
  Student* getStudent(); //get student pointer
  
  void setNext(Node* newNext);
  Node* getNext(); //get next node pointer in linked list
};

#endif
