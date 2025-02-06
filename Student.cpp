#include "Student.h"

using namespace std;

Student::Student(bool user) {
  if (user == true) {
    //Input prompt student details
    first = "";
    cout << "First name?" << endl;
    cin >> first;
    last = "";
    cout << "Last name?" << endl;
    cin >> last;
    id = 0;
    cout << "ID Number?" << endl;
    cin >> id;
    gpa = 0;
    cout << "Grade Point Average?" << endl;
    cin >> gpa;
  }
}

Student::~Student() {
}

string Student::getFirst() {
  return first;
}

string Student::getLast() {
  return last;
}

int Student::getID() {
  return id;
}

float Student::getGPA() {
  return gpa;
}

void Student::setFirst(string newFirst) {
  first = "";
  first = newFirst;
}

void Student::setLast(string newLast) {
  last = "";
  last = newLast;
}

void Student::setID(int newID) {
  id = newID;
}

void Student::setGPA(float newGPA) {
  gpa = newGPA;
}
