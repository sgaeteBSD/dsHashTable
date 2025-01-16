#include "Student.h"

using namespace std;

Student::Student() {
  first = new char[80];
  cout << "First name?" << endl;
  cin >> first;
  cout << "Last name?" << endl;
  cin >> last;
  cout << "ID Number?" << endl;
  cin >> id;
  cout << "Grade Point Average?" << endl;
  cin >> gpa;
}

Student::~Student() {
  delete[] first;
  delete[] last;
}

char* Student::getFirst() {
  return first;
}

char* Student::getLast() {
  return last;
}

int Student::getID() {
  return id;
}

float Student::getGPA() {
  return gpa;
}

void Student::setFirst(char* newFirst) {
  first = new char[80];
  strcpy(first, newFirst);
}

void Student::setLast(char* newLast) {
  last = new char[80];
  strcpy(last, newLast);
}

void Student::setID(int newID) {
  id = newID;
}

void Student::setGPA(float newGPA) {
  gpa = newGPA;
}
