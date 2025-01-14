/*
 * This is Parth's code
 */

#include <iostream>
#include <cstring>
#include "Student.h"
#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node(Student* newStudent);
  ~Node();

  Node* getNext();
  Student* getStudent();

  void setNext(Node* nextNode);
  void setStudent(Student* newStudent);
  
 private:
  Student* student;
  Node* next;
};

#endif
