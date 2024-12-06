#include "Student.h"
#include "Node.h"

#include <iostream>
//#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

void adder(Node* &head);
void printer(Node* next, Node head);
void deleter(Node* &head);
void quitter(Node* head, bool &input);

int main()
{
  /*Student george;
  vector<Student*> stu;
  cin >> george.first;
  george.id = 123;
  george.gpa = 4.23;
  Student* ptr = &george;
  stu.push_back(ptr);
  cout << stu[0]->first << stu[0]->id << stu[0]->gpa << endl;
  adder(stu);*/

  Node* head = nullptr;
  bool input = true;
  while (input == true) {
    
    cout << "Input a command." << endl;
    char command[6] = "";

    cin >> command; 
    cin.ignore();
    if (strcmp(command, "ADD") == 0) {
      adder(head);
    }
    else if (strcmp(command, "PRINT") == 0) {
      printer(head, head);
    }
    else if (strcmp(command, "DELETE") == 0) {
      deleter(head);
    }
    else if (strcmp(command, "QUIT") == 0) {
      quitter(head, input);
    }
    else {
      cout << "Invalid input! Try again." << endl;
    }
  }
}

void adder(Node* &head) {
  /*
  bool recur = false;
  if (recur == false) {
  Node* current = head;
  
  Student* newStu = new Student;
  cout << "First name?" << endl;
  cin >> newStu->first;
  cout << "Last name?" << endl;
  cin >> newStu->last;
  cout << "ID Number?" << endl;
  cin >> newStu->id;
  cout << "Grade Point Average?" << endl;
  cin >> newStu->gpa;
  }
  
  if (current == nullptr) {
    head = new Node(newStu);
  }
  else {
    if (current->getNext() == nullptr) {
      current->setNext(new Node(nullptr));
      current->getNext()->setStudent(newStu);
      cout << newStu->getFirst() << " has been added." << endl;
    }
    else {
      adder(current->getNext(), newStu)
    }
    }*/
  }

void printer(vector<Student*> &stu) {
  for (auto it = stu.begin(); it != stu.end(); ++it) {
    cout << (*it)->first << " " << (*it)->last << ", " << (*it)->id << ", " <<
      fixed << setprecision(2) << (*it)->gpa << endl;
  }
}

void deleter(vector<Student*> &stu) {
    int deleteID;
    cout << "Enter the ID of the student to be deleted: ";
    cin >> deleteID;

    for (auto it = stu.begin(); it != stu.end();) {
        if (deleteID == (*it)->id) {
            cout << "Deleting student..." << endl;
            stu.erase(it);
        } else {
            ++it; // Move to the next student only if not deleted
        }
    }
}

void quitter(vector<Student*> &stu, bool &input) {
  cout << "Goodbye!" << endl;
  input = false;
}
