#ifndef STUDENT_H
#define STUDENT_H
#include <cstring>
#include <iostream>

using namespace std;

class Student {
  private:
  char* first;
  char* last;
  int id;
  float gpa;
public:
  Student(bool userr);
  ~Student();

  char* getFirst();
  char* getLast();
  int getID();
  float getGPA();

  void setFirst(char* newFirst);
  void setLast(char* newLast);
  void setID(int newID);
  void setGPA(float newGPA);
};

#endif
