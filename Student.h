#ifndef STUDENT_H
#define STUDENT_H
#include <cstring>
#include <iostream>

class Student {
  private:
  char* first;
  char* last;
  int id;
  float gpa;
public:
  Student();
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
