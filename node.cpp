/*
 * This is Parth's code
 */
#include <iostream>
#include <cstring>
#include "node.h"
using namespace std;
Node::Node(Student* newStudent) {
  // constructor
  // creating new student
  student = newStudent;
  next = NULL; // setting next to null
}
Node::~Node(){
  // destructor
  // deleting the studennt
  delete student;
  next = NULL;
}
Node* Node::getNext() {
  return next;
  // return the next variable when going to the next node.
}
Student* Node::getStudent() {
  return student;
}
void Node::setNext(Node* nextNode) {
  next = nextNode;
}
void Node::setStudent(Student* newStudent) {
  student = newStudent;
}
