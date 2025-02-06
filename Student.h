#ifndef STUDENT_H
#define STUDENT_H
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class Student {
  private:
  string first;
  string last;
  int id;
  float gpa;
public:
  Student(bool userr);
  ~Student();

  string getFirst();
  string getLast();
  int getID();
  float getGPA();

  void setFirst(string newFirst);
  void setLast(string newLast);
  void setID(int newID);
  void setGPA(float newGPA);
};

#endif
