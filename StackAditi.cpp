
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    int id;
    string name;
};

class StudentStack
{
    struct Node
    {
        Student data;
        Node* next;
    };

    Node* top;

public:
    StudentStack()
    {
        top = nullptr;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void push(Student s)
    {
        Node* newNode = new Node;
        newNode->data = s;
        newNode->next = top;
        top = newNode;
    }

    bool pop(Student& s)
    {
        if (isEmpty())
            return false;

        Node* temp = top;
        s = temp->data;
        top = top->next;
        delete temp;
        return true;
    }
};

int main()
{
    StudentStack st;
    Student s1 = {5, "Aditi"};
    Student s2;

    st.push(s1);

    if (st.pop(s2))
        cout << s2.id << " " << s2.name;

    return 0;
}
