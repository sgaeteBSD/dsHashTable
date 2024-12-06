#ifndef STUDENT_H
#define STUDENT_H

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

  char* setFirst();
  char* setLast();
  int setID();
  float setGPA();
};

#endif
